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
#include "Utility.h"

using namespace std;

vector<string> valid_types = {"arrival", "departure"};

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

		Event(string type, tm time, Task& task, Agent& agent);

	//	Inspectors


	//	Other member functions

		void process();
		bool before(const Event& event) {return time < event.time;}
		void output(ostream& out) const;

//  Private member members

    private:


//	Data members

	private:
		string type;
        time_t time;
		Task task;
		Agent agent;
};

//	Operators

ostream& operator<<(ostream& out, const Event& e) {e.output(out); return out;}
bool operator<(const Event& e1, const Event& e2) {return e1.before(e2);}
bool operator>(const Event& e1, const Event& e2) {return !e1.before(e2);}

/****************************************************************************
*																			*
*	Function:	Event       												*
*																			*
*	Purpose:	To construct an event                                       *
*																			*
****************************************************************************/

Event::Event(string type, tm time, Task& task, Agent& agent) : type(type), time(time), agent(agent)
{
	ASSERT(util::contains(valid_types, type), "Invalid event type");
}

/****************************************************************************
*																			*
*	Function:	process       												*
*																			*
*	Purpose:	To process an event                                       	*
*																			*
****************************************************************************/

void Event::process()
{
	if (type == "arrival")
	{
		task.arrive(time);
	}
	else if (type == "departure")
	{
		task.finish(time);
	}
}

/****************************************************************************
*																			*
*	Function:	output       												*
*																			*
*	Purpose:	To output an event                                       	*
*																			*
****************************************************************************/

void Event::output(ostream& out) const
{
	out << "Type: " << type << endl;
	out << "Time: " << time << endl;
	out << "Agent: " << agent << endl;
}

#endif
