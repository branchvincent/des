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

using namespace std;

// Enumerated type

//enum u = {};
//typedef list<list<int>> util;	
//typedef list<Task*> List;
typedef vector< vector<float> > Matrix;
bool taskComparison (Task* t1, Task* t2) 
	{return t1->getArrTime() < t2->getArrTime();}

// Global variables

int SEED = 0;
float processTimes[9] = {0};
float totalTasks[9] = {0};
float waitTimes[9] = {0};

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
	
		Simulation(int t, int seed) : simTime(0), taskList(), op(), util(), phase()
		{
			if (t < 90) 
			{
				cerr << "Error: Simulation time is too short. Exiting..." << endl;
				exit(1);
			}
			endTimes[0] = 30;
			endTimes[1] = t - 30;
			endTimes[2] = t;
			SEED = seed;
		} 

	//	Other member functions

		void genTasks(int type);
		void setup();
		void runPhase();
		void run();
		void processArrival(Task* task, float arrTime, int i);
		void processDepature(Task* task, float depTime, int i);
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

//	Output list (debugging)

//	cout << "Task List " << type << endl; int i = 0;
//	for (list<Task*>::iterator it = tmpList.begin(); it != tmpList.end(); it++)
//		cout << "Task " << i++ << " = " << **it << endl;
//	cout << endl;

//	Merge new list with task list

	taskList.merge(tmpList, taskComparison);

	return;
}

/****************************************************************************
*																			*
*	Function:	setup														*
*																			*
*	Purpose:	To setup a simulation by generating all tasks				*
*																			*
****************************************************************************/

void Simulation::setup()
{
//	Generate all task and initialize utilization

	for (int i = 0; i < 3; i++)
		genTasks(i);
		
	util.resize(2*taskList.size(), vector<float>(3,0));

//	Output list (debugging)
	
//	cout << "Task List" << endl; int i = 0;
//	for (list<Task*>::iterator it = taskList.begin(); it != taskList.end(); it++)
//		cout << "Task " << i++ << " = " << **it << endl;
//	cout << endl;
	
// 	Test utilization 

//	cout << "Time, " << "wasBusy" << endl;
//	for (int i = 0; i < 2*taskList.size(); i++)
//		cout << util[i][0] << ", " << util[i][1] << endl;

	return;
}

/****************************************************************************
*																			*
*	Function:	runPhase													*
*																			*
*	Purpose:	To run the specified phase of the simulation				*
*																			*
****************************************************************************/

void Simulation::runPhase()
{
//	Generate tasks and initiliaze variables

	setup();
	int i = 0;
	list<Task*>::iterator it = taskList.begin();

	Task* arrTask;
	float arrTime;
	
	Task* depTask;
	float depTime;
	
//	Process all events in the task list
	
	cout << "Beginning Phase " << phase << "." << endl;

	while(it != taskList.end())
	{
	//	Get next arrival
	
		arrTask = *it;
		arrTime = arrTask->getArrTime();
	
	//	Get next depature
	
		depTask = op.getCurrTask();
		if (depTask != NULL)
			depTime = depTask->getDepTime();
		else
			depTime = -1;
			
	//	Process next event

		if (arrTime < depTime || depTime == -1)
		{	
			processArrival(arrTask, arrTime, i++);
			it++;
		}
		else 
			processDepature(depTask, depTime, i++);
	}
			
//	Process remaining tasks in the queue

	depTask = op.getCurrTask();
	depTime = depTask->getDepTime();
	
	while (!op.isQueueEmpty() && depTime <= endTimes[2])
	{
		processDepature(depTask, depTime, i++);
		
		depTask = op.getCurrTask();
		if (depTask != NULL)
			depTime = depTask->getDepTime();
//		else
//			depTime = endTimes[2] + 1;
	}

//	Clear task list for next phase
	
	cout << "Phase " << phase++ << " completed." << endl << endl;

//	Output utilization (debugging)
	
	for (int i = 0; i < 2*taskList.size(); i++)
		if (util[i][0] != -1)
			cout << util[i][0] << ", " << util[i][1] << ", " << util[i][2] << endl;
	taskList.clear();

	return;
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

	cout << "Beginning simulation..." << endl;
	runPhase();
	endTimes[1] = endTimes[2] - 30;
	cout << endl << endTimes[1] << endl;

//	Run other phases
	
	for (int i = 1; i < 3; i++)
		runPhase();
	
	cout << "Simulation completed." << endl;
	
	return;
}


/****************************************************************************
*																			*
*	Function:	processArrival												*
*																			*
*	Purpose:	To process a task arrival								 	*
*																			*
****************************************************************************/

void Simulation::processArrival(Task* task, float arrTime, int i)
{
//	Update time
	
	simTime = arrTime;
		
//	Determine previous state and record utilization

	if (!op.isBusy())
	{
		util[i][0] = simTime; 
		util[i][1] = 0;
		util[i][2] = -1;
	}
	else 
		util[i][0] = -1; 

//	Update state

	cout << "Task arriving at " << simTime << endl;
	op.addTask(task);
	
	return;
}

/****************************************************************************
*																			*
*	Function:	processDepature												*
*																			*
*	Purpose:	To process a task depature								 	*
*																			*
****************************************************************************/

void Simulation::processDepature(Task* task, float depTime, int i)
{
//	Get task characteristics

	float arrTime = task->getArrTime();
	int type = task->getType();
	
//	Update time and record utilization
	
	simTime = depTime;
	util[i][0] = simTime;
	util[i][1] = 1;
	util[i][2] = type;

//	Update state and stats
	
	cout << "Task departing at " << simTime << endl;
	op.makeIdle();
	waitTimes[type] += depTime - arrTime;
	
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
	ofstream fout(filePath);
	if (!fout)
	{
		cerr << "Failed to open output file. Exiting...";
		exit(1);
	}
	
	fout << "Time (s), Utilization, Type" << endl;
	
	for (int i = 0; i < 2*taskList.size(); i++)
		if (util[i][0] != -1)
			fout << util[i][0] << ", " << util[i][1] << ", " << util[i][2] << endl;
		
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