/****************************************************************************
*																			*
*	File:		TrafficLevels.h												*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the TrafficLevel class.					*
*																			*
****************************************************************************/

#ifndef TRAFFICLEVELS_H
#define TRAFFICLEVELS_H

#include <iostream>
#include <string>
#include <map>
#include "Util.h"

using namespace std;

vector<char> valid_levels = {'l', 'm', 'h'};
map<char,float> f_levels = {make_pair('l',2), make_pair('m',1), make_pair('h',0.5)};

/****************************************************************************
*																			*
*	Definition of TrafficLevels class		     					        *
*																			*
****************************************************************************/

class TrafficLevels
{
//	Public member functions

	public:

    //  Constructor

		TrafficLevels(vector<char> levels) : levels(levels),
		{ASSERT(contains(valid_levels, level));}
		TrafficLevels(vector<float> levels) : f_levels(levels) {}

	//	Inspectors

    //  Other member functions

		void output(ostream& out) const {out << level;}

//	Data members

	public:
		vector<char> levels;
		vector<float> f_levels;

};

//	Operators

ostream& operator<<(ostream& out, const TrafficLevel& tl) {tl.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	TrafficLevel												*
*																			*
*	Purpose:	To construct a traffic level object							*
*																			*
****************************************************************************/

TrafficLevel::TrafficLevel(string file) :
	numReps(100),
	numPhases(3),
	intSize(10),
	isTrafficOn(true),
	isFatigueOn(true),
	isVerboseOn(false),
	isRandOn(true)
{
	ptree params;
	read_xml(file, params);

	outputPath = params.get<string>("parameters.output_path");
	numReps = params.get<int>("parameters.replications");

	cout << outputPath;
}

/****************************************************************************
*																			*
*	Function:	output														*
*																			*
*	Purpose:	To output a parameters object 								*
*																			*
****************************************************************************/

void Parameters::output(ostream& out) const
{
	out << level;
	return;
}

#endif
