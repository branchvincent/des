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

using namespace std;
using namespace cnsts;

// Helper functions and definitions

typedef vector<vector<float> > Matrix2D;
typedef vector<Matrix2D> Matrix3D;
bool compareTasks (Task* t1, Task* t2) 
	{return t1->getArrTime() < t2->getArrTime();}

// Global variables

int SEED;
float PROCESS_TIMES[9] = {0};
float TOTAL_TASKS[9] = {0};
float WAIT_TIMES[9] = {0};
Matrix2D RAW_DATA;

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
	
		void getUtil(Matrix2D& data);
		void getStats(float pTimes[], float wTimes[], int tTasks[]);
		void outputUtil(string filePath);
		void outputRaw(string filePath);

	//	Other member functions

		void run();
		void genTasks(int type);
		void runPhase(int& uIndex);
		void processArrival(list<Task*>::iterator& it);
		void processDepature(Task* task, int& i);
	
//	Data members

	private:
		float simTime;				// simulation time
		int phase;					// current phase
		int endTimes[NUM_PHASES];	// phase end times
		list<Task*> taskList;		// task list
		Operator op;				// operators
		Matrix2D util;				// utilization
		vector<float> traffic; 		// traffic levels
};

/****************************************************************************
*																			*
*	Function:	Simulation													*
*																			*
*	Purpose:	To construct a new simulation								*
*																			*
****************************************************************************/

Simulation::Simulation(int t, int sd, vector<float> trafficLevels) : simTime(), phase(), taskList(), op()
{	
//	Check duration of simulation
	
	if (t < 90 || t%30 != 0) 
	{
		cerr << "Error: Invalid simulation time. Exiting..." << endl;
		exit(1);
	}
	
//	Check traffic array
	
	int hours = (t/60. + 0.5);
	if (trafficLevels.size() != hours) 
	{
		cerr << "Error: Invalid traffic array. Exiting..." << endl;
		exit(1);
	}
	

//	Set phase end times and seed

	endTimes[0] = 30;
	endTimes[1] = t - 30;
	endTimes[2] = t;
	SEED = sd;
	
//	Initialize utilization Matrix2D
	
//	NUM_INTS = t/INT_SIZE;
	Matrix2D temp(NUM_INTS, vector<float>(NUM_TASK_TYPES + 2, 0));
	for (int i = 1; i < NUM_INTS; i++)
			temp[i][0] = temp[i-1][0] + INT_SIZE; 
	util = temp;
	
//	Set traffic levels

	traffic = trafficLevels;

//	Set stats

	for (int i = 0; i < NUM_TASK_TYPES; i++)
	{
		PROCESS_TIMES[i] = 0;
		TOTAL_TASKS[i] = 0;
		WAIT_TIMES[i] = 0;
	}
	
//	Raw data

	Matrix2D raw(t, vector<float>(4, 0));
	RAW_DATA = raw;
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

//	Run all phases, tracking the index to utilization Matrix2D 

	int uIndex = 0;
	for (int i = 0; i < 1; i++)
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
	//	Add current task and update stats
	
		tmpList.push_back(task);
		TOTAL_TASKS[type]++;
		
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
//		if (tp != 1 && tp != 3 && tp != 4)
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
			processArrival(it);
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

void Simulation::processArrival(list<Task*>::iterator& it)
{	
//	Update time
	
	Task* task = *it;
	simTime = task->getArrTime();

//	Update state

	if (DEBUG) cout << "\t Task arriving at " << simTime << endl;
	op.addTask(task);
	it++;
	
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
	
	float beginInt = util[i][0];
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
		percBusy = timeBusy/INT_SIZE * 100;
		util[i][type + 1] += percBusy;					// By type
		util[i++][NUM_TASK_TYPES + 1] += percBusy;			// Total
//		cout << "\t\t timeBusy(" << beginInt << ", " << endInt << "):  " << timeBusy << endl;
		beginInt = endInt;
		endInt += INT_SIZE;
	}
	
	timeBusy = simTime - max(begTime, beginInt);
	percBusy = timeBusy/INT_SIZE * 100;
	util[i][type + 1] += percBusy;						// By type
	util[i][NUM_TASK_TYPES + 1] += percBusy;					// Total
//	cout << "\t\t timeBusy(" << beginInt << ", " << endInt << "):  " << timeBusy << endl;
	
//	Update state and stats
	
	if (DEBUG) cout << "\t Task departing at " << simTime << endl;
	op.makeIdle();
	PROCESS_TIMES[type] += serTime;
	WAIT_TIMES[type] += begTime - arrTime;
	
	return;
}

