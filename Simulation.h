/****************************************************************************
*																			*
*	File:		Simulation.h												*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jun 6, 2016													*
*																			*
*	Purpose:	This file defines the Simulation class.						*
*																			*
****************************************************************************/

#ifndef SIMULATION_H
#define SIMULATION_H

// Header files

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <time.h>
#include <algorithm>
#include "Operator.h"
#include "Task.h"
#include "Constants.h"
#include "Statistics.h"

using namespace std;
using namespace cnsts;

// Helper functions and definitions

typedef vector<vector<float> > Matrix2D;
typedef vector<Matrix2D> Matrix3D;
bool compareTasks (Task* t1, Task* t2) 
	{return t1->getArrTime() < t2->getArrTime();}

// Global variables

int SEED;

/****************************************************************************
*																			*
*	Definition of Simulation class											*
*																			*
****************************************************************************/

class Simulation
{
//	Public member functions

	public:
		
	//	Constructors
	
		Simulation(int t, int sd, vector<float> trafficLevels);

	//	Inspectors
	
		void getStatSums(Matrix2D& matrix, int run) {stats.getSums(matrix, run);}

	//	Other member functions

		void run();
		void genTasks(int type);
		void runPhase(int& uIndex);
		void processArrival(list<Task*>::iterator& it, int& i);
		void processDepature(Task* task, int& i);
		void output(ostream& out) const {out << stats << endl;}
	
//	Data members

	private:
		float simTime;				// simulation time
		int phase;					// current phase
		int endTimes[NUM_PHASES];	// phase end times
		list<Task*> taskList;		// task list
		Operator op;				// operators
		Matrix2D util;				// utilization
		Statistics stats;			// simulation statistics
		vector<float> traffic; 		// traffic levels
};

//	Operators

