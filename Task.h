/****************************************************************************
*																			*
*	File:		Task.h														*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the Task class.							*
*																			*
****************************************************************************/

#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <string>
#include "TaskType.h"

using namespace std;

//class TaskType;

/****************************************************************************
*																			*
*	Definition of Task class												*
*																			*
****************************************************************************/

class Task
{
//	Friends

//	friend class TaskType;

//	Public member functions

	public:

	//	Constructor
	
		Task(int priority, float arrival, float service, float expiration);
//		Task(TaskType& type, int priority, float arrival, float service, float expiration);

	//	Inspectors

//		string getName() const;
		int getPriority() const;
		float getArrival() const;
		float getDepartue() const;
		float getExpiration() const;
		float getWaitTime() const;
		float getNextEvent() const;

	//	Mutators

		void start(float time);
		void pause(float time);
		void resume(float time);
		void finish(float time);
		void expire(float time);

	//	Other member functions

		void output(ostream& out) const;
		bool higherPriority(const Task& task) const;
		bool arrivesSooner(const Task& task) const;

//	Data members

	private:
		TaskType type;		// type
		int priority;		// priority level
		float arrival;		// arrival time (min)
		float service; 		// service time (min)
		float departure;	// depature time (min)
		float expiration;	// expiration time (min)
        float wait;      	// wait time (min)
		float lastEvent;	// time of last event (min)
		string status;		// current status
};

//	Operators

ostream& operator<<(ostream& out, const Task& t);
bool operator>(const Task& t1, const Task& t2);
bool operator<(const Task& t1, const Task& t2);

#endif
