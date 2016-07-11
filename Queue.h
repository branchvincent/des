/****************************************************************************
*																			*
*	File:		Queue.h														*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jul 6, 2016													*
*																			*
*	Purpose:	This file defines the Queue class. 							*
*																			*
****************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <list>
#include "Task.h"

using namespace std;

class Queue
{
//	Public member functions
	
	public:
	
	//	Constructor
		
		Queue() : mList() {}
	
	// 	Inspector
		
		Task* front() const;
		int size() const {return mList.size();}
		
	// 	Mutators
		
		void push(Task* task) {mList.push_back(task);}
		Task* pop();
		
	//	Facilitators
		
//		void output(ostream& out) const
//		{
//		for (mList<Task*>::iterator it = taskmList.begin(); it != taskmList.end(); it++)
//			cout << **it << endl;
//		}
		
	//	Other
		
//		void makeEmpty() {mList.makeEmpty();}
//		bool isEmpty() {return mList.isEmpty();}	

//	Data members

	private:
		list<Task*> mList;
};

//ostream& operator<<(ostream& out, const Queue& q) {q.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	front														*
*																			*
*	Purpose:	To return the front item in the queue						*
*																			*
****************************************************************************/

Task* Queue::front() const
{
//	Check size

	if (mList.size() == 0) 
	{
		cerr << "Error: Cannot access empty queue. Exiting...";
		exit(1);
	}

//	Return front
	
	return mList.front();
}

/****************************************************************************
*																			*
*	Function:	pop															*
*																			*
*	Purpose:	To remove and return the front item in the queue 			*
*																			*
****************************************************************************/

Task* Queue::pop() 
{
//	Check size

	if (mList.size() == 0) 
	{
		cerr << "Error: Cannot access empty queue. Exiting...";
		exit(1);
	}

//	Get and pop front

	Task* front = mList.front(); 
	mList.pop_front(); 
	
//	Return front
	
	return front;
}

#endif