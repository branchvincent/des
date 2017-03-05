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
#include "arrivalevent.h"
#include "task.h"
#include "team.h"
#include "departureevent.h"
#include "easylogging++.h"
// #include "agent.h"
// #include "utility.h"

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
	LOG_IF(task == NULL, FATAL) << "Tried to process null task";
	// task->start(time);
	// team->addTask(task);

//	Get subteam

	LOG(DEBUG) << time << ": Team " << team << "=> Task " << task << " arriving of type " << task->taskType;
	vector<Agent*> subteam = task->taskType->agents;
	LOG(DEBUG) << "Subteam" << subteam;
	LOG_IF(subteam.size() == 0, FATAL) << "Subteam is empty";

//	Choose agent from subteam

	Agent* agent = chooseAgent(subteam);
	LOG(DEBUG) << "Chosen agent " << agent;
	task->setAgent(agent);

//	Start task or enqueue

	if (agent->isIdle())
	{
	//	Update current task

		agent->currTask = task;
		task->start(time);

	//	Insert new departure event
		
		list<Event*>::iterator it = events.begin();
		DepartureEvent d = DepartureEvent(task->departure, team, task);
		while (it != events.end() and **it <= d) it++;
		events.insert(it, new DepartureEvent(task->departure, team, task));
	}
	else
	{
		string name = agent->name;
		LOG(DEBUG) << "Agent " << name << " at " << agent << " enqueued task";
//		agent->queue.push(task);
	}
}

/****************************************************************************
*																			*
*	Function:	chooseAgent    												*
*																			*
*	Purpose:	To choose which agent to the current task                  	*
*																			*
****************************************************************************/

Agent* ArrivalEvent::chooseAgent(vector<Agent*> subteam)
{
	LOG_IF(subteam.size() == 0, FATAL) << "Subteam is empty";
	int index = 0;

	for (int i = 1; i < subteam.size(); i++)
	{
		if (subteam[i]->queue.size() < subteam[index]->queue.size())
			index = i;
	}

	LOG_IF(index >= subteam.size(), FATAL) << "ACCESS ERROR";
	LOG_IF(subteam[index] == NULL, FATAL) << "Agent of subteam is null";
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
