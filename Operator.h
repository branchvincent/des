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

bool comparePriority(Task* t1, Task* t2) 
{
	if (t1->getPriority() == t2->getPriority())
		return t1->getExpTime() > t2->getExpTime();
    else
		return t1->getPriority() < t2->getPriority();
}

float getFatigueFactor(float time) {return 1 + (time/60 * 0.01);}
typedef priority_queue<Task*,vector<Task*>,decltype(&comparePriority)> Queue;

/****************************************************************************
*																			*
*	Definition of Operator class											*
*																			*
****************************************************************************/

class Operator
{
//	Public member functions

	public:
		
	//	Constructor
	
        Operator(Statistics* sts, Queue& sharedQ) : currTask(NULL), taskQueue(&comparePriority), sharedQueue(sharedQ), stats(sts) {}
		
	//	Inspectors

		bool isBusy() const {return currTask != NULL;}
//		bool& isBusy() {return currTask != NULL;}
		bool isQueueEmpty() const {return taskQueue.empty();}
		int tasksLeft() const {return taskQueue.size();}
		Task* getCurrTask() {return currTask;}
		Task* getTop() {return taskQueue.top();}
		float getDepTime();
		
	//	Mutators
	
		void addTask(Task* task);
        void addSharedTask(Task* task);
		void startNextTask(float currTime);
        Task* getNextTask();
		void interruptTask(float currTime);
		void processDepature(Task* task);
        void makeIdle();
        void clear();
				
	//	Other member functions

		void updateUtil(Task* task, float currTime);
		void output(ostream& out) const;

//	Data members

	private:
		Task* currTask;			// current task
		Queue taskQueue;		// task queue
        Queue& sharedQueue;     // shared queue
		Statistics* stats;		// stats
};

//	Operators

ostream& operator<<(ostream& out, const Operator op) {op.output(out); return out;}

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
		return -1;
}

/****************************************************************************
*																			*
*	Function:	addTask														*
*																			*
*	Purpose:	To enqueue the specified task								*
*																			*
****************************************************************************/

void Operator::addTask(Task* task) 
{
//	Enqueue task

	taskQueue.push(task); 
	float currTime = task->getArrTime();
	
//	Start next task, if applicable

//	if (isBusy() && taskQueue.top() != currTask)
	if (isBusy() && comparePriority(currTask, taskQueue.top()))
		interruptTask(currTime);
	if (!isBusy()) 
		startNextTask(currTime);
			
	return;
}

/****************************************************************************
*																			*
*	Function:	addSharedTask												*
*																			*
*	Purpose:	To enqueue the specified shared task						*
*																			*
****************************************************************************/

void Operator::addSharedTask(Task* task)
{
//	Enqueue task
    
    sharedQueue.push(task);
    float currTime = task->getArrTime();
    
//	Start next task, if applicable
    
    if (isBusy() && comparePriority(currTask, sharedQueue.top()))
        interruptTask(currTime);
    if (!isBusy())
        startNextTask(currTime);
    
    return;
}

/****************************************************************************
*																			*
*	Function:	startNextTask												*
*																			*
*	Purpose:	To start the next task in the queue, if applicable			*
*																			*
****************************************************************************/

void Operator::startNextTask(float currTime) 
{
	if (!taskQueue.empty() || !sharedQueue.empty())
	{
	//	Get next task
	
		if (DEBUG_ON) cout << "\t Task starting at " << currTime << endl;
        currTask = getNextTask();
        
	//	Update service
		
		float serTime = currTask->getSerLeft();
	
	//	Account for fatigue, if applicable		

		if (FATIGUE_ON)
		{
			serTime *= getFatigueFactor(currTime);
			currTask->setSerTime(serTime);
		}
        
	//	Check to see if task expired
        
        float depTime = currTime + serTime;
		float expTime = currTask->getExpTime();
		int type = currTask->getType();
        
		if (expTime < depTime)
		{
			int timeInt = currTime/INT_SIZE;
			stats->incNumTasksExp(type, timeInt, 1);
//			taskQueue.pop();
			currTask = NULL;
			if (DEBUG_ON) cout << "\t\t Task expired at " << currTime << endl;
			startNextTask(currTime);
		}
		else
			currTask->setDepTime(depTime);
    }
		
	return;
}

/****************************************************************************
 *																			*
 *	Function:	getNextTask                                                 *
 *																			*
 *	Purpose:	To get the next task			*
 *																			*
 ****************************************************************************/

