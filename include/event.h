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
#include "datetime.h"

using namespace std;

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

		Event(DateTime time) : time(time) {}

	//	Inspectors

		const DateTime& getTime() const {return time;}

	//	Other member functions

		virtual void process(list<Event*>& events) = 0;
		bool before(const Event& event) const {return time < event.time;};
		bool equals(const Event& event) const {return time == event.time;}
		virtual void output(ostream& out) const = 0;

//	Data members

	public:
        DateTime time;
		// Task& task;
		// Agent& agent;
};

//	Operators

// ostream& operator<<(ostream& out, const Event& e);
inline bool operator==(const Event& e1, const Event& e2) {return e1.equals(e2);}
inline bool operator!=(const Event& e1, const Event& e2) {return !(e1 == e2);}
inline bool operator<(const Event& e1, const Event& e2) {return e1.before(e2);}
inline bool operator>(const Event& e1, const Event& e2) {return e2 < e1;}
inline bool operator<=(const Event& e1, const Event& e2) {return !(e1 > e2);}
inline bool operator>=(const Event& e1, const Event& e2) {return !(e1 < e2);}

#endif
