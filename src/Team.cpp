/****************************************************************************
*																			*
*	File:		Team.cpp													*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the Team class.							*
*																			*
****************************************************************************/

#include <iostream>
#include <string>
#include <algorithm>
#include <list>
#include "Team.h"
#include "Shift.h"
#include "ArrivalEvent.h"
#include "../lib/EasyLogging.h"

using namespace std;
// using boost::property_tree::ptree;

// enum Status {before, working, after};

/****************************************************************************
*																			*
*	Definition of Team class		     						        	*
*																			*
****************************************************************************/

//  TODO:
//  - Shared task to op with current lowest priority
//  - Add fatigue for just human operators

/****************************************************************************
*																			*
*	Function:	Team														*
*																			*
*	Purpose:	To construct a new team										*
*																			*
****************************************************************************/

Team::Team(string name, vector<Agent> agents, vector<TaskType> taskTypes)
	: name(name), agents(agents), taskTypes(taskTypes), shift()
{
	// LOG(INFO) << "Initializing team: " << name << " with " << agents.size()
		// << " agents and " << taskTypes.size() << " task types";
//	LOG(INFO) << "Start: " << shift.getStart() << " Stop: " << shift.getStop();
//	Set task arrivals

	// list<Task> temp;

	for (TaskType& taskType : taskTypes)
	{
		DateTime arrival = shift.getStart();

		while (arrival < shift.getStop())
		{
			arrivingTasks.push_back(taskType.genTask());	// add current
			arrival = arrivingTasks.back().getArrival();
		}
	}

	//	Merge lists

	// arrivingTasks.merge(temp);

// 	Get events

	for (Task& t : arrivingTasks)
	{
		events.push_back(new ArrivalEvent(t.getArrival(), &t));
	}
}

// TODO: need to reset events after each rep

// Team::Team(const ptree& xmlData, Shift shift) : shift(shift)
// {
// 	name = xmlData.get<string>("name");
//
// //	Get task types
//
// 	for (const auto& task : xmlData.get_child("tasks"))
// 	{
// 		if (task.first == "task")
// 		{
// 			taskTypes.push_back(TaskType(*this, task.second));
// 		}
// 	}
//
// //	Get agents
//
// 	for (const auto& agent : xmlData.get_child("agents"))
// 	{
// 		if (agent.first == "agent")
// 		{
// 			agents.push_back(Agent(*this, agent.second));
// 		}
// 	}
//
// //	Get shift
//
// 	phases.push_back(Phase(*this, shift.getStart(), shift.getStop(), 0));
//
// //	Get events
//
// 	for (Task& t : phases[0].arrivingTasks)
// 	{
// 		events.push_back(Event("arrival",t.getArrival(),t));
// 	}
// }

// void Team::startPhase(int phase)
// {
// 	list<Task> temp;
//
// 	for (TaskType& taskType : taskTypes)
// 	{
// 		DateTime arrival;
// 		DateTime stop = arrival + 3600;
//
// 	//	Add tasks that arrive in time
//
// 		while (arrival <= stop)
// 		{
// 			temp.push_back(taskType.genTask(phase));	// add current
// 			arrival = temp.back().getArrival();
// 		}
// 		temp.pop_back();
// 	}
//
// //	Merge lists
//
// 	arrivingTasks.merge(temp);
// }

list<Event*> Team::getEvents() {return events;}

/****************************************************************************
*																			*
*	Function:	output                                                      *
*																			*
*	Purpose:	To output a team                                            *
*																			*
****************************************************************************/

void Team::output(ostream& out) const
{
	// out << "Name: " << name << endl;
	// out << "Task types: " << taskTypes << endl;
	// out << "Agents: ";
	//
	// bool first = true;
	// for (const auto& agent : agents)
	// {
	// 	if (first)
	// 	{
	// 		out << agent.getName();
	// 		first = false;
	// 	}
	// 	else out << ", " << agent.getName();
	// }
}

/****************************************************************************
*																			*
*	Function:	isBusy                                                      *
*																			*
*	Purpose:	To determine if at least one agent is busy               	*
*																			*
****************************************************************************/

// bool Team::isBusy() const
// {
// //	TODO
//     for (const auto& agent : agents)
//         if (agent.isBusy())
//             return true;
//
//     return false;
// }

/****************************************************************************
*																			*
*	Function:	endRep                                                      *
*																			*
*	Purpose:	To end the replication                                      *
*																			*
****************************************************************************/

// void Team::endRep()
// {
// //	TODO:
// //	End stats
// //	End ops
// }

/****************************************************************************
*																			*
*	Function:	output                                                      *
*																			*
*	Purpose:	To output...                                                *
*																			*
****************************************************************************/

// void Team::output()
// {
// //  TODO
// //	Output global stats
// //	Output operator stats
// }

//	Operators

ostream& operator<<(ostream& out, const Team& t) {t.output(out); return out;}
