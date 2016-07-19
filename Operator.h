/****************************************************************************
*																			*
*	File:		Operator.h													*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jun 9, 2016													*
*																			*
*	Purpose:	This file defines the Operator class.						*
*																			*
****************************************************************************/

#ifndef OPERATOR_H
#define OPERATOR_H

#include <iostream>
#include <string>
#include <queue>
#include "Task.h"
#include "Operator.h"
#include "Statistics.h"

using namespace std;
using namespace cnsts;

//	Functions and definitions

bool cmpPrty(Task* t1, Task* t2) 
{
	if (t1->getPriority() == t2->getPriority())
		return t1->getExpTime() > t2->getExpTime();
    else
		return t1->getPriority() < t2->getPriority();
}

typedef priority_queue<Task*,vector<Task*>,decltype(&cmpPrty)> Queue;

/****************************************************************************
*																			*
*	Definition of Operator class											*
*																			*
****************************************************************************/

//  Put percShared into this class (varies by operator)

class Operator
{
//	Public member functions

	public:
		
	//	Constructor
	
        Operator(Statistics& sts, Queue& sharedQ) :
            currTask(NULL),
            taskQueue(&cmpPrty),
            sharedQueue(sharedQ),
            sharedStats(sts),
            stats() {}
		
	//	Inspectors

        bool isIdle() const {return currTask == NULL;}
		bool isBusy() const {return !isIdle();}
        int queueSize() const {return taskQueue.size();}
//		bool isQueueEmpty() const {return taskQueue.empty();}
//		int tasksLeft() const {return taskQueue.size();}
//		Task* getTop() {return taskQueue.top();}
		Task* getCurrTask() {return currTask;}
        float getDepTime();
        bool needToIntrp(Queue& queue);
		
	//	Mutators
    
		void procArr(Task* task);
		void procIntrp(float currTime);  //, Queue &queue
		void procDep(Task* task);
        void servNextTask(float currTime);
        void endRep();
				
	//	Other member functions

        void output(ostream& out) const {out << stats << endl;}

//  Private member functions
    
    private:
        float getFatigueFactor(float time) {return 1 + (time/60 * 0.01);}
        Task* getNextTask();
        bool currTaskExp();
        void procExp(float currTime);
        void updateUtil(Task* task, float currTime);

//	Data members

	private:
//        string name;
		Task* currTask;             // current task
		Queue taskQueue;            // task queue
        Queue& sharedQueue;         // shared queue
		Statistics& sharedStats;	// shared stats
        Statistics stats;           // local stats
};

//	Operators

