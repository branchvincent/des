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
#include <boost/optional.hpp>
#include "Agent.h"
#include "TaskType.h"
#include "Shift.h"

using namespace std;
using boost::property_tree::ptree;
using boost::optional;

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
    friend class TaskType;
    friend class Phase;

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

		optional<Event> getNextEvent();

		void createTasks(int phase)
		{
			for (TaskType& taskType : taskTypes)
			{
                Task task = taskType.genTask(phase);
                while (task.getArrival() < 2000)    //TODO
                {
                    arrivingTasks.push_back(task);
                }
			}
		}
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
