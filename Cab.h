/****************************************************************************
*																			*
*	File:		Cab.h														*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jul 11, 2016												*
*																			*
*	Purpose:	This file defines the Cab class. 							*
*																			*
****************************************************************************/

#ifndef CAB_H
#define CAB_H

#include <iostream>
#include <list>
#include <queue>
#include "Task.h"

using namespace std;

// Type definitions

typedef priority_queue<Task*,vector<Task*>,decltype(&comparePriority)> Queue;

class Cab
{
//	Public member functions
	
	public:
	
	//	Constructor
		
//		Cab() : con(), eng(), sharedQueue() {}
	
	// 	Inspector
		
		Task* getNextDepature();
		
	// 	Mutators
		
		void makeIdle(); 
		void addTask(Task* task);
		void startNextTask(float currTime);
		void interruptTask(float currTime);
		
	//	Facilitators
		
		
		
	//	Other
		
			

//	Data members

	private:
		Operator cond;
		Operator eng;
		Queue sharedQueue;
};

//ostream& operator<<(ostream& out, const Queue& q) {q.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	getNextDepature												*
*																			*
*	Purpose:	To 						*
*																			*
****************************************************************************/

void Cab::getNextDepature()
{
//	Get the current tasks

	Task* condTask = cond.getCurrTask();
	Task* engTask = eng.getCurrTask();
	
//	Return the next depature

	if (condTask->getDepTime() < engTask->getDepTime())
		return condTask;
	else
		return engTask;
}

/****************************************************************************
*																			*
*	Function:	genTasks													*
*																			*
*	Purpose:	To *
*																			*
****************************************************************************/

void Cab::genTasks(list<Task*>& taskList) // simTime, phase, traffic, endTimes[phase], compareTasks
{
//	For each task type,	

	for (int i = 0; i < NUM_TASKS; i++)
	{
	//	Create first task and temporary list
			
		srand(SEED++);
		list<Task*> tmpList; 
		Task* task = new Task(i, simTime, rand(), phase, traffic);
		float arrTime = task->getArrTime();
		float serTime = task->getSerTime();
		
	//	Add tasks to list while time is left

		while (arrTime < endTimes[phase])
		{
		//	Add current task
		
			tmpList.push_back(task);
			
		//	Get next task
		
			task = new Task(i, arrTime, rand(), phase, traffic);
			arrTime = task->getArrTime();
			serTime = task->getSerTime();
		}

	//	Merge new list with task list

		taskList.merge(tmpList, compareTasks);
	}
	
	return;
}

#endif