/****************************************************************************
*																			*
*	Function:	outputData													*
*																			*
*	Purpose:	To output the utilization data to the specified filepath 	*
*																			*
****************************************************************************/

void Simulation::outputUtil(string filePath)
{
//	Open output file

	ofstream fout(filePath);
	if (!fout)
	{
		cerr << "Failed to open output file. Exiting...";
		exit(1);
	}
	
//	Output header

	fout << "Time (min),";
	for (int i = 0; i < util[0].size() - 2; i++)
		fout << "Type " << i << ",";
	fout << "Total" << endl;
	
//	Output data

	for (int i = 0; i < util.size(); i++)
	{
		for (int j = 0; j < util[i].size(); j++)
			fout << util[i][j] << ",";
		fout << endl;
	}	
	
	return;
}

/****************************************************************************
*																			*
*	Function:	outputRaw													*
*																			*
*	Purpose:	To output the raw data to the specified filepath 			*
*																			*
****************************************************************************/

void Simulation::outputRaw(string filePath)
{
//	Open output file

	ofstream fout(filePath);
	if (!fout)
	{
		cerr << "Failed to open output file. Exiting...";
		exit(1);
	}
	
//	Output header

	fout << "Time (min),";
	for (int i = 0; i < util[0].size() - 2; i++)
		fout << "Type " << i << ",";
	fout << "Total" << endl;
	
//	Output data

	for (int i = 0; i < util.size(); i++)
	{
		for (int j = 0; j < util[i].size(); j++)
			fout << util[i][j] << ",";
		fout << endl;
	}	
	
	return;
}

/****************************************************************************
*																			*
*	Function:	getUtil														*
*																			*
*	Purpose:	To get the utilization data								 	*
*																			*
****************************************************************************/

void Simulation::getUtil(Matrix2D& data)
{
//	Check Matrix2D size

	if (data.size() != NUM_INTS || data[0].size() != NUM_TASK_TYPES + 2)
		cerr << "Error:  Incompatible Matrix2D size. Exiting..." << endl;

//	Copy data to specified Matrix2D

	for (int i = 0; i < util.size(); i++)
		for (int j = 0; j < util[i].size(); j++)
			data[i][j] = util[i][j];
			
//	Output data

//	cout << "Utilization Data" << endl;
//	
//	cout << "Time \t";
//	for (int i = 0; i < util.size(); i++)
//		cout << "Type " << i << '\t';
//	cout << "Total" << endl;
//	
//	for (int i = 0; i < util.size(); i++)
//	{
//		for (int j = 0; j < util[i].size(); j++)
//			cout << util[i][j] << '\t';
//		cout << endl;
//	}
	
	return;
}

/****************************************************************************
*																			*
*	Function:	getStats													*
*																			*
*	Purpose:	To get the statistics compiled for the simulation			*
*																			*
****************************************************************************/

void Simulation::getStats(float pTimes[], float wTimes[], int tTasks[])
{
//	Copy stats to specified arrays

	for (int i = 0; i < 9; i++)
	{
		if (TOTAL_TASKS[i] != 0)
			pTimes[i] = PROCESS_TIMES[i]/TOTAL_TASKS[i];
		else
			pTimes[i] = 0;
		wTimes[i] = WAIT_TIMES[i];
		tTasks[i] = TOTAL_TASKS[i];
	}

//	Output stats
	
//	cout << "Simulation Statistics" << endl;
//
//	cout << "Processing Times:  \t";
//	for (int j = 0; j < 9; j++)
//		cout << PROCESS_TIMES[j] << '\t';
//	cout << endl;
//
//	cout << "Wait Times:  \t\t";
//	for (int j = 0; j < 9; j++)
//		cout << WAIT_TIMES[j] << '\t';
//	cout << endl;
//
//	cout << "Total Tasks:  \t\t";
//	for (int j = 0; j < 9; j++)
//		cout << TOTAL_TASKS[j] << '\t';
//	cout << endl;
	
	return;
}

#endif