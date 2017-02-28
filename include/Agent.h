/****************************************************************************
*																			*
*	File:		Agent.h														*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the Agent class.							*
*																			*
****************************************************************************/

#ifndef AGENT_H
#define AGENT_H

#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <list>
#include "Task.h"
// #include "Shift.h"
#include "TaskType.h"
// #include "Utility.h"
// #include "Statistics.h"
#include "../deps/pugixml.h"

using namespace std;
using pugi::xml_document;
using pugi::xml_node;

class Event;
class Team;

/****************************************************************************
*																			*
*	Definition of Agent class												*
*																			*
****************************************************************************/

class Agent
{
//	Friend class

	friend class Team;

//	Public member functions

	public:

	//	Constructor

		// Agent(Team& team, const ptree& xmlData);
		// Agent(Team& team, const ptree& xmlData);
		Agent();
		Agent(xml_node& data, vector<TaskType*> taskTypes);
       	Agent(string name, vector<TaskType*> taskTypes);

	//	Inspectors

		// const string& getName() const {return name;}
		bool isIdle() const {return currTask == NULL;}
		bool isBusy() const {return !isIdle();}
		// int getQueueSize() const {return queue.size();}
		// const Task& getCurrTask() const {return currTask;}
		// const float& getDepTime() const;
		// const bool& needToIntrp(priority_queue<Task>& queue);
		// const float getUtil(int i) {return stats.getUtil(i);}

	//	Mutators

		void setTeam(Team* t) {team = t;}
		// void addTask(Task* task);
		// void arrive(Task& task, float time);
		// void interrupt(float time);
		// void depart(Task& task, float time);
		// void service(Task& task, float time);

//         void servNextTask(float currTime);
//         void clear();
//         void endRep() {stats.endRep(); clear();}
//
// 	//	Other member functions

		// optional<Event> getNextEvent() const;
//         void output();
   		void output(ostream& out) const;

// //  Private member functions
//
//     private:
//         float getFatigueFactor(float time) {return 1 + (time/60 * 0.01);}
//         bool currTaskExp();
//         void procExp(float currTime);
//         void updateUtil(Task* task, float currTime);

//	Data members

	public:
		Team* team;
        string name;
		vector<TaskType*> taskTypes;		// types of tasks
		priority_queue<Task*> queue; 	// task queue
		Task* currTask;             	// current task
		// Statistics& sharedStats;		// shared stats
       // Statistics stats;          	 	// local stats
};

//	Operators

ostream& operator<<(ostream& out, const Agent& a);

#endif
