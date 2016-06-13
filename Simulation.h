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
#include <queue>
#include <cstdlib>
#include <ctime>
#include <list>
#include "Task.h"
#include "Operator.h"
#include <vector>

using namespace std;

// Enumerated type

//enum u = {};
//typedef list<list<int>> util;	
//typedef list<Task*> List;
typedef vector< vector<int> > matrix;
bool taskComparison (Task* t1, Task* t2) 
	{return t1->getArrTime() < t2->getArrTime();}

// Global variables

int SEED = 0;
char TYPE[] = {'A','B','C','D','E','F'};

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
	
		Simulation(int t) : simTime(0), endTime(t), taskList(), op(), util() {}

	//	Other member functions

		void genTasks(char type);
		void setup();
		void run();
		void outputData(string filePath);
	
//	Data members

	private:
		int simTime;			// simulation time
		int endTime;			// end time
		list<Task*> taskList;	// task list
		Operator op;			// operators
		matrix util;			// utilization
};

/****************************************************************************
*																			*
*	Function:	genTasks													*
*																			*
*	Purpose:	To generate tasks of the specified type						*
*																			*
****************************************************************************/

void Simulation::genTasks(char type)
{
//	Create first task

	srand(SEED);
	list<Task*> tmpList; 
	Task* task = new Task(type, 0, rand());
	int arrTime = task->getArrTime();
	
//	Add tasks to list while time is left

	while (arrTime < endTime)
	{
		tmpList.push_back(task);
		task = new Task(type, arrTime, rand());
		arrTime = task->getArrTime();
	}
	
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
	for (int i = 0; i < 2; i++)
		genTasks(TYPE[i]);

//	Output list (debugging purposes)
	
	cout << "Task List" << endl; int i = 0;
	for (list<Task*>::iterator it = taskList.begin(); it != taskList.end(); it++)
		cout << "Task " << i++ << " = " << **it;
	cout << endl;
	
// 	Test utilization 

	util.resize(2*taskList.size(), vector<int>(2,0));
//	cout << "Time, " << "wasBusy" << endl;
//	for (int i = 0; i < 2*taskList.size(); i++)
//		cout << util[i][0] << ", " << util[i][1] << endl;

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
//	Generate tasks and initiliaze variables

	setup();
	list<Task*>::iterator it = taskList.begin();
	int arrTime;
	int depTime;
	Task* task;
	cout << "Beginning simulation..." << endl;
	
//	Process all events in the list
	
	int i = 0;											// delete
	while(it != taskList.end())
	{
		task = *it;
		arrTime = task->getArrTime();
		depTime = op.getDepTime();
	
	//	Process arrival, if next event

		if (arrTime < depTime || depTime == -1)
		{
		//	Determine previous state and record utilization
		
			simTime = arrTime;
			
			if (!op.isBusy())
			{
				util[i][0] = simTime; 
				util[i][1] = 0;
			}
			else 
				util[i][0] = -1; 

		//	Update state
		
			cout << "Task arriving at " << simTime << endl;
			op.addTask(task);
			it++;
		}
	//	Process depature, if next event
	
		else 
		{
		//	Record utilization
		
			simTime = depTime;
			util[i][0] = simTime; 
			util[i][1] = 1;
		
		//	Update state
		
			cout << "Task departing at " << simTime << endl;
			op.makeFree();
		}
		i++;										// delete
	}
		
//	Ensure operator completes all tasks in queue

	while (!op.isQueueEmpty() || op.isBusy())
	{
	//	Record utilization
		
		simTime = op.getDepTime();
		util[i][0] = simTime; 
		util[i][1] = 1;
		
	//	Update state
	
		cout << "Task departing at " << simTime << endl;
		op.makeFree();
		i++;
	}
	
	for (int i = 0; i < 2*taskList.size(); i++)
		if (util[i][0] != -1)
			cout << util[i][0] << ", " << util[i][1] << endl;
		
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
		cerr << "Failed to open output file.";
		exit(1);
	}
	
	fout << "Time (s), Utilization" << endl;
	
	for (int i = 0; i < 2*taskList.size(); i++)
		if (util[i][0] != -1)
			fout << util[i][0] << ", " << util[i][1] << endl;
		
	return;
}

#endif