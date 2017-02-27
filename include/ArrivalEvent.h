/****************************************************************************
*																			*
*	File:		ArrivalEvent.h										    	*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the ArrivalEvent class.	   				*
*																			*
****************************************************************************/

#ifndef ARRIVALEVENT_H
#define ARRIVALEVENT_H

#include <iostream>
#include <string>
#include "TaskEvent.h"
// #include "../DateTime.h"

using namespace std;

// class Task;
// class Agent;

/****************************************************************************
*																			*
*	Definition of ArrivalEvent class		     						    *
*																			*
****************************************************************************/

class ArrivalEvent : public TaskEvent
{
//	Public member functions

	public:

    //  Constructor

		ArrivalEvent(DateTime time, Task* task); //, Agent& agent);

	//	Inspectors

	//	Other member functions

		void process();
		void output(ostream& out) const;
};

//	Operators

ostream& operator<<(ostream& out, const ArrivalEvent& e);

#endif
