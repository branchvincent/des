/****************************************************************************
*																			*
*	File:		Event.h												        *
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the Event class.	   					    *
*																			*
****************************************************************************/

#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <string>
#include "DateTime.h"

using namespace std;

// class Task;
// class Agent;

/****************************************************************************
*																			*
*	Definition of Event class		     						            *
*																			*
****************************************************************************/

class Event
{
//	Public member functions

	public:

    //  Constructor

		Event(DateTime time); //, Task& task), Agent& agent);

	//	Inspectors

		const DateTime& getTime() const;

	//	Other member functions

		virtual void process() = 0;
		bool before(const Event& event) const;
		virtual void output(ostream& out) const = 0;

//	Data members

	protected:
        DateTime time;
		// Task& task;
		// Agent& agent;
};

//	Operators

// ostream& operator<<(ostream& out, const Event& e);
bool operator<(const Event& e1, const Event& e2);
bool operator>(const Event& e1, const Event& e2);

#endif
