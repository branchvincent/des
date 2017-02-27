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
#include "TaskEvent.h"
// #include "../DateTime.h"

using namespace std;

// class Task;
// class Agent;

/****************************************************************************
*																			*
*	Definition of DepartureEvent class		     						    *
*																			*
****************************************************************************/

class DepartureEvent : public TaskEvent
{
//	Public member functions

	public:

    //  Constructor

		DepartureEvent(DateTime time, Task* task); //, Agent& agent);

	//	Inspectors

	//	Other member functions

		void process();
		void output(ostream& out) const;
};

//	Operators

ostream& operator<<(ostream& out, const DepartureEvent& e);

#endif
