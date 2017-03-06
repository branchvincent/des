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
#include "event.h"
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

Team::Team(const xml_node& data) : _name("Default"), _agents{}, _taskTypes{}, _shift(),
	_arrivingTasks{}, _events{}
{
	LOG(DEBUG) << "Initializing team at " << this;

//	Name

	_name = util::toLower(data.attribute("name").value());
	LOG_IF(_name == "", FATAL) << "XML Error: Could not read team attribute 'name'";

//	Task types

	for (const xml_node& type : data.child("tasks"))
		if ((string)type.name() == "task")
			_taskTypes.emplace_back(type);
	LOG_IF(_taskTypes.size() == 0, FATAL) << "Team " << _name << " has not task types";

//	Agents

	for (const xml_node& agent : data.child("agents"))
		if ((string)agent.name() == "agent")
		 	_agents.emplace_back(this, agent);
	LOG_IF(_agents.size() == 0, FATAL) << "Team " << _name << " has no agents";

//	Initialize task arrivals

	validate();
	initArrivingTasks();
	initEvents();

	LOG(DEBUG) << "Initialized team\n" << *this << endl << "at " << this;
	// LOG(INFO) 	<< "Initialized team " << name << " with " << agents.size()
				// << " agents and " << taskTypes.size() << " task types";
	// LOG(INFO) << "Start: " << shift.getStart() << " Stop: " << shift.getStop();
}


// Team::Team(Shift shift)
// 	: name("DefaultTeam"), agents{Agent()}, taskTypes{TaskType(),TaskType()}, shift(shift)
// {
// 	LOG(DEBUG) 	<< "Initializing team: " << name << " with " << agents.size()
// 				<< " agents and " << taskTypes.size() << " task types";
// 	// LOG(INFO) << "Start: " << shift.getStart() << " Stop: " << shift.getStop();
//
// //	Initialize task arrivals
//
// 	initArrivingTasks();
// 	initEvents();
// }
//
// Team::Team(string name, vector<Agent> agents, vector<TaskType> taskTypes)
// 	: name(name), agents(agents), taskTypes(taskTypes), shift()
// {
// 	LOG(INFO) << "Initializing team: " << name << " with " << agents.size()
// 		<< " agents and " << taskTypes.size() << " task types";
// 	LOG(INFO) << "Start: " << shift.getStart() << " Stop: " << shift.getStop();
//
// //	Initialize task arrivals
//
// 	initArrivingTasks();
// 	initEvents();
// }

// list<Event*> Team::getEvents() {return _events;}

/****************************************************************************
*																			*
*	Function:	validate													*
*																			*
*	Purpose:	To validate a team											*
*																			*
****************************************************************************/

void Team::validate() const
{
//	Convert task types to pointers

	// vector<Agent*> agent_ps;
	// agent_ps.reserve(agents.size());
	// for (const Agent& agent : agents)
	// 	agent_ps.push_back(&agent);

//	Tasks

	for (const TaskType& type : _taskTypes)
	{
		for (const Agent* agent: type.agents())
		{
			// LOG_IF(not util::contains(agent_ps, agent), FATAL) << "Team not valid: incorrect agent in tasktype";
			// LOG_IF(not util::contains(agents, *agent), FATAL) << "Team not valid: task type's agents does not contain self";
			agent->validate();
		}
	}

//	Agents

	for (const Agent& agent : _agents)
	{
		LOG_IF(agent.team() != this, FATAL) << "Team not valid: incorrect team for agent "
			<< &agent << ". Expected " << this << " but received " << agent.team();
		for (const TaskType* type: agent.taskTypes())
		{
			// LOG_IF(not util::contains(taskTypes, *type), FATAL) << "Team not valid: agent's task types does not contain self";
			type->validate();
		}
	}
}
// void Team::addTask(Task* task)
// {
// 	TaskType* type = task->taskType; //agents;
// 	vector<Agent*> subteam = type->agents;
// 	Agent* agent = chooseAgent(subteam);
// 	agent->addTask(task);
// }

Agent* Team::chooseAgent(vector<Agent*> subteam)
{
	 int index = 0;

	 for (int i = 1; i < subteam.size(); i++)
	 {
	 	if (subteam[i]->queue().size() < subteam[index]->queue().size())
	 		index = i;
	 }
	 return subteam[index];
}


void Team::reset()
{
//	Reset

	for (TaskType& taskType : _taskTypes)
	{
		taskType.reset();
	}
	_arrivingTasks.clear();
	_events.clear();

//	Reinitialize task arrivals

	initArrivingTasks();
	initEvents();
}

void Team::initArrivingTasks()
{
//	TODO: merge
//	TODO: incorporate shift start

	DateTime start = _shift.getStart();
	DateTime stop = _shift.getStop();

	for (TaskType& taskType : _taskTypes)
	{
		Task task = taskType.genTask();

		while (task.arrival() < stop)
		{
			_arrivingTasks.push_back(task);
			task = taskType.genTask();
		}
	}
	_arrivingTasks.sort();
}

void Team::initEvents()
{
// 	Get events

	for (Task& t : _arrivingTasks)
	{
		_events.push_back(new ArrivalEvent(t.arrival(), this, &t));
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
	out << "Team " << _name << endl;
	out << "Task types: " << _taskTypes << endl;
	out << "Agents: ";

	// bool first = true;
	// for (const auto& agent : _agents)
	// {
	// 	if (first)
	// 	{
	// 		out << agent.name();
	// 		first = false;
	// 	}
	// 	else out << ", " << agent.name();
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
//
// void Team::output()
// {
// //  TODO
// //	Output global stats
// //	Output operator stats
// }

//	Operators

ostream& operator<<(ostream& out, const Team& t) {t.output(out); return out;}
