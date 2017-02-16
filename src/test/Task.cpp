/****************************************************************************
*																			*
*	File:		Task.cpp													*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the Task class.							*
*																			*
****************************************************************************/

#include <iostream>
#include <string>
#include "Task.h"
#include "TaskType.h"
#include "Event.h"
#include "DateTime.h"
#include "Utility.h"

using namespace std;

//  Statuses = premature, waiting, in progress, complete

/****************************************************************************
*																			*
*	Function:	Task														*
*																			*
*	Purpose:	To construct a task											*
*																			*
****************************************************************************/

Task::Task(TaskType& type, int priority, DateTime arrival, float service, DateTime expiration) :
    type(type),
    priority(priority),
    arrival(arrival),
    service(service),
	departure(expiration),
	expiration(expiration),
	wait(0),
    lastEvent(arrival),
	status("premature")
{
//	Check for negatives

	ASSERT(priority >= 0, "Priority cannot be negative");
	ASSERT(arrival >= 0, "Arrival cannot be negative");
	ASSERT(service >= 0, "Service cannot be negative");
	ASSERT(expiration >= 0, "Expiration cannot be negative");
    ASSERT(arrival + service <= expiration, "Task expires too soon");

//	Check for infinites

	// ASSERT(priority < INFINITY, "Priority cannot be infinite");
	// ASSERT(arrival < INFINITY, "Arrival cannot be infinite");
	// ASSERT(service < INFINITY, "Service cannot be infinite");
	// ASSERT(expiration < INFINITY, "Expiration cannot be infinite");
	// ASSERT(arrival + service <= expiration, "Task expires too soon");
}

//  Inspectors

// const TaskType& Task::getType();int Task::getPriority() const {return priority;}
// float Task::getArrival() const {return arrival;}
// float Task::getDepartue() const {return departure;}
// float Task::getExpiration() const {return expiration;}
// float Task::getWaitTime() const {return wait;}

/****************************************************************************
*																			*
*	Function:	getNextEvent												*
*																			*
*	Purpose:	To return the time of the next event						*
*																			*
****************************************************************************/

optional<Event> Task::getEvent()
{
    if (status == "premature")
        return Event("arrival", arrival, *this);
	else if (status == "in progress")
    {
        if (departure < expiration)
            return Event("departure", departure, *this);
        else
            return Event("expiration", expiration, *this);
    }
    return optional<Event>();
}

/****************************************************************************
*																			*
*	Function:	start														*
*																			*
*	Purpose:	To start servicing a task									*
*																			*
****************************************************************************/

void Task::start(DateTime time)
{
	if (status == "waiting")
	{
		resume(time);
	}
	else
	{
		ASSERT(status == "premature" && time >= arrival, "Task cannot be started before arrival");
		wait += time - arrival;
        departure = time + service;
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

void Task::pause(DateTime time)
{
	ASSERT(status == "in progress", "Task not in progress cannot be paused");
	service -= time - lastEvent;
	ASSERT(service > 0, "Paused task has finished");
    departure = expiration;
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

void Task::resume(DateTime time)
{
	ASSERT(status == "waiting", "Task not waiting cannot be resumed");
	wait += time - lastEvent;
    departure = time + service;
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

void Task::finish(DateTime time)
{
	ASSERT(status == "in progress", "Task not in progress cannot be finished");
	service -= time - lastEvent;
	ASSERT(service == 0, "Task has not finished " << service);
	lastEvent = time;
	status = "complete";
	cout << time << ": Finishing task..." << *this << endl;
}

/****************************************************************************
*																			*
*	Function:	expire														*
*																			*
*	Purpose:	To expire a task											*
*																			*
****************************************************************************/

void Task::expire(DateTime time)
{
	ASSERT(time == expiration, "Task has not expired yet");
	ASSERT(status == "in progress" or status == "waiting", "Task not in progress nor waiting cannot expire");

	if (status == "in progress")
		service -= time - lastEvent;
	else if (status == "waiting")
		wait += time - lastEvent;

	ASSERT(service > 0, "Task has actually finished");
    status = "complete";
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
    // cout << "Type: " << type.name << ", ";
	cout << "Priority: " << priority << ", ";
	cout << "Arrival: " << arrival << ", ";
	cout << "Service: " << service <<  ", ";
	cout << "Departure: " << departure << ", ";
	cout << "Expiration: " << expiration;
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

bool Task::arrivesBefore(const Task& task) const {return arrival < task.getArrival();}

//	Operators

ostream& operator<<(ostream& out, const Task& t) {t.output(out); return out;}
bool operator<(const Task& t1, const Task& t2) {return t1.arrivesBefore(t2);}
bool operator>(const Task& t1, const Task& t2) {return !t1.arrivesBefore(t2);}
// bool operator>(const Task& t1, const Task& t2) {return t1.higherPriority(t2);}
// bool operator<(const Task& t1, const Task& t2) {return !t1.higherPriority(t2);}
