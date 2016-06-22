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

using namespace std;

// Helper functions and definitions

typedef vector< vector<float> > Matrix;
bool compareTasks (Task* t1, Task* t2) 
	{return t1->getArrTime() < t2->getArrTime();}

// Global variables

int seed;
int numInts;
const int intSize = 30;
const int numTypes = 9;
float processTimes[9] = {0};
float totalTasks[9] = {0};
float waitTimes[9] = {0};
bool debug = true;
Matrix rawData;

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
	
		Simulation(int t, int sd);

	//	Inspectors
	
		void getUtil(Matrix& data);
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

Simulation::Simulation(int t, int sd) : simTime(), phase(), taskList(), op()
{	
//	Check duration of simulation
	
	if (t < 90 || t%10 != 0) 
	{
		cerr << "Error: Invalid simulation time. Exiting..." << endl;
		exit(1);
	}

//	Set phase end times and seed

	endTimes[0] = 30;
	endTimes[1] = t - 30;
	endTimes[2] = t;
	seed = sd;
	
//	Initialize utilization matrix
	
	numInts = t/intSize;
	Matrix temp(numInts, vector<float>(numTypes + 2, 0));
	for (int i = 1; i < numInts; i++)
			temp[i][0] = temp[i-1][0] + intSize; 
	util = temp;
	
//	Raw data

	Matrix raw(t, vector<float>(4, 0));
	rawData = raw;
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

//	Run all phases, tracking the index to utilization matrix 

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
	
	srand(seed++);
	list<Task*> tmpList; 
	Task* task = new Task(type, simTime, rand(), phase);
	float arrTime = task->getArrTime();
	float serTime = task->getSerTime();
	
//	Add tasks to list while time is left

	while (arrTime < endTimes[phase])
	{
	//	Add current task and update stats
	
		tmpList.push_back(task);
		totalTasks[type]++;
		
	//	Get next task
	
		task = new Task(type, arrTime, rand(), phase);
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
	
	for (int tp = 0; tp < 9; tp++)
		if (tp != 1 && tp != 3 && tp != 4)
			genTasks(tp);

//	Initiliaze variables

	list<Task*>::iterator it = taskList.begin();
	Task* arrTask;
	float arrTime;
	Task* depTask;
	float depTime;
	
//	Debugging 

	if (debug)
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
//	Get task characteristics

	float arrTime = task->getArrTime();
	float depTime = task->getDepTime();
	float serTime = task->getSerTime();
	float begTime = depTime - serTime;
	int type = task->getType();
	
//	Get interval times and update time
	
	float beginInt = util[i][0];
	float endInt = beginInt + intSize;
	simTime = depTime;
	float timeBusy = 0;
	float percBusy = 0;
	
//	Record utilization

	while (begTime >= endInt)
	{
		i++;
		beginInt = endInt;
		endInt += intSize;
	}

	while (simTime >= endInt)
	{
		timeBusy = endInt - max(begTime, beginInt);
		percBusy = timeBusy/intSize * 100;
		util[i][type + 1] += percBusy;					// By type
		util[i++][numTypes + 1] += percBusy;			// Total
//		cout << "\t\t timeBusy(" << beginInt << ", " << endInt << "):  " << timeBusy << endl;
		beginInt = endInt;
		endInt += intSize;
	}
	
	timeBusy = simTime - max(begTime, beginInt);
	percBusy = timeBusy/intSize * 100;
	util[i][type + 1] += percBusy;						// By type
	util[i][numTypes + 1] += percBusy;					// Total
//	cout << "\t\t timeBusy(" << beginInt << ", " << endInt << "):  " << timeBusy << endl;
	
//	Update state and stats
	
	cout << "\t Task departing at " << simTime << endl;
	op.makeIdle();
	processTimes[type] += serTime;
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

void Simulation::getUtil(Matrix& data)
{
//	Check matrix size

	if (data.size() != numInts || data[0].size() != numTypes + 2)
		cerr << "Error:  Incompatible matrix size. Exiting..." << endl;

//	Copy data to specified matrix

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
		pTimes[i] = processTimes[i];
		wTimes[i] = waitTimes[i];
		tTasks[i] = totalTasks[i];
	}

//	Output stats
	
	cout << "Simulation Statistics" << endl;

	cout << "Processing Times:  \t";
	for (int j = 0; j < 9; j++)
		cout << processTimes[j] << '\t';
	cout << endl;

	cout << "Wait Times:  \t\t";
	for (int j = 0; j < 9; j++)
		cout << waitTimes[j] << '\t';
	cout << endl;

	cout << "Total Tasks:  \t\t";
	for (int j = 0; j < 9; j++)
		cout << totalTasks[j] << '\t';
	cout << endl;
	
	return;
}

#endif