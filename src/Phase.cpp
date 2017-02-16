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
		Task task = taskType.genTask(num);

	//	Add tasks that arrive in time

		while (task.getArrival() < stop)
		{
			temp.push_back(task);			// add current
			task = taskType.genTask(num);	// get next
		}
	}

//	Merge lists

	arrivingTasks.merge(temp);
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
