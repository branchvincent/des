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

DepartureEvent::DepartureEvent(DateTime time, Task* task) : TaskEvent(time, task)
{}

/****************************************************************************
*																			*
*	Function:	process       												*
*																			*
*	Purpose:	To process an event                                       	*
*																			*
****************************************************************************/

void DepartureEvent::process()
{
	if (task != NULL)
		task->finish(time);
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