ostream& operator<<(ostream& out, const Simulation sim) {sim.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	Simulation													*
*																			*
*	Purpose:	To construct a new simulation								*
*																			*
****************************************************************************/

Simulation::Simulation(int t, int sd, vector<float> trafficLevels) : simTime(), phase(), taskList(), op(), 
																		stats(NUM_TASK_TYPES, NUM_INTS, 0)
{	
//	Check duration of simulation

	if (t < 90 || t%10 != 0) 
	{
		cerr << "Error: Invalid simulation time. Exiting..." << endl;
		exit(1);
	}
	
//	Check traffic array
	
	if (trafficLevels.size() != NUM_HOURS) 
	{
		cerr << "Error: Invalid traffic array. Exiting..." << endl;
		exit(1);
	}
	
//	Set phase end times and seed

	endTimes[0] = 30;
	endTimes[1] = t - 30;
	endTimes[2] = t;
	SEED = sd;
	
//	Set traffic levels

	traffic = trafficLevels;
}

/****************************************************************************
*																			*
*	Function:	run															*
*																			*
*	Purpose:	To run the simulation by completing the generated tasks		*
*																			*
****************************************************************************/

void Simulation::run()
{
	cout << "Beginning simulation..." << endl;

//	Run all phases, tracking the stats index

	int uIndex = 0;
	for (int i = 0; i < 3; i++)
		runPhase(uIndex);
	
	cout << "Simulation completed." << endl;

	return;
}

/****************************************************************************
*																			*
*	Function:	genTasks													*
*																			*
*	Purpose:	To generate tasks of the specified type						*
*																			*
****************************************************************************/

void Simulation::genTasks(int type)
{
//	Create first task and temporary list
	
	srand(SEED++);
	list<Task*> tmpList; 
	Task* task = new Task(type, simTime, rand(), phase, traffic);
	float arrTime = task->getArrTime();
	float serTime = task->getSerTime();
	
//	Add tasks to list while time is left

	while (arrTime < endTimes[phase])
	{
	//	Add current task
	
		tmpList.push_back(task);
		
	//	Get next task
	
		task = new Task(type, arrTime, rand(), phase, traffic);
		arrTime = task->getArrTime();
		serTime = task->getSerTime();
	}

//	Merge new list with task list

	taskList.merge(tmpList, compareTasks);

	return;
}

/****************************************************************************
*																			*
*	Function:	runPhase													*
*																			*
*	Purpose:	To run the specified phase of the simulation				*
*																			*
****************************************************************************/

void Simulation::runPhase(int& uIndex)
{
//	Generate all task types
	
	for (int tp = 0; tp < NUM_TASK_TYPES; tp++)
		genTasks(tp);

//	Initiliaze variables

	list<Task*>::iterator it = taskList.begin();
	Task* arrTask;
	float arrTime;
	Task* depTask;
	float depTime;
	
//	Debugging 

	if (DEBUG)
	{
		cout << "Task List" << endl; int i = 0;
		for (list<Task*>::iterator it = taskList.begin(); it != taskList.end(); it++)
			cout << "Task " << i++ << ":  " << **it << endl;
		cout << endl;
	}
	
//	Process all events in the task list
	
	cout << "Beginning Phase " << phase << "." << endl;

	while(it != taskList.end())
	{
	//	Get next arrival and depature
	
		arrTask = *it;
		arrTime = arrTask->getArrTime();
		depTask = op.getCurrTask();
		depTime = op.getDepTime();
				
	//	Process next event

		if (arrTime < depTime || depTime == -1)
			processArrival(it, uIndex);
		else 
			processDepature(depTask, uIndex);
	}
			
//	Process remaining tasks in the queue

	depTask = op.getCurrTask();
	depTime = op.getDepTime();
	
	while (op.isBusy() && depTime <= endTimes[2])
	{
		processDepature(depTask, uIndex);
		depTask = op.getCurrTask();
		depTime = op.getDepTime();
	}

//	Clear task list for next phase
	
	cout << "Phase " << phase++ << " completed." << endl << endl;
	taskList.clear();

	return;
}

/****************************************************************************
*																			*
*	Function:	processArrival												*
*																			*
*	Purpose:	To process a task arrival								 	*
*																			*
****************************************************************************/

void Simulation::processArrival(list<Task*>::iterator& it, int& i)
{	
//	Update time
	
	Task* task = *it;
	simTime = task->getArrTime();
	int type = task->getType();

//	Update state and stats

	if (DEBUG) cout << "\t Task arriving at " << simTime << endl;
	op.addTask(task);
	it++;
	
	stats.incNumTasksIn(type, i, 1);
	
//	cout << op << endl;
	
	return;
}

/****************************************************************************
*																			*
*	Function:	processDepature												*
*																			*
*	Purpose:	To process a task depature								 	*
*																			*
****************************************************************************/

void Simulation::processDepature(Task* task, int& i)
{
//	Get task characteristics

	float arrTime = task->getArrTime();
	float depTime = task->getDepTime();
	float serTime = task->getSerTime();
	float begTime = depTime - serTime;
	int type = task->getType();
	
//	Get interval times and update time
	
	float beginInt = stats.getInterval(i);
	float endInt = beginInt + INT_SIZE;
	simTime = depTime;
	float timeBusy = 0;
	float percBusy = 0;

//	Record utilization

	while (begTime >= endInt)
	{
		i++;
		beginInt = endInt;
		endInt += INT_SIZE;
	}

	while (simTime >= endInt)
	{
		timeBusy = endInt - max(begTime, beginInt);
		percBusy = timeBusy/INT_SIZE;
		stats.incUtil(type, i, percBusy);
		stats.incAvgServiceTime(type, i++, timeBusy);
//		cout << "\t\t timeBusy(" << beginInt << ", " << endInt << "):  " << timeBusy << endl;
		beginInt = endInt;
		endInt += INT_SIZE;
	}
	
	timeBusy = simTime - max(begTime, beginInt);
	percBusy = timeBusy/INT_SIZE;
	stats.incUtil(type, i, percBusy);
	stats.incAvgServiceTime(type, i, timeBusy);
//	cout << "\t\t timeBusy(" << beginInt << ", " << endInt << "):  " << timeBusy << endl;
	
//	Update state and stats
	
	if (DEBUG) cout << "\t Task departing at " << simTime << endl;
	op.makeIdle();
	
	stats.incAvgWaitTime(type, i, begTime - arrTime);
	stats.incNumTasksOut(type, i, 1);
	
	return;
}

#endif