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
#include "Python.h"

using namespace std;
using namespace cnsts;

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

//  Shared task to op with current lowest priority

class Supervisor
{
//  Friend class
    
    friend Operator;
    
//	Public member functions
	
	public:
	
	//	Constructor
		
//        Supervisor(Statistics* sts) : sharedQueue(), eng(sts, sharedQueue),
//                                        con(sts, sharedQueue), stats(sts) {}
	
        Supervisor() : stats(), sharedQueue(&cmpPrty), eng(stats, sharedQueue, "Engineer"), con(stats, sharedQueue, "Conductor") {}

	// 	Inspector
		
        Task* getNextDepature();
        float getNextDeptTime();
		bool isBusy() const {return (eng.isBusy() || con.isBusy());}
        bool opIsIdle() {return (eng.isIdle() || con.isIdle());}
        Operator& getIdleOp();
        bool needToIntrp() {return (eng.needToIntrp(sharedQueue) || con.needToIntrp(sharedQueue));}
	
    // 	Mutators
		
        void procArr(Task* task);
        void procIntrp(float currTime);
		void procDep(Task* task);
        void endRep();
        void plot() {Py_Initialize(); eng.plot(); con.plot(); Py_Finalize();}
    
    //  Other member functions
    
        void output(ostream& out) const
            {out << stats << endl << eng << endl << con << endl;}

//	Data members

	private:
        Statistics stats;
        Queue sharedQueue;
        Operator eng;
		Operator con;
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
//	Get the depature times

    float engDep = eng.getDepTime();
    float conDep = con.getDepTime();
	
//	Return the task with the soonest depature

	if (engDep <= conDep)
        return eng.getCurrTask();
    else
        return con.getCurrTask();
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
    
    if (opNum == 0)
        eng.procArr(task);
    else if (opNum == 1)
        con.procArr(task);
    else
    {
        if (eng.queueSize() < con.queueSize())
            eng.procArr(task);
        else
            con.procArr(task);
    }
//    else
//        sharedQueue.push(task);

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
    if (eng.isIdle())
        return eng;
    
    else if (con.isIdle())
        return con;
    
    else
    {
        cerr << "Error: No idle operator. Exiting..." << endl;
        exit(1);
    }
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
    
    if (eng.needToIntrp(sharedQueue) && con.needToIntrp(sharedQueue))
    {
        if (cmpPrty(eng.getCurrTask(), con.getCurrTask()))
            eng.procIntrp(currTime);
        else
            con.procIntrp(currTime);
    }
    
//  Check to interrupt engineer
    
    else if (eng.needToIntrp(sharedQueue))
        eng.procIntrp(currTime);
    
//  Check to interrupt conductor
    
    else if (con.needToIntrp(sharedQueue))
        con.procIntrp(currTime);

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
    
    if (task == eng.getCurrTask())
        eng.procDep(task);
    else if (task == con.getCurrTask())
        con.procDep(task);
    else
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
    
    con.endRep();
    eng.endRep();
    
//  Clear shared queue
    
    while (!sharedQueue.empty())
        sharedQueue.pop();
    
    return;
}

#endif