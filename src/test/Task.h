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

using namespace std;

class TaskType;

/****************************************************************************
*																			*
*	Definition of Task class												*
*																			*
****************************************************************************/

class Task
{
//	Friends

	friend class TaskType;
	friend class Agent;

//	Public member functions

	public:

	//	Constructor

		Task(TaskType& type, int priority, float arrival, float service, float expiration);

	//	Inspectors

		const TaskType& getType() const {return type;}
		const int& getPriority() const {return priority;}
		const float& getArrival() const {return arrival;}
		const float& getDepartue() const {return departure;}
		const float& getExpiration() const {return expiration;}
		const float& getWaitTime() const {return wait;}
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
		TaskType& type;		// type
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
