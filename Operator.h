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

float getFatigueFactor(float time) 
	{return 1 + (time/60 * 0.01);}
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
	
		Operator(Statistics* sts) : currTask(NULL), taskQueue(&comparePriority), stats(sts) {}
		
	//	Inspectors

		bool isBusy() const {return currTask != NULL;}
//		bool& isBusy() {return currTask != NULL;}
		bool isQueueEmpty() const {return taskQueue.empty();}
//		bool& isQueueEmpty() {return taskQueue.empty();}
		int tasksLeft() const {return taskQueue.size();}
//		int& tasksLeft() {return taskQueue.size();}
//		float getDepTime() const {return currTask->getDepTime();}
//		float& getDepTime() {return currTask->getDepTime();}
		Task* getCurrTask() {return currTask;} 
//		Task* getTop() {return taskQueue.front();}
		float getDepTime();
		
	//	Mutators
	
		void makeIdle(); 
		void addTask(Task* task);
		void startNextTask(float currTime);
		void interruptTask(float currTime);
				
	//	Other member functions

		void updateUtil(Task* task, float currTime);
		void output(ostream& out) const;

//	Data members

	private:
		Task* currTask;			// current task
		Queue taskQueue;		// task queue
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
		taskQueue.pop();
		startNextTask(depTime);
	}
		
	return;
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

	if (isBusy() && taskQueue.top() != currTask)
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
	if (!taskQueue.empty())
	{
	//	Get next task
	
		if (DEBUG) cout << "\t Task starting at " << currTime << endl;
		currTask = taskQueue.top();
//		taskQueue.pop(); 

	//	Update service and depature time
		
		float serTime = currTask->getSerTime();
		float fatFactor = getFatigueFactor(currTime);
	
	//	Account for fatigue, if applicable		

		if (FATIGUE_ON)
		{
			serTime *= fatFactor;
			currTask->setSerTime(serTime);
		}
	
	//	Update depature time
	
		float depTime = currTime + serTime;
		
	//	Check to see if task expired
	
		float expTime = currTask->getExpTime();
		int type = currTask->getType();
		
		if (expTime < depTime)
		{
			int i = currTime/INT_SIZE;
			stats->incNumTasksExp(type, i, 1);
			taskQueue.pop();
			if (DEBUG) cout << "\t\t Task expired at " << currTime << endl;
			startNextTask(currTime);
		}
		else
			currTask->setDepTime(depTime);
	}
		
	return;
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
	
	if (DEBUG) cout << "\t\t Task interrupted at " << currTime << endl;
	updateUtil(currTask, currTime);
	
	float depTime = currTask->getDepTime();
	currTask->setSerTime(depTime - currTime);
	currTask->setDepTime(-1);

//	Add current task to queue and start next task

//	taskQueue.push(currTask);
	startNextTask(currTime);
	
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
	float serTime = task->getSerTime();
	float begTime = depTime - serTime;
	int type = task->getType();
		
//	Get interval times and update time
	
	float beginInt = 0;
	float endInt = beginInt + INT_SIZE;
	float timeBusy = 0;
	float percBusy = 0;

//	Record utilization

	int i = 0;
	while (begTime >= endInt)
	{
		i++;
		beginInt = endInt;
		endInt += INT_SIZE;
	}

	while (currTime >= endInt)
	{
		timeBusy = endInt - max(begTime, beginInt);
		percBusy = timeBusy/INT_SIZE;
		stats->incUtil(type, i, percBusy);
		stats->incAvgServiceTime(type, i++, timeBusy);
		beginInt = endInt;
		endInt += INT_SIZE;
	}
	
	timeBusy = currTime - max(begTime, beginInt);
	percBusy = timeBusy/INT_SIZE;
	stats->incUtil(type, i, percBusy);
	stats->incAvgServiceTime(type, i, timeBusy);
	
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