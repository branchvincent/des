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

class Team;
class Agent;
class Task;

/****************************************************************************
*																			*
*	Definition of Event class		     						            *
*																			*
****************************************************************************/

class Event
{
	public:
		Event(DateTime time) : time(time) {}
		virtual void process(list<Event*>& events) = 0;
		bool before(const Event& event) const {return time < event.time;};
		bool equals(const Event& event) const {return time == event.time;}
		virtual void output(ostream& out) const = 0;
	public:
        DateTime time;
};

inline bool operator==(const Event& e1, const Event& e2) {return e1.equals(e2);}
inline bool operator!=(const Event& e1, const Event& e2) {return !(e1 == e2);}
inline bool operator<(const Event& e1, const Event& e2) {return e1.before(e2);}
inline bool operator>(const Event& e1, const Event& e2) {return e2 < e1;}
inline bool operator<=(const Event& e1, const Event& e2) {return !(e1 > e2);}
inline bool operator>=(const Event& e1, const Event& e2) {return !(e1 < e2);}

/****************************************************************************
*																			*
*	Definition of TaskEvent class	     						            *
*																			*
****************************************************************************/

class TaskEvent : public Event
{
	public:
		TaskEvent(DateTime time, Task* task) : Event(time), task(task) {}
	protected:
		Task* task;
};

/****************************************************************************
*																			*
*	Definition of TeamEvent class	     						            *
*																			*
****************************************************************************/

class TeamEvent : public Event
{
	public:
		TeamEvent(DateTime time, Team* team) :  Event(time), team(team) {}
		// Team* getTeam() const {return team;}
	protected:
		Team* team;
};

/****************************************************************************
*																			*
*	Definition of ArrivalEvent class		     						    *
*																			*
****************************************************************************/

class ArrivalEvent : public TeamEvent
{
	public:
		ArrivalEvent(DateTime time, Team* team, Task* task) : TeamEvent(time, team), task(task) {}
		Agent* chooseAgent(vector<Agent*> subteam);
		void process(list<Event*>& events);
		void output(ostream& out) const;
	public:
		Task* task;
};

ostream& operator<<(ostream& out, const ArrivalEvent& e);

/****************************************************************************
*																			*
*	Definition of DepartureEvent class		     						    *
*																			*
****************************************************************************/

class DepartureEvent : public TeamEvent
{
	public:
		DepartureEvent(DateTime time, Team* team, Task* task) : TeamEvent(time, team), task(task) {}
		void process(list<Event*>& events);
		void output(ostream& out) const;
	public:
		Task* task;
};

ostream& operator<<(ostream& out, const DepartureEvent& e);

#endif
