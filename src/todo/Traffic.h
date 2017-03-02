/****************************************************************************
*																			*
*	File:		Traffic.h													*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the Traffic class.						*
*																			*
****************************************************************************/

#ifndef TRAFFIC_H
#define TRAFFIC_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "utility.h"

using namespace std;

vector<char> valid_levels = {'l', 'm', 'h'};
map<char,float> multiplier_map = {{'l',2}, {'m',1}, {'h',0.5}};

/****************************************************************************
*																			*
*	Definition of Traffic class				     					        *
*																			*
****************************************************************************/

class Traffic
{
//	Public member functions

	public:

    //  Constructor

		Traffic() : levels(), multipliers() {}
		Traffic(vector<char> levels);

	//	Inspectors

		vector<char> getTrafficLevels() const {return levels;}
		char getTrafficLevel(int i) const
			{util::checkIndex(levels, i); return levels[i];}
		vector<float> getMultipliers() const {return multipliers;}
		float getMultiplier(int i) const
			{util::checkIndex(multipliers, i); return multipliers[i];}

    //  Other member functions

		void output(ostream& out) const {out << levels;}

//	Data members

	public:
		vector<char> levels;
		vector<float> multipliers;
};

//	Operators

ostream& operator<<(ostream& out, const Traffic& t) {t.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	Traffic														*
*																			*
*	Purpose:	To construct a traffic object								*
*																			*
****************************************************************************/

Traffic::Traffic(vector<char> levels) : levels(levels)
{
	for (char& level : levels)
	{
		ASSERT(util::contains(valid_levels, level), level << " is not a valid traffic level");
		multipliers.push_back(multiplier_map[level]);
	}
}

#endif
