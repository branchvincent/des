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

bool compareArrivals(Task t1, Task t2) {return t1.arrivesSooner(t2);}

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

        Phase(Team& team, int num, float start, float stop);

	//	Inspectors


	//	Mutators


	//	Other member functions

        // void output(ostream& out) const {out << stats << endl;}

//  Private member functions

//     private:


//	Data members

	private:
		Team& team;
		int num;
        float start;
		float stop;
		vector<Task> tasks;
};

//	Operators

// ostream& operator<<(ostream& out, const Operator& op) {op.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	Phase														*
*																			*
*	Purpose:	To construct a phase										*
*																			*
****************************************************************************/

float Phase::Phase(Team& team, int num, float start, float stop) : times(times)
{
//	Create all tasks

	list<Task> temp;

	for (const auto& taskType : team.taskTypes)
	{
		Task task = taskType.genTask(num);
		float arrival = task.getArrival();

	//	Add tasks that arrive in time

		while (arrival < stop)
		{
			temp.push_back(task);			// add current
			task = taskType.genTask(num);	// get next
			arrival = task.getArrival();
		}
	}

//	Merge lists

	tasks.merge(temp, compareArrivals);
}

void Phase::run()
{
	cout << "Beginning Phase " << number << "." << endl;



	cout << "Phase " << number << " completed." << endl;
}

#endif