ostream& operator<<(ostream& out, const Operator& op) {op.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	getDepTime													*
*																			*
*	Purpose:	To get the depature time of the current task				*
*																			*
****************************************************************************/

float Operator::getDepTime() 
{
	if (isBusy())
		return currTask->getDepTime();
	else
		return INFINITY;
}

/****************************************************************************
*																			*
*	Function:	needToIntrp                                                 *
*																			*
*	Purpose:	To determine if the current task needs to be interrupted by *
*               by the specified task                                       *
*																			*
****************************************************************************/

bool Operator::needToIntrp(Queue& queue)
{
//    cout << "isBusy = " << isBusy() << endl;
//    cout << "taskQueue.size() = " << taskQueue.size() << endl;
//    cout << "currTask = " << *currTask << endl;
//    cout << "taskQueue.top() = " << *taskQueue.top() << endl;
    
    if (isBusy() && queue.size() > 0)
        return cmpPrty(currTask, queue.top());
    else
        return false;
}

/****************************************************************************
*																			*
*	Function:	procArr                                                     *
*																			*
*	Purpose:	To enqueue the specified task								*
*																			*
****************************************************************************/

void Operator::procArr(Task* task)
{
//	Enqueue task
    
    taskQueue.push(task);

//  Get task attributes
    
    float currTime = task->getArrTime();
    int type = task->getType();
    int timeInt = currTime/INT_SIZE;
    task->setQueTime(currTime);
    
//  Update stats
    
    stats.incNumTasksIn(type, timeInt, 1);
    
//	Service next task, if idle
    
    if (isIdle())
        servNextTask(currTime);
    
//  Interrupt current task, if applicable
    
    else if (needToIntrp(taskQueue)) 
        procIntrp(currTime);

	return;
}

/****************************************************************************
*																			*
*	Function:	processIntrp												*
*																			*
*	Purpose:	To process an interruption of the current task              *
*																			*
****************************************************************************/

void Operator::procIntrp(float currTime)
{
//  Check that the operator is busy
    
    if (isIdle())
    {
        cerr << "Error: Cannot process task interruption. Exiting..." << endl;
        exit(1);
    }
    
    if (DEBUG_ON) cout << "\t\t Task interrupted at " << currTime << endl; //" " << *currTask << endl;
    
//	Update stats
    
    updateUtil(currTask, currTime);
    float depTime = currTask->getDepTime();
    currTask->setSerLeft(depTime - currTime);
    currTask->setDepTime(INFINITY);
    currTask->setQueTime(currTime);

//	Add current task to queue and service next task
    
//    float percLeft = currTask->getPercLeft();
//    float percAllowed = currTask->getPercAllowed();
//
//    if (percLeft <= percAllowed)
//    {
//        sharedQueue.push(currTask);
//        currTask->setOpNum(2);
//    }
//    else
        taskQueue.push(currTask);
    
//  Service next task
    
    currTask = NULL;
    servNextTask(currTime);
    
    return;
}

/****************************************************************************
*																			*
*	Function:	procDep                                                     *
*																			*
*	Purpose:	To process a task depature								 	*
*																			*
****************************************************************************/

void Operator::procDep(Task* task)
{
//	Get task attributes
    
    float depTime = task->getDepTime();
    float begTime = task->getBegTime();
    int type = task->getType();
    int timeInt = begTime/INT_SIZE;

//	Update stats
    
    if (DEBUG_ON) cout << "\t Task departing at " << depTime << endl;
    updateUtil(task, depTime);
    stats.incNumTasksOut(type, timeInt, 1);

//  Start next task, if applicable
    
    currTask = NULL;
    servNextTask(depTime);

    return;
}

/****************************************************************************
*																			*
*	Function:	endRep														*
*																			*
*	Purpose:	To end the current replication                              *
*																			*
****************************************************************************/

void Operator::endRep()
{
//  Update stats
    
    stats.endRep();
    
//  Clear current task
    
    currTask = NULL;
    
//  Clear queue
    
    while (!taskQueue.empty())
        taskQueue.pop();
    
    return;
}

/****************************************************************************
*																			*
*	Function:	output														*
*																			*
*	Purpose:	To output an operator										*
*																			*
****************************************************************************/

//void Operator::output(ostream& out) const
//{
////  Output operator's status and number of enqueued tasks
//    
//    if (currTask != NULL)
//        cout << "Operator is busy until " << currTask->getDepTime();
//    else
//        cout << "Operator is not busy";
//    
//    cout << " and has " << taskQueue.size() << " tasks in queue." << endl;
//    
////  Output queue
//    
//    cout << "Queue = {" << endl;
//    
//    Queue tmpQ = taskQueue;
//    
//    while (!tmpQ.empty())
//    {
//        cout << *tmpQ.top() << endl;
//        tmpQ.pop();
//    }
//    
//    cout << "}" << endl;
//    
//    return;
//}

/****************************************************************************
*																			*
*	Function:	getNextTask                                                 *
*																			*
*	Purpose:	To get the next task to be serviced                         *
*																			*
****************************************************************************/

Task* Operator::getNextTask()
{
//  Initialize variable
    
    Task* nextTask;
    
//  Compare the next two tasks
    
    if (!taskQueue.empty() && !sharedQueue.empty())
    {
        Task* myTask = taskQueue.top();
        Task* sharedTask = sharedQueue.top();
        
        if (cmpPrty(myTask, sharedTask))
        {
            nextTask = sharedTask;
            sharedQueue.pop();
        }
        else
        {
            nextTask = myTask;
            taskQueue.pop();
        }
    }
    else if (!taskQueue.empty())
    {
        nextTask = taskQueue.top();
        taskQueue.pop();
    }
    else if (!sharedQueue.empty())
    {
        nextTask = sharedQueue.top();
        sharedQueue.pop();
    }
    else
    {
        cerr << "Error: Cannot access next task. Exiting..." << endl;
        exit(1);
    }
    
    return nextTask;
}

/****************************************************************************
*																			*
*	Function:	servNextTask												*
*																			*
*	Purpose:	To service the next task in the queue, if applicable		*
*																			*
****************************************************************************/

// Bug here?

void Operator::servNextTask(float currTime)
{
//  Check that a task can be serviced
    
    if (!taskQueue.empty())
//	if (!taskQueue.empty() && !sharedQueue.empty())
	{
	//	Get next task
        
        if (DEBUG_ON) cout << "\t Task starting at " << currTime << endl;
        
        currTask = taskQueue.top();
        taskQueue.pop();
        
//        currTask = getNextTask();
        currTask->setBegTime(currTime);
       
//        cout << "\t\t currTask =  " << *currTask << endl;
//        if (taskQueue.size() > 0)
//            cout << "\t\t taskQueue.top = " << *taskQueue.top() << endl;
//        if (sharedQueue.size() > 0)
//            cout << "\t\t sharedQueue.top = " << *sharedQueue.top() << endl;
        
	//	Account for fatigue, if applicable
		
		float serTime = currTask->getSerLeft();
        
		if (FATIGUE_ON)
		{
			serTime *= getFatigueFactor(currTime);
//			currTask->setSerTime(serTime);          //  error: set time left
            currTask->setSerLeft(serTime);
            serTime = currTask->getSerLeft();
		}
        
    //  Set depature time
        
        float depTime = currTime + serTime;
        currTask->setDepTime(depTime);
    
    //  Update stats
        
        int timeInt = currTime/INT_SIZE;
        int type = currTask->getType();
        float waitTime = currTime - currTask->getQueTime();
        stats.incAvgWaitTime(type, timeInt, waitTime);
        sharedStats.incAvgWaitTime(type, timeInt, waitTime);

    //	Check to see if task expired
        
        if (currTaskExp())
            procExp(currTime);
    }
		
	return;
}

/****************************************************************************
*																			*
*	Function:	currTaskExp                                                 *
*																			*
*	Purpose:	To check if the current task has expired                    *
*																			*
****************************************************************************/

bool Operator::currTaskExp()
{
//  Get task attributes
    
    float depTime = currTask->getDepTime();
    float expTime = currTask->getExpTime();
    
//  Check if depature time has been set
    
    if (isinf(depTime))
    {
        cerr << "Error: Current task has not started. Exiting..." << endl;
        exit(1);
    }
    
//  Check for expiration
    
    if (expTime < depTime)
        return true;
    else
        return false;
}

/****************************************************************************
*																			*
*	Function:	procExp                                                     *
*																			*
*	Purpose:	To process a task expiration                                *
*																			*
****************************************************************************/

void Operator::procExp(float currTime)
{
    if (DEBUG_ON) cout << "\t\t Task expired at " << currTime << endl;

//  Get task attributes and update stats
    
    int type = currTask->getType();
    int timeInt = currTime/INT_SIZE;
    stats.incNumTasksExp(type, timeInt, 1);
    sharedStats.incNumTasksExp(type, timeInt, 1);

//  Start next task
    
    currTask = NULL;
    servNextTask(currTime);
    
    return;
}

/****************************************************************************
*																			*
*	Function:	updateUtil													*
*																			*
*	Purpose:	To update the utilization									*
*																			*
****************************************************************************/

//  Fix wait time
//  change to updatestat and seed each array here (or implement in stats class)

void Operator::updateUtil(Task* task, float currTime)
{
//	Get task attributes

    float begTime = task->getBegTime();
    int type = task->getType();
		
//	Get interval times and update time
	
    int timeInt = begTime/INT_SIZE;
	float beginInt = timeInt * INT_SIZE;
	float endInt = beginInt + INT_SIZE;
	float timeBusy = 0;
	float percBusy = 0;
 
//	Record utilization

	while (currTime >= endInt)
	{
		timeBusy = endInt - max(begTime, beginInt);
		percBusy = timeBusy/INT_SIZE;
		stats.incUtil(type, timeInt, percBusy);
		stats.incAvgServiceTime(type, timeInt, timeBusy);
        sharedStats.incAvgServiceTime(type, timeInt++, timeBusy);
        
        if (timeBusy < 0)
        {
            cout << "NEG VALUE: timeBusy = " << timeBusy << endl;
            cout << "\t task = " << *task << endl;
        }
		
        beginInt = endInt;
		endInt += INT_SIZE;
	}
	
	timeBusy = currTime - max(begTime, beginInt);
	percBusy = timeBusy/INT_SIZE;
	stats.incUtil(type, timeInt, percBusy);
	stats.incAvgServiceTime(type, timeInt, timeBusy);
    sharedStats.incAvgServiceTime(type, timeInt, timeBusy);

    if (timeBusy < 0)
    {
        cout << "NEG VALUE: timeBusy = " << timeBusy << endl;
        cout << "\t task = " << *task << endl;
    }
    
	return;
}

#endif