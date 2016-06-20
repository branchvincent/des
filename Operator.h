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

using namespace std;

//	Functions and definitions

bool comparePriority (Task* t1, Task* t2) 
	{return t1->getPriority() > t2->getPriority();}
float getFatigueFactor(float time) 
	{return 1 + (time/60 * 0.01);}
//typedef priority_queue<Task*,vector<Task*>,decltype(&comparePriority)> Queue;


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
	
		Operator() : currTasks(NULL), taskQueue() {} // taskQueue(&comparePriority)
		
	//	Inspectors

		bool isBusy() const {return currTasks != NULL;}
//		bool& isBusy() {return currTasks != NULL;}
		bool isQueueEmpty() const {return taskQueue.empty();}
//		bool& isQueueEmpty() {return taskQueue.empty();}
		int tasksLeft() const {return taskQueue.size();}
//		int& tasksLeft() {return taskQueue.size();}
//		float getDepTime() const {return currTasks->getDepTime();}
//		float& getDepTime() {return currTasks->getDepTime();}
		Task* getCurrTask() {return currTasks;} 
		Task* getTop() {return taskQueue.front();}
		float getDepTime();
		
	//	Mutators
	
		void makeIdle(); 
		void addTask(Task* task);
		void startNextTask(float startTime);
				
	//	Other member functions

		void output(ostream& out) const;

//	Data members

	private:
		Task* currTasks;		// current tasks
		queue<Task*> taskQueue;		// task queue
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
		return currTasks->getDepTime();
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
	if (!taskQueue.empty())
	{
		float depTime = currTasks->getDepTime(); 
		currTasks = NULL; 
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
	taskQueue.push(task); 
	if (currTasks == NULL) 
		startNextTask(task->getArrTime());
		
	return;
}

/****************************************************************************
*																			*
*	Function:	startNextTask												*
*																			*
*	Purpose:	To start the next task in the queue, if applicable			*
*																			*
****************************************************************************/

void Operator::startNextTask(float startTime) 
{
	if (!taskQueue.empty())
	{
	//	Get next task
	
//		cout << "\t Task starting at " << startTime << endl;
//		currTasks = taskQueue.top();
		Task* nextTask = taskQueue.front();
		currTasks = nextTask;
//		taskQueue.pop(); 

	//	Update service and depature time
		
		float serTime = currTasks->getSerTime();
		float fatFactor = getFatigueFactor(startTime);
		serTime *= fatFactor;
		currTasks->setSerTime(serTime);
		currTasks->setDepTime(startTime + serTime);
	}
		
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
	if (currTasks != NULL)
		cout << "Operator is busy until " << currTasks->getDepTime();
	else
		cout << "Operator is not busy";
	
	cout << " and has " << taskQueue.size() << " tasks in queue." << endl;  
	
}

#endif