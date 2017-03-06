/****************************************************************************
*																			*
*	File:		Event.cpp												    *
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the Event class.	   					    *
*																			*
****************************************************************************/

#include <iostream>
#include <string>
#include "event.h"
#include "team.h"
#include "task.h"
#include "easylogging++.h"

using namespace std;

/****************************************************************************
*																			*
*	Definition of ArrivalEvent class		     						    *
*																			*
****************************************************************************/

/****************************************************************************
*																			*
*	Function:	process       												*
*																			*
*	Purpose:	To process an event                                       	*
*																			*
****************************************************************************/

void ArrivalEvent::process(list<Event*>& events)
{
	// task->start(time);
	// team->addTask(task);

//	Get subteam

//	LOG(DEBUG) << time << ": Team " << team << "=> Task " << task << " arriving of type " << task.type();
	vector<Agent> subteam = task.type().agents();
	// LOG(DEBUG) << "Subteam" << subteam;
	LOG_IF(subteam.size() == 0, FATAL) << "Subteam is empty";

//	Choose agent from subteam

	Agent& agent = chooseAgent(subteam);
	LOG(DEBUG) << "Chosen agent " << agent;
	task.setAgent(&agent);

//	Start task or enqueue

	if (agent.isIdle())
	{
	//	Update current task

		agent.currTask(&task);
		task.start(time);

	//	Insert new departure event

		list<Event*>::iterator it = events.begin();
		DepartureEvent d = DepartureEvent(task.departure(), team, task);
		while (it != events.end() and **it <= d) it++;
		events.insert(it, new DepartureEvent(task.departure(), team, task));
	}
	else
	{
		LOG(DEBUG) << "Agent " << agent.name() << " at " << agent << " enqueued task";
//		agent.queue().push(task);
	}
}

/****************************************************************************
*																			*
*	Function:	chooseAgent    												*
*																			*
*	Purpose:	To choose which agent to the current task                  	*
*																			*
****************************************************************************/

Agent& ArrivalEvent::chooseAgent(vector<Agent>& subteam)
{
	LOG_IF(subteam.size() == 0, FATAL) << "Subteam is empty";
	int index = 0;

	for (int i = 1; i < subteam.size(); i++)
	{
		if (subteam[i].queue().size() < subteam[index].queue().size())
			index = i;
	}

	util::checkIndex(subteam,index);
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

ostream& operator<<(ostream& out, const ArrivalEvent& e) {e.output(out); return out;}

/****************************************************************************
*																			*
*	Definition of DepartureEvent class		     						    *
*																			*
****************************************************************************/

/****************************************************************************
*																			*
*	Function:	process       												*
*																			*
*	Purpose:	To process an event                                       	*
*																			*
****************************************************************************/

void DepartureEvent::process(list<Event*>& events)
{
	// LOG_IF(task == NULL, FATAL) << "Tried to process null task";
	LOG(DEBUG) << time << ": Team " << team << "=> Task " << task << " departing";
	task.finish(time);
	Agent& agent = task.agent();
	// ASSERT(agent != NULL, "NULL");
//	agent->currTask(NULL);

//	LOG(DEBUG) << agent;

	if (!agent.queue().empty())
	{
		agent.currTask(agent.queue().top());
		agent.queue().pop();
		Task& newTask = agent.currTask();
		newTask.start(time);

		list<Event*>::iterator it = events.begin();
		DepartureEvent d = DepartureEvent(newTask.departure(), team, newTask);
		while (it != events.end() and **it <= d) it++;
		events.insert(it, new DepartureEvent(newTask.departure(), team, newTask));
		// LOG(DEBUG) << "Inserting departure at " << newTask->departure;
	}
	list<Event*>::iterator it = events.begin();
	DepartureEvent d = DepartureEvent(task.departure(), team, task);
	while (**it < d) it++;
	events.insert(--it, new DepartureEvent(task.departure(), team, task));
}

/****************************************************************************
*																			*
*	Function:	output       												*
*																			*
*	Purpose:	To output an event                                       	*
*																			*
****************************************************************************/

void DepartureEvent::output(ostream& out) const
{
	out << "Departing at " << time;
	// out << "Type: " << type << endl;
	// out << "Time: " << time << endl;
	// out << "Agent: " << agent << endl;
}

ostream& operator<<(ostream& out, const DepartureEvent& e) {e.output(out); return out;}
