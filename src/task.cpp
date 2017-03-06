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
#include "task.h"
#include "tasktype.h"
#include "event.h"
#include "datetime.h"
#include "utility.h"
#include "team.h"
#include "easylogging++.h"

using namespace std;

enum Status {PREMATURE, WAITING, IN_PROGRESS, COMPLETE};

/****************************************************************************
*																			*
*	Function:	Task														*
*																			*
*	Purpose:	To construct a task											*
*																			*
****************************************************************************/

// Task::Task() : _type(NULL), _agent(NULL), _priority(0), _arrival(DateTime()), service(1),
//     departure(DateTime()),
//     expiration(DateTime()),
//     wait(0),
//     lastEvent(arrival),
//     status("premature")
// {}

Task::Task(int priority, DateTime arrival, float service, DateTime expiration, TaskType& type) :
    _type(type),
    _agent(NULL),
    _priority(priority),
    _arrival(arrival),
    _service(service),
    _departure(expiration),
    _expiration(expiration),
	_wait(0),
    _lastEvent(arrival),
	_status("premature")
{}

// Task::Task(TaskType& type, int priority, DateTime arrival, float service, DateTime expiration) :
//     type(type),
//     priority(priority),
//     arrival(arrival),
//     service(service),
// 	departure(expiration),
// 	expiration(expiration),
// 	wait(0),
//     lastEvent(arrival),
// 	status("premature")
// {
// //	Check for negatives
//
// 	ASSERT(priority >= 0, "Priority cannot be negative");
// 	ASSERT(arrival >= 0, "Arrival cannot be negative");
// 	ASSERT(service >= 0, "Service cannot be negative");
// 	ASSERT(expiration >= 0, "Expiration cannot be negative");
//     ASSERT(arrival + service <= expiration, "Task expires too soon " << arrival + service << " "  << expiration);
//
// //	Check for infinites
//
// 	ASSERT(priority < INFINITY, "Priority cannot be infinite");
// 	ASSERT(arrival < INFINITY, "Arrival cannot be infinite");
// 	ASSERT(service < INFINITY, "Service cannot be infinite");
// 	ASSERT(expiration < INFINITY, "Expiration cannot be infinite");
// 	ASSERT(arrival + service <= expiration, "Task expires too soon");
// }

/****************************************************************************
*																			*
*	Function:	getNextEvent												*
*																			*
*	Purpose:	To return the time of the next event						*
*																			*
****************************************************************************/

// optional<Event> Task::getEvent()
// {
//     if (status == "premature")
//         return Event("arrival", arrival, *this);
// 	else if (status == "in progress")
//     {
//         if (departure < expiration)
//             return Event("departure", departure, *this);
//         else
//             return Event("expiration", expiration, *this);
//     }
//     return optional<Event>();
// }

/****************************************************************************
*																			*
*	Function:	start														*
*																			*
*	Purpose:	To start servicing a task									*
*																			*
****************************************************************************/

void Task::start(DateTime time)
{
	if (_status == "waiting")
	{
		resume(time);
	}
	else
	{
        LOG(DEBUG) << time << ": Task " << this << " starting"; //" (ETA " << time+service << ")";
		// ASSERT(status == "premature" && time >= arrival, "Task cannot be started before arrival");
		_wait += time - _arrival;
        _departure = time + _service;
		_lastEvent = time;
		_status = "in progress";
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
    LOG(INFO) << time << ": Task pausing";
	ASSERT(_status == "in progress", "Task not in progress cannot be paused");
	_service -= time - _lastEvent;
	ASSERT(_service > 0, "Paused task has finished");
    _departure = _expiration;
	_lastEvent = time;
	_status = "waiting";
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
    LOG(DEBUG) << time << ": Task resuming";
	ASSERT(_status == "waiting", "Task not waiting cannot be resumed");
	_wait += time - _lastEvent;
    _departure = time + _service;
	_lastEvent = time;
	_status = "in progress";
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
    // LOG(INFO) << time << ": Task finishing";
	LOG_IF(_status != "in progress", ERROR) << "Task not in progress cannot be finished: status = " << _status;
	_service -= time - _lastEvent;
//	ASSERT(service == 0, "Task has not finished " << service);
	LOG_IF(_service >= 1, ERROR) << "Task has not finished: " << _service << " left";
	_lastEvent = time;
	_status = "complete";
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
    LOG(INFO) << time << ": Task expiring";
	ASSERT(time == _expiration, "Task has not expired yet");
	ASSERT(_status == "in progress" or _status == "waiting", "Task not in progress nor waiting cannot expire");

	if (_status == "in progress")
		_service -= time - _lastEvent;
	else if (_status == "waiting")
		_wait += time - _lastEvent;

	ASSERT(_service > 0, "Task has actually finished");
    _status = "complete";
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
	out << "Priority: " << _priority << ", ";
	out << "Arrival: " << _arrival << ", ";
	out << "Service: " << _service <<  ", ";
	out << "Departure: " << _departure << ", ";
	out << "Expiration: " << _expiration;
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
	if (this->_priority == task._priority)
		return this->_expiration < task._expiration;
	else
		return this->_priority > task._priority;
}

bool Task::arrivesBefore(const Task& task) const {return _arrival < task._arrival;}

//	Operators

ostream& operator<<(ostream& out, const Task& t) {t.output(out); return out;}
bool operator<(const Task& t1, const Task& t2) {return t1.arrivesBefore(t2);}
bool operator>(const Task& t1, const Task& t2) {return !t1.arrivesBefore(t2);}
// bool operator>(const Task& t1, const Task& t2) {return t1.higherPriority(t2);}
// bool operator<(const Task& t1, const Task& t2) {return !t1.higherPriority(t2);}
