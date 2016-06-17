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

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include "Operator.h"
#include "Task.h"
#include <time.h>
#include <algorithm>

using namespace std;

// Helper functions and definitions

typedef vector< vector<float> > Matrix;
bool taskComparison (Task* t1, Task* t2) 
	{return t1->getArrTime() < t2->getArrTime();}

// Global variables

int SEED = 0;
int intSize = 10;
float processTimes[9] = {0};
float totalTasks[9] = {0};
float waitTimes[9] = {0};
bool debug = true;

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
	
		Simulation(int t, int seed);

	//	Other member functions

		void run();
		void genTasks(int type);
		void runPhase(int& i);
		void processArrival(list<Task*>::iterator& it);
		void processDepature(Task* task, int& i);
		void processData(Matrix& busy, int intSize);
		void outputData(string filePath);
		void reportStats();
	
//	Data members

	private:
		float simTime;			// simulation time
		int phase;				// current phase
		int endTimes[3];		// phase end times
		list<Task*> taskList;	// task list
		Operator op;			// operators
		Matrix util;			// utilization
};

/****************************************************************************
*																			*
*	Function:	Simulation													*
*																			*
*	Purpose:	To construct a new simulation								*
*																			*
****************************************************************************/

Simulation::Simulation(int t, int seed) : simTime(), phase(), taskList(), op()
{
//	Check time duration
	
	if (t < 90 || t%10 != 0) 
	{
		cerr << "Error: Simulation time is too short or not a multiple of 10. Exiting..." << endl;
		exit(1);
	}

//	Set phase end times 

	endTimes[0] = 30;
	endTimes[1] = t - 30;
	endTimes[2] = t;
	
//	Initialize utilization matrix
	
	int numInts = t/intSize;
	util(numInts, vector<float>(10,0));
	for (int i = 1; i < numInts; i++)
			util[i][0] = util[i-1][0] + intSize; 

//	Set seed
	
	if (debug) 
		SEED = 0;
	else
		SEED = seed;
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
//	Run Phase 0 and update Phase 1 end time
	
	int j = 0;
	cout << "Beginning simulation..." << endl;
	runPhase(j);
	endTimes[1] = endTimes[2] - 30;

//	Run other phases
	
//	for (int i = 1; i < 3; i++)
//		runPhase(j);
	
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
	Task* task = new Task(type, simTime, rand(), phase);
	float arrTime = task->getArrTime();
	float serTime = task->getSerTime();
	
//	Add tasks to list while time is left

	while (arrTime < endTimes[phase])
	{
	//	Add current task and update stats
	
		tmpList.push_back(task);
		processTimes[type] += serTime;
		totalTasks[type]++;
		
	//	Get next task
	
		task = new Task(type, arrTime, rand(), phase);
		arrTime = task->getArrTime();
		serTime = task->getSerTime();
	}

//	Merge new list with task list

	taskList.merge(tmpList, taskComparison);

	return;
}

/****************************************************************************
*																			*
*	Function:	runPhase													*
*																			*
*	Purpose:	To run the specified phase of the simulation				*
*																			*
****************************************************************************/

void Simulation::runPhase(int& i)
{
//	Generate all task types

	for (int tp = 0; tp < 3; tp++)
		genTasks(tp);

//	debugging

	cout << "Task List " << endl;
	for (list<Task*>::iterator it = taskList.begin(); it != taskList.end(); it++)
		cout << "Task = " << **it << endl;
	cout << endl;

//	Initiliaze variables

	list<Task*>::iterator it = taskList.begin();

	Task* arrTask;
	float arrTime;
	Task* depTask;
	float depTime;
	
	float prevTime = 0;
	
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
			processArrival(it);
		else 
			processDepature(depTask, i);
	}
			
//	Process remaining tasks in the queue

	depTask = op.getCurrTask();
	depTime = op.getDepTime();
	
	while (!op.isQueueEmpty() && depTime <= endTimes[2])
	{
		processDepature(depTask, i);
		
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

void Simulation::processArrival(list<Task*>::iterator& it)
{
cout << "\t Enter arrival." << endl;
	
//	Update time
	
	Task* task = *it;
	simTime = task->getArrTime();

//	Update state

	cout << "\t Task arriving at " << simTime << endl;
	op.addTask(task);
	it++;
	
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
	cout << "\t Enter depature." << endl;	

//	Get task characteristics

	float arrTime = task->getArrTime();
	float depTime = task->getDepTime();
	float serTime = task->getSerTime();
	float begTime = depTime - serTime;
	int type = task->getType();
	
//	Get interval times

	cout << util.size() << endl;
	cout << util[0].size() << endl;
	
	for (int k = 0; k < util.size(); k++) {
		for (int j = 0; j < util[i].size(); j++)
			cout << util[k][j] << " " << endl;
		cout << endl;
	}
	
	float beginInt = util[i][0];
	float endInt = beginInt + intSize;
	
//	Update time
	
	simTime = depTime;
	
//	Record utilization

	int time = 0;
	if (simTime >= endInt)
	{
		time = endInt - max(begTime, beginInt);
		util[i++][type] += time/intSize * 100;
	}
	else 
	{
		time = simTime - max(begTime, beginInt);
		util[i][type] += time/intSize * 100;
	}

//	Update state and stats
	
	cout << "\t Task departing at " << simTime << endl;
	op.makeIdle();
	waitTimes[type] += begTime - arrTime;
	
	return;
}

/****************************************************************************
*																			*
*	Function:	outputData													*
*																			*
*	Purpose:	To output the utilization data to the specified filepath 	*
*																			*
****************************************************************************/

void Simulation::outputData(string filePath)
{
//	Check output file

	ofstream fout(filePath);
	if (!fout)
	{
		cerr << "Failed to open output file. Exiting...";
		exit(1);
	}
	
//	Output header

	fout << "Time (min) " << endl;
	for (int i = 1; i < util[0].size(); i++)
		fout << "Type " << i - 1 << ",";
	
//	Output data

	for (int i = 0; i < util.size(); i++)
	{
		for (int j = 0; j < util[i].size(); i++)
			fout << util[i][j] << ",";
		cout << endl;
	}	
	return;
}

/****************************************************************************
*																			*
*	Function:	reportStats													*
*																			*
*	Purpose:	To report the statistics compiled for the simulation		*
*																			*
****************************************************************************/

void Simulation::reportStats()
{
	for (int i = 0; i < 9; i++)
	{
		cout << "Processing time for Type " << i << " = " << processTimes[i] << endl;
		cout << "Waiting time for Type " << i << " = " << waitTimes[i] << endl;
		cout << "Total task of Type " << i << " = " << totalTasks[i] << endl;
	}
	return;
}

#endif