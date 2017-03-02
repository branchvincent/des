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
#include "task.h"
#include "team.h"
#include "optionparser.h"
#include "ezprogressbar.h"
#include "easylogging++.h"
#include "pugixml.h"

using namespace std;
using pugi::xml_document;
using pugi::xml_node;

// Helper functions and definitions

bool cmpEvents(Event* t1, Event* t2) {return (*t1) < (*t2);}

/****************************************************************************
*																			*
*	Definition of Simulation class											*
*																			*
****************************************************************************/

class Simulation
{
//	Public member functions

	public:

	//	Constructors

		Simulation(Options opts);
		// ~Simulation() {del *;}

	//	Other member functions

        void run();
		void output(ostream& out) const;

//  Private member functions

    private:
		void run(int rep);
		void reset();

//	Data members

	private:
		Options opts;				// command line options
		ez::ezProgressBar bar;		// progress bar
		// Parameters parameters;		// simulation parameters
		vector<Team> teams;			// trains
		list<Event*> events;		// event list
		// Stats stats;				// TODO: statistics
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

Simulation::Simulation(Options opts) : opts(opts)
{
//	TODO: Perform assertions (i.e. duration of simulation and traffic)

	LOG(INFO) << "Initializing simulation";
	bar = ez::ezProgressBar(opts.reps);

// // 	Load xml
//
// 	xml_document doc;
// 	if (!doc.load_file(file.c_str())) cerr << "Failed to read." << endl;
//
// //	Read xml
//
// 	xml_node params = doc.child("parameters");
// 	parameters = Parameters(params);
// 	LOG(INFO) << "Params = " << parameters;
//
// 	for (xml_node& team : doc.child("teams"))
// 	{
// 		if ((string)team.name() == "team")
// 		{
// 			teams.push_back(Team(team));
// 		}
// 	}

//	Fill teams

	// teams.push_back(Team());
	// teams.push_back(Team(Shift("01-01 12:00", "01-02 3:00")));
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
	for (int i = 0; i < opts.reps; i++, ++bar)
	{
		// run(i);
		reset();
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
	LOG(INFO) << "Rep " << rep + 1 << " of " << opts.reps << " started";

//	Get events

	for (Team& ti : teams)
	{
		events.merge(ti.getEvents());
	}
	events.sort(cmpEvents);

//	Process events

	Event* e;

	while (!events.empty())
	{
		e = events.front();
		e->process(events);
		events.pop_front();
	}

//	TODO: Might need to clear agents for next rep

	LOG(INFO) << "Rep " << rep + 1 << " of " << opts.reps << " completed";
}

/****************************************************************************
*																			*
*	Function:	reset														*
*																			*
*	Purpose:	To reset a simulation										*
*																			*
****************************************************************************/

void Simulation::reset()
{
	for (Team& team : teams)
	{
		team.reset();
	}
	events.clear();
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
	// out << "Parameters: " << parameters << endl;
	// out << "Flags: " << flags;
	//	TODO: Might want to output stats
}

#endif
