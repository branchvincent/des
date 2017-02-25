/****************************************************************************
*																			*
*	File:		Phase.cpp													*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the Phase class.							*
*																			*
****************************************************************************/

#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include "Phase.h"
#include "Team.h"
#include "Task.h"

using namespace std;

// bool compareArrivals(Task t1, Task t2) {return t1.arrivesSooner(t2);}

/****************************************************************************
*																			*
*	Function:	Phase														*
*																			*
*	Purpose:	To construct a phase										*
*																			*
****************************************************************************/

Phase::Phase(Team& team, DateTime start, DateTime stop, int num) : team(team)
{
//	Create all tasks

	list<Task> temp;

	for (TaskType& taskType : team.taskTypes)
	{
		DateTime arrival;

	//	Add tasks that arrive in time
		cout << arrival << " " << stop << endl;

		while (arrival <= stop)
		{
			temp.push_back(taskType.genTask(num));	// add current
			arrival = temp.back().getArrival();
			cout << "Here " << temp.size() << endl;
		}
	}

//	Merge lists

	arrivingTasks.merge(temp);

	cout << "ArrivingTasks = " << arrivingTasks.size() << endl;
}

// void Phase::run()
// {
// 	cout << "Beginning Phase " << number << "." << endl;
//
//
//
// 	cout << "Phase " << number << " completed." << endl;
// }

//	Operators

// ostream& operator<<(ostream& out, const Operator& op) {op.output(out); return out;}
