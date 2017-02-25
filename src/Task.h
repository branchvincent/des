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
#include <boost/optional.hpp>
#include "DateTime.h"

using namespace std;
using boost::optional;

class TaskType;
class Event;

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

		Task(TaskType& type, int priority, DateTime arrival, float service, DateTime expiration);

	//	Inspectors

		const TaskType& getType() const {return type;}
		const int& getPriority() const {return priority;}
		const DateTime& getArrival() const {return arrival;}
		const DateTime& getDeparture() const {return departure;}
		const DateTime& getExpiration() const {return expiration;}
		const float& getWaitTime() const {return wait;}
		optional<Event> getEvent();

	//	Mutators

		void start(DateTime time);
		void pause(DateTime time);
		void resume(DateTime time);
		void finish(DateTime time);
		void expire(DateTime time);

	//	Other member functions

		void output(ostream& out) const;
		bool higherPriority(const Task& task) const;
		bool arrivesBefore(const Task& task) const;

//	Data members

	private:
		TaskType& type;			// type
		int priority;			// priority level
		DateTime arrival;		// arrival time (sec)
		float service; 			// service time (sec)
		DateTime departure;		// depature time (sec)
		DateTime expiration;	// expiration time (sec)
        float wait;      		// wait time (sec)
		DateTime lastEvent;		// time of last event (sec)
		string status;			// current status
};

//	Operators

ostream& operator<<(ostream& out, const Task& t);
bool operator>(const Task& t1, const Task& t2);
bool operator<(const Task& t1, const Task& t2);

#endif
