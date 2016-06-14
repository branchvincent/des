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

bool priorityComparison (Task* t1, Task* t2) 
	{return t1->getPriority() < t2->getPriority();}

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
	
		Operator() : busy(), depTime(-1), taskQueue() {}
		
	//	Inspectors

		bool isBusy() const {return busy;}
		bool& isBusy() {return busy;}
		bool isQueueEmpty() const {return taskQueue.empty();}
		float getDepTime() const {return depTime;}
		float& getDepTime() {return depTime;}
		Task* getCurrTask() {return taskQueue.front();} 
		
	//	Mutators
	
		void makeBusy(int t) {busy = true; depTime = t;}
		void makeFree() {busy = false; taskQueue.pop(); startNextTask(depTime);}
		void setDepTime(int t) {depTime = t;}
		void addTask(Task* task) 
			{taskQueue.push(task); if (!busy) startNextTask(task->getArrTime());}
		void startNextTask(float startTime);
				
	//	Other member functions

		void output(ostream& out) const;

//	Data members

	private:
//		vector<Task*> currTasks;	// current tasks
		bool busy;
		float depTime;				// task depature time	
		queue<Task*> taskQueue;		// task queue
};

//	Operators

ostream& operator<<(ostream& out, const Operator op) {op.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	output														*
*																			*
*	Purpose:	To output an operator										*
*																			*
****************************************************************************/

void Operator::output(ostream& out) const 
{
	if (busy)
		cout << "Operator is busy until ";
	else
		cout << "Operator is not busy until ";
	
	cout << depTime << " and has " << taskQueue.size() << " tasks in queue." << endl;  
	
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
		cout << "Task starting at " << startTime << endl;
		Task* nextTask = taskQueue.front();
		busy = true;
		depTime = startTime + nextTask->getSerTime();
	}
	else
		depTime = -1;
		
	return;
}

#endif