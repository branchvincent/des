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
#include <random>
#include <cmath>
#include <algorithm>

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

		Task(string type, float priority, float arrival, float service, float expiration);

	//	Inspectors

		// string getType() const {return type;}
		int getPriority() const {return priority;}
		float getArrival() const {return arrival;}
		// float getService() const {return serTime;}
		// float getDepartue() const {return depTime;}
		float getExpiration() const {return expiration;}
        // float get() const {return begTime;}
        // float getQueTime() const {return queTime;}
        // float getSerLeft() const {return serLeft;}

		void start(float time);
		void pause(float time);
		void resume(float time);
		void finish(float time);
		void expire(float time);
		// float getWaitTime();

	//	Mutators

		// void setDepTime(float t) {depTime = t;}
        // void setSerLeft(float t) {serLeft = t;}
        // void setBegTime(float t) {begTime = t;}
        // void setQueTime(float t) {queTime = t;}

	//	Other member functions

		void output(ostream& out) const;
		bool higherPriority(const Task& task) const;
		bool arrivesSooner(const Task& task) const {return arrival < task.getArrival();}

//	Data members

	private:
		string type;		// type
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
*	Purpose:	To construct a task of the specified type					*
*																			*
****************************************************************************/

Task::Task(string type, float priority, float arrival, float service, float expiration) :
    type(type),
    priority(priority),
    arrival(arrival),
    service(service),
	departure(INFINITY),
	expiration(expiration),
	wait(0),
    lastEvent(-1),
	status("premature")
{}
//	if (aTime != -1)
// 	{
// 		arrTime = aTime;
// 	}

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

		cout << "Starting task..." << *this << endl;
	}
}

void Task::pause(float time)
{
	ASSERT(status == "in progress", "Task not in progress cannot be paused");
	service -= time - lastEvent;
	ASSERT(service > 0, "Paused task has finished");
	lastEvent = time;
	status = "waiting";

	cout << "Pausing task..." << *this << endl;
}

void Task::resume(float time)
{
	ASSERT(status == "waiting", "Task not waiting cannot be resumed");
	wait += time - lastEvent;
	lastEvent = time;
	status = "in progress";

	cout << "Resuming task..." << *this << endl;
}

void Task::finish(float time)
{
	ASSERT(status == "in progress", "Task not in progress cannot be finished");
	service -= time - lastEvent;
	ASSERT(service == 0, "Task has not finished");
	lastEvent = time;
	status = "done";

	cout << "Finishing task..." << *this << endl;
}

void Task::expire(float time)
{
	ASSERT(time == expiration, "Task has not expired yet");
	ASSERT(status == "in progress" or status == "waiting", "Task not in progress nor waiting cannot expire");

	if (status == "in progress")
		service -= time - lastEvent;
	else if (status == "waiting")
		wait += time - lastEvent;

	ASSERT(service > 0, "Task has actually finished");

	cout << "Expiring task..." << *this << endl;
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
	cout << "Type " << type << ", ";
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
