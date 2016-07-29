/****************************************************************************
*																			*
*	File:		Supervisor.h												*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jul 11, 2016												*
*																			*
*	Purpose:	This file defines the Supervisor class. 					*
*																			*
****************************************************************************/

#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include <iostream>
#include <list>
#include <queue>
#include "Task.h"
#include "Operator.h"
#include "Statistics.h"
#include <Python/Python.h>

using namespace std;
using namespace params;

// Type definitions

//bool cmpPrty2(Task* t1, Task* t2)
//{
//    if (t1->getPriority() == t2->getPriority())
//        return t1->getExpTime() > t2->getExpTime();
//    else
//        return t1->getPriority() < t2->getPriority();
//}
//
//typedef priority_queue<Task*,vector<Task*>,decltype(&cmpPrty)> Queue2;

/****************************************************************************
*																			*
*	Definition of Supervisor class                                          *
*																			*
****************************************************************************/

//  Notes
//  - Shared task to op with current lowest priority
//  - Add num_op and names
//  - Add fatigue for just human operators
//  - Add shared task ID as a subset

class Supervisor
{
//  Friend class
    
    friend Operator;
    
//	Public member functions
	
	public:
	
	//	Constructor
	
        Supervisor() : stats(), sharedQueue(&cmpPrty), ops{Operator("Engineer", stats, sharedQueue), Operator("Conductor", stats, sharedQueue)} {}

	// 	Inspector
		
        Task* getNextDepature();
        float getNextDeptTime();
		bool isBusy() const {return (ops[0].isBusy() || ops[1].isBusy());}
        bool opIsIdle() {return (ops[0].isIdle() || ops[1].isIdle());}
        Operator& getIdleOp();
        bool needToIntrp() {return (ops[0].needToIntrp(sharedQueue) || ops[1].needToIntrp(sharedQueue));}
	
    // 	Mutators
		
        void procArr(Task* task);
        void procIntrp(float currTime);
		void procDep(Task* task);
        void endRep();
        void plot() {Py_Initialize(); ops[0].plot(); ops[1].plot(); Py_Finalize();}
    
    //  Other member functions
    
        void output(ostream& out) const
            {out << stats << endl << ops[0] << endl << ops[1] << endl;}

//	Data members

	private:
        Statistics stats;
        Queue sharedQueue;
        Operator ops[NUM_OPS];
};

