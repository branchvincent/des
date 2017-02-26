/****************************************************************************
*																			*
*	File:		Simulation.h												*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the Simulation class.						*
*																			*
****************************************************************************/

#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "Flags.h"
#include "Parameters.h"
#include "Event.h"
#include "Team.h"
#include "../lib/EasyLogging.h"
#include "../lib/EZProgressBar.h"

using namespace std;
using boost::property_tree::ptree;

// Helper functions and definitions

// bool cmpTaskArrs(Task t1, Task t2) {return t1.arrivesSooner(t2);}

/****************************************************************************
*																			*
*	Definition of Simulation class											*
*																			*
****************************************************************************/

//  Notes
//  - Add utilization count for tasks cut off at end of phase (processAllDepts)

class Simulation
{
//	Public member functions

	public:

	//	Constructors

        Simulation(string file, Flags flags);
		// ~Simulation() {del *;}

	//	Other member functions

        void run();
		void output(ostream& out) const;

//  Private member functions

    private:
		void run(int rep);

//	Data members

	private:
		Flags flags;				// command line flags
		ez::EZProgressBar bar;		// progress bar
		Parameters parameters;		// simulation parameters
		vector<Team> teams;			// trains
		list<Event> events;			// event list
};

//	Operators

ostream& operator<<(ostream& out, const Simulation& s) {s.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	Simulation													*
*																			*
*	Purpose:	To construct a new simulation								*
*																			*
****************************************************************************/

Simulation::Simulation(string file, Flags flags = Flags()) : flags(flags), parameters(file)
{
//	TODO: Perform assertions (i.e. duration of simulation and traffic)

//  Initialize srand

    if (flags.isOn("rand"))
        srand((unsigned int) time(0));
    else
        srand(0);

	if (flags.isOn("verbose"))
	{
		cout << parameters << endl;
		cout << flags << endl;
	}

	// if (flags.isOn("pbar"))
	bar = ez::EZProgressBar(parameters.numReps);

//	Fill teams

	ptree params;
	read_xml(file, params);

	for (const auto& team : params.get_child("teams"))
	{
		if (team.first == "team")
		{
			teams.push_back(Team(team.second));
		}
	}
}

/****************************************************************************
*																			*
*	Function:	run                                                         *
*																			*
*	Purpose:	To run the simulation for the specified number of           *
*               replications                                                *
*																			*
****************************************************************************/

void Simulation::run()
{
	LOG(INFO) << "Simulation started";

//	Run each replication

	bar.start();
	for (int i = 0; i < parameters.numReps; i++, ++bar)
	{
		run(i);
	}

	LOG(INFO) << "Simulation completed";
}

/****************************************************************************
*																			*
*	Function:	run                                                         *
*																			*
*	Purpose:	To run one replication of the simulation                    *
*																			*
****************************************************************************/

void Simulation::run(int rep)
{
	LOG(INFO) << "Rep " << rep + 1 << " of " << parameters.numReps << " started";

//	Get events

	for (Team& ti : teams)
	{
		events.merge(ti.getEvents());
	}

//	Process events

	for (Event& e : events)
	{
		e.process();
		// LOG(INFO) << "Event " << e << " processed";
	}

//	TODO: Might need to clear agents for next rep

	LOG(INFO) << "Rep " << rep + 1 << " of " << parameters.numReps << " completed";
}

/****************************************************************************
*																			*
*	Function:	output														*
*																			*
*	Purpose:	To output a simulation										*
*																			*
****************************************************************************/

void Simulation::output(ostream& out) const
{
	out << "Parameters: " << parameters << endl;
	out << "Flags: " << flags;
	//	TODO: Might want to output stats
}

#endif