Task* Operator::getNextTask()
{
    Task* nextTask;
    
//  Compare the next two tasks
    
    if (!taskQueue.empty() && !sharedQueue.empty())
    {
        Task* myTask = taskQueue.top();
        Task* sharedTask = sharedQueue.top();
        
        if (comparePriority(myTask, sharedTask))
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
    else
    {
        nextTask = sharedQueue.top();
        sharedQueue.pop();
    }
    
    return nextTask;
}

/****************************************************************************
*																			*
*	Function:	interruptTask												*
*																			*
*	Purpose:	To 			*
*																			*
****************************************************************************/

void Operator::interruptTask(float currTime) 
{
//	Update current task service time
	
	if (DEBUG_ON) cout << "\t\t Task interrupted at " << currTime << endl;
	updateUtil(currTask, currTime);
	
    float depTime = currTask->getDepTime();
    currTask->setSerLeft(depTime - currTime);
	currTask->setDepTime(-1);

//	Add current task to queue and start next task
    
    float percLeft = currTask->getPercLeft();
    float percShared = currTask->percShared();
    
    if (currTask != NULL)
        cout << "currTask = " << *currTask << endl;
    else
        cout << "Error:  NUll pointer" << endl;
    
    if (sharedQueue.size() != 0)
        cout << "sharTask 1 of " << sharedQueue.size() << " = " << *sharedQueue.top() << endl;
    
//    if (percLeft <= percShared)
        sharedQueue.push(currTask);
//    else
//        taskQueue.push(currTask);
    
    currTask = NULL;
	startNextTask(currTime);
	

//	record how many tasks move back to sharedqueue

	return;
}

/****************************************************************************
*																			*
*	Function:	updateUtil													*
*																			*
*	Purpose:	To update the utilization									*
*																			*
****************************************************************************/

void Operator::updateUtil(Task* task, float currTime)
{
//	Get task characteristics

	float depTime = task->getDepTime();
	float serTime = task->getSerLeft();
	float begTime = depTime - serTime;
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
		stats->incUtil(type, timeInt, percBusy);
		stats->incAvgServiceTime(type, timeInt++, timeBusy);
		beginInt = endInt;
		endInt += INT_SIZE;
	}
	
	timeBusy = currTime - max(begTime, beginInt);
	percBusy = timeBusy/INT_SIZE;
	stats->incUtil(type, timeInt, percBusy);
	stats->incAvgServiceTime(type, timeInt, timeBusy);
	
	return;
}

/****************************************************************************
*																			*
*	Function:	processDepature												*
*																			*
*	Purpose:	To process a task depature								 	*
*																			*
****************************************************************************/

void Operator::processDepature(Task* task)
{
//	Get task characteristics

	float arrTime = task->getArrTime();
	float depTime = task->getDepTime();
	float serTime = task->getSerLeft();
	float begTime = depTime - serTime;
	int type = task->getType();
		
//	Get interval times and update time
	
    int timeInt = begTime/INT_SIZE;
	float beginInt = timeInt * INT_SIZE;
	float endInt = beginInt + INT_SIZE;
	float timeBusy = 0;
	float percBusy = 0;

//	Record utilization

	while (depTime >= endInt)
	{
		timeBusy = endInt - max(begTime, beginInt);
		percBusy = timeBusy/INT_SIZE;
		stats->incUtil(type, timeInt, percBusy);
		stats->incAvgServiceTime(type, timeInt++, timeBusy);
        if (timeBusy < 0) {
            cout << "NEG VALUE: timeBusy = " << timeBusy << endl;
            cout << "\t task = " << *task << endl;}
		beginInt = endInt;
		endInt += INT_SIZE;
	}
	
	timeBusy = depTime - max(begTime, beginInt);
	percBusy = timeBusy/INT_SIZE;
	stats->incUtil(type, timeInt, percBusy);
	stats->incAvgServiceTime(type, timeInt, timeBusy);
    if (timeBusy < 0) {
        cout << "NEG VALUE: timeBusy = " << timeBusy << endl;
        cout << "\t task = " << *task << endl;}
	
//	Update state and stats
	
	if (DEBUG_ON) cout << "\t Task departing at " << depTime << endl;
	makeIdle();
	
	stats->incAvgWaitTime(type, timeInt, begTime - arrTime);
	stats->incNumTasksOut(type, timeInt, 1);
    
    if (begTime - arrTime < 0) {
        cout << "NEG VALUE: waitTime = " << begTime - arrTime << endl;
        cout << "task = " << *task << endl;}
	
//    cout << sharedQueue.size() << endl;
    
	return;
}

/****************************************************************************
*																			*
*	Function:	makeIdle													*
*																			*
*	Purpose:	To finish the current task and move to the next one, if		*
*				applicable													*
*																			*
****************************************************************************/

void Operator::makeIdle()
{
    if (isBusy())
    {
        float depTime = currTask->getDepTime();
        currTask = NULL;
//        taskQueue.pop();
        startNextTask(depTime);
    }
    
    return;
}

/****************************************************************************
*																			*
*	Function:	clear														*
*																			*
*	Purpose:	To clear the operator of all tasks 							*
*																			*
****************************************************************************/

void Operator::clear()
{
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

void Operator::output(ostream& out) const 
{
//	if (currTask != NULL)
//		cout << "Operator is busy until " << currTask->getDepTime();
//	else
//		cout << "Operator is not busy";
//	
//	cout << " and has " << taskQueue.size() << " tasks in queue." << endl;  

	Queue temp = taskQueue;
	
	while (!temp.empty())
	{
		cout << *temp.top() << endl;
		temp.pop();
	}
	
	return;
}

#endif