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
#include "datetime.h"

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
		// Task();
		Task(int priority, DateTime arrival, float service, DateTime expiration, TaskType& type);

	//	Inspectors

		// const TaskType* type() const {return _type;}
		// const Agent* agent() const {return _agent;}
		// const int& priority() const {return _priority;}
		// const DateTime& arrival() const {return _arrival;}
		// const float& service() const {return _service;}
		// const DateTime& departure() const {return _departure;}
		// const DateTime& expiration() const {return _expiration;}
		// const float& wait() const {return _wait;}
		// // const DateTime& lastEvent() const {return _lastEvent;}
		// const string& status() const {return _status;}

		 TaskType& type() {return _type;}
		 Agent& agent() const {ASSERT(_agent != NULL, "Agent is null"); return *_agent;}
//		 Agent& agent() const {return *_agent;}
		 int priority() {return _priority;}
		 DateTime arrival() {return _arrival;}
		 float service() {return _service;}
		 DateTime departure() {return _departure;}
		 DateTime expiration() {return _expiration;}
		 float wait() {return _wait;}
		// const DateTime& lastEvent() const {return _lastEvent;}
		 string status() {return _status;}

	//	Mutators

		void start(DateTime time);
		void pause(DateTime time);
		void resume(DateTime time);
		void finish(DateTime time);
		void expire(DateTime time);

	//	Other member functions

		void setAgent(Agent* a) {_agent = a;}
		void output(ostream& out) const;
		bool higherPriority(const Task& task) const;
		bool arrivesBefore(const Task& task) const;

//	Data members

	public:
		TaskType& _type;		// type of task
		Agent* _agent;			// current agent
		int _priority;			// priority level
		DateTime _arrival;		// arrival time (sec)
		float _service; 		// service time (sec)
		DateTime _departure;	// depature time (sec)
		DateTime _expiration;	// expiration time (sec)
        float _wait;      		// wait time (sec)
		DateTime _lastEvent;	// time of last event (sec)
		string _status;			// current status
};

//	Operators

ostream& operator<<(ostream& out, const Task& t);
bool operator>(const Task& t1, const Task& t2);
bool operator<(const Task& t1, const Task& t2);

#endif
