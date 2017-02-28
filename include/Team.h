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
// #include <boost/property_tree/ptree.hpp>
// #include <boost/property_tree/xml_parser.hpp>
// #include <boost/optional.hpp>
#include "Agent.h"
#include "TaskType.h"
#include "Shift.h"
#include "ArrivalEvent.h"
#include "../deps/pugixml.h"
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

		//TODO: const xml_node
		Team(xml_node& data);
		Team(Shift shift = Shift());
		Team(string name, vector<Agent> agents, vector<TaskType> taskTypes);

	// 	Inspector

        // int getQueueSize() const {return ops[0].getQueueSize();}
        // Task getNextTask();
        // float getNextDeptTime();
        // bool isBusy() const;
		// float getUtil(int i, int j) {return ops[i].getUtil(j);}

    // 	Mutators

        // void startPhase(int phase);
        // optional<Event> getNextEvent();
        list<Event*> getEvents();
        // void addTask(Task* task);

        // void arrive(Task* task);
        // void depart(Task* task);
        // void reset() {for (const auto& agent : agents) agent.reset();};
        // void endRep();


    //  Other member functions

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
		string name;
        vector<Agent> agents;
		vector<TaskType> taskTypes;

		Shift shift;
		list<Task> arrivingTasks;
		// vector<Phase> phases;
        // int phase;
        // string status;
        list<Event*> events;
		// Team supervisor;
};

//	Operators

ostream& operator<<(ostream& out, const Team& t);

#endif
