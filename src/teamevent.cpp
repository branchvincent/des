/****************************************************************************
*																			*
*	File:		TeamEvent.cpp												*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the TeamEvent class.	   					*
*																			*
****************************************************************************/

#include <iostream>
#include <string>
#include "teamevent.h"

using namespace std;

/****************************************************************************
*																			*
*	Function:	TeamEvent       										    *
*																			*
*	Purpose:	To construct an event                                       *
*																			*
****************************************************************************/

TeamEvent::TeamEvent(DateTime time, Team* team) : Event(time), team(team) //, agent(agent)
{}

// const Task& TeamEvent::getTask() const {return &task;}
Team* TeamEvent::getTeam() const {return team;}

/****************************************************************************
*																			*
*	Function:	output       												*
*																			*
*	Purpose:	To output an event                                       	*
*																			*
****************************************************************************/

// void Event::output(ostream& out) const
// {
// 	out << "Time: " << time << endl;
// 	// out << "Agent: " << agent << endl;
// }