ostream& operator<<(ostream& out, const Supervisor& s) {s.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	getNextDepature												*
*																			*
*	Purpose:	To get the task with the soonest depature					*
*																			*
****************************************************************************/

Task* Supervisor::getNextDepature()
{
//	Initialize variables
    
    float currDepTime;
    float minTime = ops[0].getDepTime();
    int minIndex = 0;
    
//  Get depature time and index of soonest depature
    
    for (int i = 0; i < NUM_OPS; i++)
    {
    //  Get depature time
        
        currDepTime = ops[i].getDepTime();
        
    //  Check for new minimum
        
        if (currDepTime < minTime)
        {
            minTime = currDepTime;
            minIndex = i;
        }
    }

//  Return task with minimum depature time
    
    return ops[minIndex].getCurrTask();
}

/****************************************************************************
*																			*
*	Function:	getNextDeptTime                                             *
*																			*
*	Purpose:	To get the depature time for the next task 					*
*																			*
****************************************************************************/

float Supervisor::getNextDeptTime()
{
//  Get next departing task
    
    Task* task = getNextDepature();
    
//  Get depature time
    
    if (task != NULL)
        return task->getDepTime();
    else
        return INFINITY;
}

/****************************************************************************
*																			*
*	Function:	procArr                                                     *
*																			*
*	Purpose:	To process a task arrival								 	*
*																			*
****************************************************************************/

void Supervisor::procArr(Task* task)
{	
//	Get task attributes
    
	float currTime = task->getArrTime();
    int opNum = task->getOpNum();
    if (DEBUG_ON) cout << "\t Task arriving at " << currTime << endl; //" " << *task << endl;
    
//	Add task to the appropriate queue
    
//    ops[1].procArr(task);

    if (opNum != NUM_OPS)
        ops[opNum].procArr(task);
    else
    {
        sharedQueue.push(task);
    
    //  See operator should service task
        
        cout << "SHARED TASK ARRIVAL" << endl;
        
        for (int i = 0; i < NUM_OPS; i++)
        {
            if (ops[i].isBusy())
                cout << ops[i].getName() << " is busy with " << *(ops[i].getCurrTask()) << endl;
            else
                cout << ops[i].getName() << " is idle." << endl;
        }
        
        if (opIsIdle()) getIdleOp().servNextTask(currTime);
        else if (needToIntrp()) procIntrp(currTime);
    }
//    else
//    {
//        if (ops[0].queueSize() < ops[1].queueSize())
//            ops[0].procArr(task);
//        else
//            ops[1].procArr(task);
//    }


//  Determine if an operator should change behavior
    
//    if (opIsIdle())
//        getIdleOp().servNextTask(currTime);
//    if (needToIntrp())
//        procIntrp(currTime);
//    if (opIsIdle())
//        getIdleOp().servNextTask(currTime);
    
//  Update stat

    int type = task->getType();
    int timeInt = currTime/INT_SIZE;
	stats.incNumTasksIn(type, timeInt, 1);
    
	return;
}

/****************************************************************************
*																			*
*	Function:	getIdleOp                                                   *
*																			*
*	Purpose:	To return the operator that is availabe                     *
*																			*
****************************************************************************/

Operator& Supervisor::getIdleOp()
{
//  Search for idle operator
    
    for (int i = 0; i < NUM_OPS; i++)
        if (ops[i].isIdle())
            return ops[i];
    
//  If not found, return error
    
    cerr << "Error: No idle operator. Exiting..." << endl;
    exit(1);
}

/****************************************************************************
*																			*
*	Function:	procIntrp                                                   *
*																			*
*	Purpose:	To process an interuption for the appropriate operator      *
*																			*
****************************************************************************/

void Supervisor::procIntrp(float currTime)
{
//  Check to interrupt the operator working on the lowest priority
    
    if (ops[0].needToIntrp(sharedQueue) && ops[1].needToIntrp(sharedQueue))
    {
        if (cmpPrty(ops[0].getCurrTask(), ops[1].getCurrTask()))
            ops[0].procIntrp(currTime);
        else
            ops[1].procIntrp(currTime);
    }
    
//  Check to interrupt engineer
    
    else if (ops[0].needToIntrp(sharedQueue))
        ops[0].procIntrp(currTime);
    
//  Check to interrupt conductor
    
    else if (ops[1].needToIntrp(sharedQueue))
        ops[1].procIntrp(currTime);

    else
    {
        cerr << "Error: Cannot interrupt either operator. Exiting..." << endl;
        exit(1);
    }
    
    return;
}

/****************************************************************************
*																			*
*	Function:	procDep                                                     *
*																			*
*	Purpose:	To process the task depature                                *
*																			*
****************************************************************************/

void Supervisor::procDep(Task* task)
{
//  Process depature from appropriate operator
    
    bool taskFound = false;
    
    for (int i = 0; i < NUM_OPS; i++)
        if (task == ops[i].getCurrTask())
        {
            ops[i].procDep(task);
            taskFound = true;
        }
    
//  If task was not found, ouput error
    
    if (!taskFound)
    {
        cerr << "Error: Could not process task depature. Exiting..." << endl;
        exit(1);
    }
    
//  Update stats
    
    int timeInt = task->getDepTime()/INT_SIZE;
    stats.incNumTasksOut(task->getType(), timeInt, 1);

	return;
}

/****************************************************************************
*																			*
*	Function:	endRep                                                      *
*																			*
*	Purpose:	To end the replication                                      *
*																			*
****************************************************************************/

void Supervisor::endRep()
{
//  Update stats
    
    stats.endRep();
    
//  Clear operators
    
    for (int i = 0; i < NUM_OPS; i++)
        ops[i].endRep();
    
//  Clear shared queue
    
    cout << "Ending Rep... sharedQueue.size() = " << sharedQueue.size() << endl;
    while (!sharedQueue.empty())
        sharedQueue.pop();
    
    return;
}

#endif