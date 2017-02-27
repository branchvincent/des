/****************************************************************************
*																			*
*	File:		ArrivalEvent.cpp											*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the ArrivalEvent class.	   				*
*																			*
****************************************************************************/

#include <iostream>
#include <string>
#include "ArrivalEvent.h"
#include "Task.h"
#include "Team.h"
#include "DepartureEvent.h"
#include "../lib/EasyLogging.h"
// #include "Agent.h"
// #include "Utility.h"

using namespace std;

/****************************************************************************
*																			*
*	Function:	ArrivalEvent       											*
*																			*
*	Purpose:	To construct an event                                       *
*																			*
****************************************************************************/

ArrivalEvent::ArrivalEvent(DateTime time, Team* team, Task* task) : TeamEvent(time, team), task(task)
{}

/****************************************************************************
*																			*
*	Function:	process       												*
*																			*
*	Purpose:	To process an event                                       	*
*																			*
****************************************************************************/

void ArrivalEvent::process(list<Event*>& events)
{
	if (task == NULL)
	{
		LOG(ERROR) << "Tried to process null task";
		return;
	}
	// task->start(time);
	// team->addTask(task);

	LOG(INFO) << time << ": Team " << team << "=> Task " << task << " arriving";
	vector<Agent*> subteam = task->taskType->agents;
	Agent* agent = chooseAgent(subteam);
	task->setAgent(agent);

	if (agent->isIdle())
	{
		agent->currTask = task;
		task->start(time);

		list<Event*>::iterator it = events.begin();
		DepartureEvent d = DepartureEvent(task->departure, team, task);
		while (it != events.end() and **it <= d) it++;
		events.insert(it, new DepartureEvent(task->departure, team, task));
		// LOG(DEBUG) << "Inserting departure at " << task->departure;
	}
	else
	{
		agent->queue.push(task);
		// LOG(INFO) << "Agent " << agent->name << " enqueued task";
	}
}

Agent* ArrivalEvent::chooseAgent(vector<Agent*> subteam)
{
	int index = 0;

	for (int i = 1; i < subteam.size(); i++)
	{
		if (subteam[i]->queue.size() < subteam[index]->queue.size())
			index = i;
	}
	return subteam[index];
}

/****************************************************************************
*																			*
*	Function:	output       												*
*																			*
*	Purpose:	To output an event                                       	*
*																			*
****************************************************************************/

void ArrivalEvent::output(ostream& out) const
{
	out << "Arriving at " << time;
	// out << "Type: " << type << endl;
	// out << "Time: " << time << endl;
	// out << "Agent: " << agent << endl;
}

//	Operators

ostream& operator<<(ostream& out, const ArrivalEvent& e) {e.output(out); return out;}
