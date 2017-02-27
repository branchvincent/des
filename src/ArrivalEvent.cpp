/****************************************************************************
*																			*
*	File:		ArrivalEvent.cpp											*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the ArrivalEvent class.	   				*
*																			*
****************************************************************************/

#include <iostream>
#include <string>
#include "ArrivalEvent.h"
#include "Task.h"
#include "../lib/EasyLogging.h"
// #include "Agent.h"
// #include "Utility.h"

using namespace std;

/****************************************************************************
*																			*
*	Function:	ArrivalEvent       											*
*																			*
*	Purpose:	To construct an event                                       *
*																			*
****************************************************************************/

ArrivalEvent::ArrivalEvent(DateTime time, Task* task) : TaskEvent(time, task)
{}

/****************************************************************************
*																			*
*	Function:	process       												*
*																			*
*	Purpose:	To process an event                                       	*
*																			*
****************************************************************************/

void ArrivalEvent::process()
{
	if (task != NULL)
	{
		task->start(time);
		// LOG(INFO) << "Processing task arrival";
	}
	// else
	// 	LOG(WARNING) << "Tried to process null task";
}

/****************************************************************************
*																			*
*	Function:	output       												*
*																			*
*	Purpose:	To output an event                                       	*
*																			*
****************************************************************************/

void ArrivalEvent::output(ostream& out) const
{
	out << "Arriving at " << time;
	// out << "Type: " << type << endl;
	// out << "Time: " << time << endl;
	// out << "Agent: " << agent << endl;
}

//	Operators

ostream& operator<<(ostream& out, const ArrivalEvent& e) {e.output(out); return out;}
