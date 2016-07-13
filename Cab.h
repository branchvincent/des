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
#include "Operator.h"
#include "Statistics.h"

using namespace std;
using namespace cnsts;

// Type definitions

typedef priority_queue<Task*,vector<Task*>,decltype(&comparePriority)> Queue;

/****************************************************************************
*																			*
*	Definition of Cab class                                                 *
*																			*
****************************************************************************/

class Cab
{
//	Public member functions
	
	public:
	
	//	Constructor
		
        Cab(Statistics* sts) : sharedQueue(), eng(sts, sharedQueue), cond(sts, sharedQueue), stats(sts) {}
	
	// 	Inspector
		
		bool isBusy() const {return cond.isBusy() || eng.isBusy();}
		Task* getNextDepature();
        float getNextDeptTime();
		
	// 	Mutators
		
        void processArrival(Task* task);
        void addTask(Task* task);
        void addSharedTask(Task* task) {eng.addSharedTask(task); cond.addSharedTask(task);}
		void processDepature(Task* task);
        void clear();

//	Data members

	private:
        Queue sharedQueue;
        Operator eng;
		Operator cond;
		Statistics* stats;
};

//ostream& operator<<(ostream& out, const Queue& q) {q.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	getNextDepature												*
*																			*
*	Purpose:	To get the task with the soonest depature					*
*																			*
****************************************************************************/

Task* Cab::getNextDepature()
{
//	Get the current tasks

	Task* condTask = cond.getCurrTask();
	Task* engTask = eng.getCurrTask();
    float condDep = cond.getDepTime();
	float engDep = eng.getDepTime();
	
//	Return the task with the soonest depature

	if (condDep <= engDep && condDep != -1)
		return condTask;
	else
		return engTask;
}

/****************************************************************************
*																			*
*	Function:	getNextDeptTime                                             *
*																			*
*	Purpose:	To get the depature time for the next task 					*
*																			*
****************************************************************************/

float Cab::getNextDeptTime()
{
//  Get departing task
    
    Task* task = getNextDepature();
    
//  Get depature time
    
    if (task != NULL)
        return task->getDepTime();
    else
        return -1;
}

/****************************************************************************
*																			*
*	Function:	processArrival												*
*																			*
*	Purpose:	To process a task arrival								 	*
*																			*
****************************************************************************/

void Cab::processArrival(Task* task)
{	
//	Get task attributes
	
	float arrTime = task->getArrTime();
	int type = task->getType();
    int timeInt = arrTime/INT_SIZE;

//	Update state and stats

	if (DEBUG_ON) cout << "\t Task arriving at " << arrTime << endl;
    addTask(task);
	stats->incNumTasksIn(type, timeInt, 1);
    
	return;
}

/****************************************************************************
*																			*
*	Function:	addTask														*
*																			*
*	Purpose:	To add the specified task to its respective queue			*
*																			*
****************************************************************************/

void Cab::addTask(Task* task)
{
    int opNum = task->getOpNum();
    
    if (opNum == 0)
        eng.addTask(task);
    else if (opNum == 1)
        cond.addTask(task);
    else
        addSharedTask(task);
    
    return;
}

/****************************************************************************
*																			*
*	Function:	processDepature												*
*																			*
*	Purpose:	To process the task depature                                *
*																			*
****************************************************************************/

void Cab::processDepature(Task* task)
{
    if (task == cond.getCurrTask())
        cond.processDepature(task);
    else
        eng.processDepature(task);
    
//	stats->incAvgWaitTime(task->getType(), i, task->getWaitTime());
//    stats->incNumTasksOut(task->getType(), i, 1);

	return;
}

/****************************************************************************
*																			*
*	Function:	clear                                                       *
*																			*
*	Purpose:	To clear the cab of all tasks                               *
*																			*
****************************************************************************/

void Cab::clear()
{
//  Clear operators
    
    cond.clear();
    eng.clear();
    
//  Clear shared queue
    
    while (!sharedQueue.empty())
        sharedQueue.pop();
    
    return;
}

#endif