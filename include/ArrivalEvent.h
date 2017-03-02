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
#include "teamevent.h"
#include "task.h"
// #include "../DateTime.h"

using namespace std;

// class Task;
class Agent;

/****************************************************************************
*																			*
*	Definition of ArrivalEvent class		     						    *
*																			*
****************************************************************************/

class ArrivalEvent : public TeamEvent
{
//	Public member functions

	public:

    //  Constructor

		ArrivalEvent(DateTime time, Team* team, Task* task); //, Agent& agent);

	//	Inspectors

	//	Other member functions

		Agent* chooseAgent(vector<Agent*> subteam);
		void process(list<Event*>& events);
		void output(ostream& out) const;

//	Private data members

	public:
		Task* task;
};

//	Operators

ostream& operator<<(ostream& out, const ArrivalEvent& e);

#endif
