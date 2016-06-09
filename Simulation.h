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
#include <string>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <list>
#include "Task.h"
#include "Operator.h"

using namespace std;

// Enumerated type

//enum u = {};

// Global seed array (placeholder)

int seedArr[50];

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
	
		Simulation(int t) : simTime(0), endTime(t), taskList(), op() {}

	//	Other member functions

		void genTasks();
		void run();
	
//	Data members

	private:
		int simTime;			// simulation time
		int endTime;			// end time
		list<Task*> taskList;	// task list
		Operator op;			// operators
		list<list<int>> util;	// utilization
};

/****************************************************************************
*																			*
*	Function:	genTasks													*
*																			*
*	Purpose:	To setup a simulation by generatings tasks					*
*																			*
****************************************************************************/

void Simulation::genTasks()
{
//	Randomly fill seed array

	for (int i = 0; i < 50; i++)
		seedArr[i] = 150*i;
	
//	Create first task

	Task* task = new Task('A', 0, seedArr[0]);
	int arrTime = task->getArrTime();
	int i = 1;
	
//	Add tasks to list while time is left

	while (arrTime < endTime)
	{
		taskList.push_back(task);
		task = new Task('A', arrTime, seedArr[i]);
		arrTime = task->getArrTime();
		i++;
	}
	
//	Output list (debugging purposes)
	
	cout << "Task List" << endl;
	i = 0;
	for (list<Task*>::iterator it = taskList.begin(); it != taskList.end(); it++)
	{
		cout << "Task " << i << " = " << **it;
		i++;
	}
	cout << endl;

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

	genTasks();
	list<Task*>::iterator it = taskList.begin();
	int arrTime;
	int depTime;
	Task* task;
	cout << "Beginning simulation..." << endl;
	
//	Process all events in the list

	while(it != taskList.end())
	{
		task = *it;
		arrTime = task->getArrTime();
		depTime = op.getDepTime();
	
	//	Process arrival, if next event

		if (arrTime < depTime || depTime == -1)
		{
			cout << "Task arriving at " << arrTime << endl;
			op.addTask(task);
			simTime = arrTime;	
			it++;
		}
		
	//	Process depature, if next event
	
		else 
		{
			cout << "Task departing at " << depTime << endl;
			op.makeFree();
			simTime = depTime;
		}
	}
	
//	Ensure operator completes all tasks in queue

	while (!op.isQueueEmpty() || op.isBusy())
	{
		depTime = op.getDepTime();
		cout << "Task departing at " << depTime << endl;
		op.makeFree();
		simTime = depTime;
	}
	
	return;
}

#endif