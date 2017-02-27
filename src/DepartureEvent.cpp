/****************************************************************************
*																			*
*	File:		DepartureEvent.cpp											*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the DepartureEvent class.	   				*
*																			*
****************************************************************************/

#include <iostream>
#include <string>
#include "DepartureEvent.h"
#include "Task.h"
#include "../lib/EasyLogging.h"
// #include "Agent.h"
// #include "Utility.h"

using namespace std;

/****************************************************************************
*																			*
*	Function:	DepartureEvent       										*
*																			*
*	Purpose:	To construct an event                                       *
*																			*
****************************************************************************/

DepartureEvent::DepartureEvent(DateTime time, Team* team, Task* task) : TeamEvent(time, team), task(task)
{}

/****************************************************************************
*																			*
*	Function:	process       												*
*																			*
*	Purpose:	To process an event                                       	*
*																			*
****************************************************************************/

void DepartureEvent::process(list<Event*> events)
{
	if (task == NULL)
	{
		LOG(ERROR) << "Tried to process null task";
		return;
	}

	task->finish(time);
	Agent* agent = task->agent;
	agent->currTask = NULL;

	list<Event*>::iterator it = events.begin();
	DepartureEvent d = Event(task->departure, team, task);
	while (**it < d) it++;
	events.insert(--it, new DepartureEvent(task->departure, team, task));
}

/****************************************************************************
*																			*
*	Function:	output       												*
*																			*
*	Purpose:	To output an event                                       	*
*																			*
****************************************************************************/

void DepartureEvent::output(ostream& out) const
{
	out << "Departing at " << time;
	// out << "Type: " << type << endl;
	// out << "Time: " << time << endl;
	// out << "Agent: " << agent << endl;
}

//	Operators

ostream& operator<<(ostream& out, const DepartureEvent& e) {e.output(out); return out;}
