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
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "Agent.h"
#include "TaskType.h"
#include "Shift.h"

using namespace std;
using boost::property_tree::ptree;

//class Agent;
//class TaskType;
class Event;

/****************************************************************************
*																			*
*	Definition of Team class		     						        	*
*																			*
****************************************************************************/

class Team
{
//  Friend class

   	friend class Agent;

//	Public member functions

	public:

	//	Constructor

		Team(const ptree& xmlData);
		// Team(string name, vector<Agent> agents, vector<TaskTypes> taskTypes);

	// 	Inspector

    //     // int getQueueSize() const {return ops[0].getQueueSize();}
    //     Task getNextTask();
    //     float getNextDeptTime();
    //     bool isBusy() const;
	// 	// float getUtil(int i, int j) {return ops[i].getUtil(j);}

    // 	Mutators

		// Event getNextEvent();

	// 	void createTasks()
	// 	{
	// 		for (const auto& agent : agents)
	// 		{
	//
	// 		}
	// 	}
	//
    //     void arrive(Task* task);
	// 	void depart(Task* task);
    //     void reset() {for (const auto& agent : agents) agent.reset();};
    //     void endRep();
	//
    // //  Other member functions
	//
    //     void output();
        void output(ostream& out) const;

//	Data members

	private:
        // Statistics stats;
		string name;
   		vector<Agent> agents;
		vector<TaskType> taskTypes;
		Shift shift;
		list<Task> arrivingTasks;
		// vector<Phase> phases;
		// Team supervisor;
};

//	Operators

ostream& operator<<(ostream& out, const Team& t);

#endif
