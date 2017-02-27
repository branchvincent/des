/****************************************************************************
*																			*
*	File:		TeamEvent.h											        *
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the TeamEvent class.	   					*
*																			*
****************************************************************************/

#ifndef TEAMEVENT_H
#define TEAMEVENT_H

#include <iostream>
#include <string>
#include "Event.h"
//#include "Team.h"

using namespace std;

 class Team;
// class Agent;

/****************************************************************************
*																			*
*	Definition of TeamEvent class	     						            *
*																			*
****************************************************************************/

class TeamEvent : public Event
{
//	Public member functions

	public:

    //  Constructor

		TeamEvent(DateTime time, Team* team); //, Agent& agent);

	//	Inspectors

		Team* getTeam() const;

	//	Other member functions

		// virtual void output(ostream& out) const = 0;

//	Data members

	protected:
		Team* team;
};

//	Operators

// ostream& operator<<(ostream& out, const Event& e);

#endif
