/****************************************************************************
*																			*
*	File:		Team.h														*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the Team class.							*
*																			*
****************************************************************************/

#ifndef TEAM_H
#define TEAM_H

#include <iostream>
#include <string>
#include "agent.h"
#include "tasktype.h"
#include "shift.h"
#include "pugixml.h"
// #include "Phase.h"

using namespace std;
using pugi::xml_document;
using pugi::xml_node;

//class Agent;
//class TaskType;
// class Event;

/****************************************************************************
*																			*
*	Definition of Team class		     						        	*
*																			*
****************************************************************************/

class Team
{
//  Friend class

 //   	friend class Agent;
    // friend class TaskType;
    // friend class Phase;

//	Public member functions

	public:

	//	Constructor

		Team(const xml_node& data);
		// Team(const Team& t);
		// Team(Shift shift = Shift());
		// Team(string name, vector<Agent> agents, vector<TaskType> taskTypes);

	// 	Inspector

		// const string& name() const {return _name;}
		// const vector<Agent>& agents() const {return _agents;}
		// const vector<TaskType>& taskTypes() const {return _taskTypes;}
		// const Shift& shift() {return _shift;}
		// const list<Task>& arrivingTasks() {return _arrivingTasks;}
		// const list<Event*>& events() {return _events;}

		string name() {return _name;}
	    vector<Agent> agents()  {return _agents;}
	    vector<TaskType> taskTypes()  {return _taskTypes;}
	    Shift& shift() {return _shift;}
	    list<Task> arrivingTasks() {return _arrivingTasks;}
	    list<Event*> events() {return _events;}

        // int getQueueSize() const {return ops[0].getQueueSize();}
        // Task getNextTask();
        // float getNextDeptTime();
        // bool isBusy() const;
		// float getUtil(int i, int j) {return ops[i].getUtil(j);}

    // 	Mutators

        // void startPhase(int phase);
        // optional<Event> getNextEvent();
        // list<Event*> getEvents();
        // void addTask(Task* task);

        // void arrive(Task* task);
        // void depart(Task* task);
        // void reset() {for (const auto& agent : agents) agent.reset();};
        // void endRep();


    //  Other member functions

		void validate() const;
        void reset();
        void output(ostream& out) const;
		Agent* chooseAgent(vector<Agent*> subteam);

//  Private member functions

    private:
        // vector<Agent&> getAgentSubset(TaskType type);
        void initArrivingTasks();
        void initEvents();

//	Data members

	public:
        // Statistics stats;
		string _name;
        vector<Agent> _agents;
		vector<TaskType> _taskTypes;
		Shift _shift;
		list<Task> _arrivingTasks;
		// vector<Phase> phases;
        // int phase;
        // string status;
        list<Event*> _events;
		// Team supervisor;
};

//	Operators

ostream& operator<<(ostream& out, const Team& t);

#endif
