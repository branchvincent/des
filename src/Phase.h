/****************************************************************************
*																			*
*	File:		Phase.h														*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jun 9, 2016													*
*																			*
*	Purpose:	This file defines the Phase class.							*
*																			*
****************************************************************************/

#ifndef PHASE_H
#define PHASE_H

#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include "Task.h"

using namespace std;

class Team;

/****************************************************************************
*																			*
*	Definition of Phase class												*
*																			*
****************************************************************************/

class Phase
{
//	Public member functions

	public:

	//	Constructor

        Phase(Team& team, DateTime start, DateTime stop, int num);

	//	Inspectors


	//	Mutators


	//	Other member functions

        // void output(ostream& out) const {out << stats << endl;}

//  Private member functions

//     private:


//	Data members

	private:
		Team& team;
        DateTime start;
		DateTime stop;
		int num;
		list<Task> arrivingTasks;
};

//	Operators

// ostream& operator<<(ostream& out, const Operator& op);

#endif
