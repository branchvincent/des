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
#include "event.h"
#include "batch.h"
#include "optionparser.h"
#include "ezprogressbar.h"
#include "easylogging++.h"
#include "pugixml.h"

using namespace std;
using pugi::xml_document;
using pugi::xml_node;

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
//		~Simulation() {for () delete *;}

	//	Other member functions

        void run();
		void output(ostream& out) const;

//  Private member functions

    private:
	void loadTeams(const xml_node& data);
		void run(int rep);
		void reset();

//	Data members

	private:
		Options opts;				// command line options
		ez::ezProgressBar bar;		// progress bar
		vector<Batch> batches;		// groups of teams
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

// 	Load xml

	xml_document doc;
	pugi::xml_parse_result result = doc.load_file(opts.in.c_str());
 	LOG_IF(not result, FATAL) << "Failed to read input file '" << opts.in
		<< "': " << result.description();

//	Load batches and teams

	// for (const xml_node& batch : doc.child("batches"))
	// 	if ((string)batch.name() == "batch")
	// 		batches.emplace_back(batch);

	loadTeams(doc);
}

void Simulation::loadTeams(const xml_node& data)
{
//	Define batches

	for (const xml_node& batch : data.child("batches"))
		if ((string)batch.name() == "batch")
			batches.emplace_back(batch);

//	Add teams

	xml_node t;
	xml_node p ;

	for (Batch& batch : batches)
	{
	//	Find teams

		for (const xml_node& team : data.child("teams"))
		{
			if ((string)team.name() == "team" and util::toLower(team.attribute("type").value()) == batch.type)
			{
				t = team;
			}
			else if ((string)team.name() == "team" and util::toLower(team.attribute("type").value()) == batch.partnerType)
			{
				p = team;
			}
		}

	//	Create teams

		LOG_IF(t == data, FATAL) << "Team " << batch.type << " not found";
		LOG_IF(p == data, FATAL) << "Team " << batch.partnerType << " not found";
		for (int i = 0; i < batch.count; i++)
		{
			teams.emplace_back(t, batch.shift);
		}
	}

	LOG(INFO) << "Initialized " << teams.size() << " teams";
	// for (const xml_node& team : doc.child("teams"))
	// 	if ((string)team.name() == "team")
	// 		teams.emplace_back(team);

	// for (const xml_node& team : doc.child("teams"))
	// 	if ((string)team.name() == "team")
	// 		teams.emplace_back(team);
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
		run(i);
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
		events.merge(ti.events());
	}
	events.sort(cmpEvents);

//	Process events

	Event* e;
	DateTime t, t_prev = 0;
	int processCount = 0;

	while (not events.empty())
	{
	//	Check time

		e = events.front();
		t = e->time;
		LOG_IF(t_prev > t, FATAL) << "Events not in chronological order";
		// LOG(DEBUG) << "Processing event at " << t;

	//	Process

		e->process(events);
		events.pop_front();
		t_prev = t;
		processCount++;
	}

//	TODO: Might need to clear agents for next rep

	LOG(INFO) << "Rep " << rep + 1 << " of " << opts.reps << " completed "
		<< "(" << processCount << " events processed)";
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
		team.reset();
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
	//	TODO: Might want to output stats
}

#endif
