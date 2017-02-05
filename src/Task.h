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
#include <cmath>
#include "Util.h"

using namespace std;

/****************************************************************************
*																			*
*	Definition of Task class												*
*																			*
****************************************************************************/

class Task
{
//	Public member functions

	public:

	//	Constructor

		Task(string name, float priority, float arrival, float service, float expiration);

	//	Inspectors

		string getName() const {return name;}
		int getPriority() const {return priority;}
		float getArrival() const {return arrival;}
		float getDepartue() const {return departure;}
		float getExpiration() const {return expiration;}
		float getWaitTime() const {return wait;}
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
		bool arrivesSooner(const Task& task) const {return arrival < task.getArrival();}

//	Data members

	private:
		// Agent agent;
		string name;		// name
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

ostream& operator<<(ostream& out, const Task& t) {t.output(out); return out;}
bool operator>(const Task& t1, const Task& t2) {return t1.higherPriority(t2);}
bool operator<(const Task& t1, const Task& t2) {return !t1.higherPriority(t2);}

/****************************************************************************
*																			*
*	Function:	Task														*
*																			*
*	Purpose:	To construct a task											*
*																			*
****************************************************************************/

Task::Task(string name, float priority, float arrival, float service, float expiration) :
    name(name),
    priority(priority),
    arrival(arrival),
    service(service),
	departure(-1),
	expiration(expiration),
	wait(0),
    lastEvent(-1),
	status("premature")
{
//	Check for negatives

	ASSERT(priority >= 0, "Priority cannot be negative");
	ASSERT(arrival >= 0, "Arrival cannot be negative");
	ASSERT(service >= 0, "Service cannot be negative");
	ASSERT(expiration >= 0, "Expiration cannot be negative");

//	Check for infinites

	ASSERT(priority < INFINITY, "Priority cannot be infinite");
	ASSERT(arrival < INFINITY, "Arrival cannot be infinite");
	ASSERT(service < INFINITY, "Service cannot be infinite");
	ASSERT(expiration < INFINITY, "Expiration cannot be infinite");
	ASSERT(arrival + service <= expiration, "Task expires too soon");
}
//	if (aTime != -1)
// 	{
// 		arrTime = aTime;
// 	}

/****************************************************************************
*																			*
*	Function:	getNextEvent												*
*																			*
*	Purpose:	To return the time of the next event						*
*																			*
****************************************************************************/

float Task::getNextEvent() const
{
	if (status == "in progress")
		return min(departure, expiration);
	else
		return INFINITY;
}

/****************************************************************************
*																			*
*	Function:	start														*
*																			*
*	Purpose:	To start servicing a task									*
*																			*
****************************************************************************/

void Task::start(float time)
{
	if (status == "waiting")
	{
		resume(time);
	}
	else
	{
		ASSERT(status == "premature" && time >= arrival, "Task cannot be started before arrival");
		wait += time - arrival;
		lastEvent = time;
		status = "in progress";

		cout << time <<  ": Starting task..." << *this << endl;
	}
}

/****************************************************************************
*																			*
*	Function:	pause														*
*																			*
*	Purpose:	To pause servicing a task									*
*																			*
****************************************************************************/

void Task::pause(float time)
{
	ASSERT(status == "in progress", "Task not in progress cannot be paused");
	service -= time - lastEvent;
	ASSERT(service > 0, "Paused task has finished");
	lastEvent = time;
	status = "waiting";

	cout << time << ": Pausing task..." << *this << endl;
}

/****************************************************************************
*																			*
*	Function:	resume														*
*																			*
*	Purpose:	To resume servicing a task									*
*																			*
****************************************************************************/

void Task::resume(float time)
{
	ASSERT(status == "waiting", "Task not waiting cannot be resumed");
	wait += time - lastEvent;
	lastEvent = time;
	status = "in progress";

	cout << time << ": Resuming task..." << *this << endl;
}

/****************************************************************************
*																			*
*	Function:	finish														*
*																			*
*	Purpose:	To finish servicing a task									*
*																			*
****************************************************************************/

void Task::finish(float time)
{
	ASSERT(status == "in progress", "Task not in progress cannot be finished");
	service -= time - lastEvent;
	ASSERT(service == 0, "Task has not finished " << service);
	lastEvent = time;
	status = "done";

	cout << time << ": Finishing task..." << *this << endl;
}

/****************************************************************************
*																			*
*	Function:	expire														*
*																			*
*	Purpose:	To expire a task											*
*																			*
****************************************************************************/

void Task::expire(float time)
{
	ASSERT(time == expiration, "Task has not expired yet");
	ASSERT(status == "in progress" or status == "waiting", "Task not in progress nor waiting cannot expire");

	if (status == "in progress")
		service -= time - lastEvent;
	else if (status == "waiting")
		wait += time - lastEvent;

	ASSERT(service > 0, "Task has actually finished");

	cout << time << ": Expiring task..." << *this << endl;
}

/****************************************************************************
*																			*
*	Function:	output														*
*																			*
*	Purpose:	To output a task											*
*																			*
****************************************************************************/

void Task::output(ostream& out) const
{
	cout << "Priority: " << priority << ", ";
	cout << "Name " << name << ", ";
	cout << "Arrival " << arrival << ", ";
	cout << "Service " << service <<  ", ";
	cout << "Departure " << departure << ", ";
	cout << "Expiration " << expiration << ")";
}

/****************************************************************************
*																			*
*	Function:	greaterPriority												*
*																			*
*	Purpose:	To return if the specified task is of higher priority		*
*																			*
****************************************************************************/

bool Task::higherPriority(const Task& task) const
{
	if (this->priority == task.getPriority())
		return this->expiration < task.getExpiration();
	else
		return this->priority > task.getPriority();
}

#endif
