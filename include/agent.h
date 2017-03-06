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
#include "task.h"
// #include "shift.h"
#include "tasktype.h"
// #include "utility.h"
// #include "Statistics.h"
#include "pugixml.h"

using namespace std;
using pugi::xml_document;
using pugi::xml_node;

class Event;
class Team;

struct CmpPrty
{
	bool operator()(Task* t1, Task* t2) {return t2->higherPriority(*t1);}
};
// typedef Agent Queue;

// bool cmpPrty(Task* t1, Task* t2) {return t2->higherPriority(*t2);}
// typedef priority_queue<Task*,vector<Task*>,decltype(&cmpPrty)> Queue;
typedef priority_queue<Task*,vector<Task*>,CmpPrty> Queue;

/****************************************************************************
*																			*
*	Definition of Agent class												*
*																			*
****************************************************************************/

class Agent
{
//	Friend class

	// friend class Team;

//	Public member functions

	public:

	//	Constructor

		// Agent();
		Agent(Team& team, const xml_node& data);
     //   	Agent(string name, vector<TaskType*> taskTypes);

	//	Inspectors

		// Team* team() const {return _team;}
		// string& name() {return _name;}
		// const vector<TaskType*>& taskTypes() const {return _taskTypes;}
		// Queue& queue() {return _queue;}
		// Task* currTask() {return _currTask;}

//		Team team() {return _team;}
		string name() {return _name;}
		vector<TaskType> taskTypes() const;
		vector<int> taskTypeIds() const {return _taskTypeIds;}
		Queue& queue() {return _queue;}
		Task& currTask() {return *_currTask;}

		bool isIdle() const {return _currTask == NULL;}
		bool isBusy() const {return !isIdle();}
		void validate() const;
		// int getQueueSize() const {return queue.size();}
		// const Task& getCurrTask() const {return currTask;}
		// const float& getDepTime() const;
		// const bool& needToIntrp(priority_queue<Task>& queue);
		// const float getUtil(int i) {return stats.getUtil(i);}

	//	Mutators

		// void team(Team* team) {_team = team;}
		// void name(string name) {_name = name;}
		// void taskTypes(vector<TaskType*>& taskTypes) {_taskTypes = taskTypes;}
		// const Team& team() const {return _team;}
		void currTask(Task* currTask) {_currTask = currTask;}

		// void setTeam(Team* t) {team = t;}
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

	private:
		Team& _team;
        string _name;
		vector<int> _taskTypeIds;	// types of tasks
		Queue _queue; 					// task queue
		Task* _currTask;             	// current task
		// Statistics& sharedStats;		// shared stats
       // Statistics stats;          	 	// local stats
};

//	Operators

ostream& operator<<(ostream& out, const Agent& a);

#endif
