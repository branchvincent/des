/****************************************************************************
*																			*
*	File:		DepartureEvent.h										    *
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the DepartureEvent class.	   				*
*																			*
****************************************************************************/

#ifndef DEPARTUREEVENT_H
#define DEPARTUREEVENT_H

#include <iostream>
#include <string>
#include "TeamEvent.h"
// #include "../DateTime.h"
#include "Task.h"

using namespace std;

// class Task;
// class Agent;

/****************************************************************************
*																			*
*	Definition of DepartureEvent class		     						    *
*																			*
****************************************************************************/

class DepartureEvent : public TeamEvent
{
//	Public member functions

	public:

    //  Constructor

		DepartureEvent(DateTime time, Team* team, Task* task); //, Agent& agent);

	//	Inspectors

	//	Other member functions

		void process(list<Event*>& events);
		void output(ostream& out) const;

	public:
		Task* task;
};

//	Operators

ostream& operator<<(ostream& out, const DepartureEvent& e);

#endif
