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
#include "DateTime.h"

using namespace std;

class Team;
class TaskType;
class Event;
class Agent;

/****************************************************************************
*																			*
*	Definition of Task class												*
*																			*
****************************************************************************/

class Task
{
//	Friends

	friend class TaskType;
	friend class Team;
	// friend class Agent;

//	Public member functions

	public:

	//	Constructor

		//TODO: add name
		// Task(TaskType& type, int priority, DateTime arrival, float service, DateTime expiration);
		Task();
		Task(int priority, DateTime arrival, float service, DateTime expiration, TaskType* taskType);

	//	Inspectors

		// const TaskType& getType() const {return type;}
		const int& getPriority() const {return priority;}
		const DateTime& getArrival() const {return arrival;}
		const DateTime& getDeparture() const {return departure;}
		const DateTime& getExpiration() const {return expiration;}
		const float& getWaitTime() const {return wait;}

	//	Mutators

		void start(DateTime time);
		void pause(DateTime time);
		void resume(DateTime time);
		void finish(DateTime time);
		void expire(DateTime time);

	//	Other member functions

		void setAgent(Agent* a) {agent = a;}
		void output(ostream& out) const;
		bool higherPriority(const Task& task) const;
		bool arrivesBefore(const Task& task) const;

//	Data members

	public:
		TaskType* taskType;		// type of task
		Agent* agent;			// current agent
		// Team* team;				// team
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
