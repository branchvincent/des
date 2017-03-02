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
#include "team.h"
#include "shift.h"
#include "arrivalevent.h"
#include "easylogging++.h"
#include "pugixml.h"

using namespace std;
using pugi::xml_node;
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

Team::Team(xml_node& data) : shift()
{
	string name = data.attribute("name").value();

	for (xml_node& child : data.child("tasks"))
	{
		if ((string)child.name() == "task")
		{
			taskTypes.push_back(TaskType(child));
		}
	}

	//TODO: fix types
	for (xml_node& child : data.child("agents"))
	{
		if ((string)child.name() == "agent")
		{
			string temp = child.attribute("task_ids").value();
			vector<int> ids = util::toVector<int>(temp);
			vector<TaskType*> subset;
			for (int i = 0; i < taskTypes.size(); i++)
			{
				if (util::contains(ids, i))
				{
					subset.push_back(&taskTypes[i]);
				}
			}
			agents.push_back(Agent(child, subset));

			// for (TaskType* type : subset)
			// {
			// 	type->addAgent(&(agents.back()));
			// }
		}
	}

//	Initialize task arrivals

	for (Agent& agent : agents) agent.setTeam(this);
	for (TaskType& taskType : taskTypes)
	{
		taskType.setTeam(this);
		taskType.addAgent(&agents[0]);	//TODO: fix
	}
	initArrivingTasks();
	initEvents();

	LOG(INFO) << "Initializing team: " << name << " with " << agents.size()
		<< " agents and " << taskTypes.size() << " task types";
	LOG(INFO) << "Start: " << shift.getStart() << " Stop: " << shift.getStop();
}

Team::Team(Shift shift)
	: name("DefaultTeam"), agents{Agent()}, taskTypes{TaskType(),TaskType()}, shift(shift)
{
	LOG(INFO) << "Initializing team: " << name << " with " << agents.size()
		<< " agents and " << taskTypes.size() << " task types";
	LOG(INFO) << "Start: " << shift.getStart() << " Stop: " << shift.getStop();

//	Initialize task arrivals

	for (Agent& agent : agents) agent.setTeam(this);
	for (TaskType& taskType : taskTypes)
	{
		taskType.setTeam(this);
		taskType.addAgent(&agents[0]);
	}
	initArrivingTasks();
	initEvents();
}

Team::Team(string name, vector<Agent> agents, vector<TaskType> taskTypes)
	: name(name), agents(agents), taskTypes(taskTypes), shift()
{
	LOG(INFO) << "Initializing team: " << name << " with " << agents.size()
		<< " agents and " << taskTypes.size() << " task types";
	LOG(INFO) << "Start: " << shift.getStart() << " Stop: " << shift.getStop();

//	Initialize task arrivals

	initArrivingTasks();
	initEvents();
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

// void Team::addTask(Task* task)
// {
// 	TaskType* type = task->taskType; //agents;
// 	vector<Agent*> subteam = type->agents;
// 	Agent* agent = chooseAgent(subteam);
// 	agent->addTask(task);
// }

// vector<Agent&> Team::getAgentSubset(TaskType type)
// {
// 	vector<Agent&> subset;
//
// 	for (Agent& agent : agents)
// 	{
// 		if (util::containts(agent.taskTypes, type))
// 		{
// 			subset.push_back(agent);
// 		}
// 	}
// 	return subset;
// }

Agent* Team::chooseAgent(vector<Agent*> subteam)
{
	int index = 0;

	for (int i = 1; i < subteam.size(); i++)
	{
		if (subteam[i]->queue.size() < subteam[index]->queue.size())
			index = i;
	}
	return subteam[index];
}



void Team::reset()
{
//	Reset

	for (TaskType& taskType : taskTypes)
	{
		taskType.reset();
	}
	arrivingTasks.clear();
	events.clear();

//	Reinitialize task arrivals

	initArrivingTasks();
	initEvents();
}

void Team::initArrivingTasks()
{
//	TODO: merge
//	TODO: incorporate shift start

	DateTime start = shift.getStart();
	DateTime stop = shift.getStop();

	for (TaskType& taskType : taskTypes)
	{
		Task task = taskType.genTask();

		while (task.getArrival() < stop)
		{
			arrivingTasks.push_back(task);
			task = taskType.genTask();
		}
	}
	arrivingTasks.sort();
}

void Team::initEvents()
{
// 	Get events

	for (Task& t : arrivingTasks)
	{
		events.push_back(new ArrivalEvent(t.getArrival(), this, &t));
	}
}

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
