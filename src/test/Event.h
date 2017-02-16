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

using namespace std;

class Task;
class Agent;

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

		// Event(string type) : {}
		Event(string type, tm time, Task& task, Agent& agent);
		Event(string type, time_t time, Task& task, Agent& agent);

	//	Inspectors


	//	Other member functions

		void process();
		bool before(const Event& event) const;
		void output(ostream& out) const;

//  Private member members

    private:


//	Data members

	private:
		string type;
        time_t time;
		Task& task;
		Agent& agent;
};

//	Operators

ostream& operator<<(ostream& out, const Event& e);
bool operator<(const Event& e1, const Event& e2);
bool operator>(const Event& e1, const Event& e2);

#endif
