/****************************************************************************
*																			*
*	File:		Parameters.h												*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the Parameters class.						*
*																			*
****************************************************************************/

#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "Shift.h"

using namespace std;
using boost::property_tree::ptree;

/****************************************************************************
*																			*
*	Definition of Parameters class		     						        *
*																			*
****************************************************************************/

class Parameters
{
//	Public member functions

	public:

    //  Constructor

		Parameters(string file);

	//	Inspectors

    //  Other member functions

		void output

//	Data members

	public:
    //	General settings

        string outputPath;
		int numReps;
		int numPhases;
		int intSize;
		Shift shift;
		vector<float> trafficLevels;
		// vector<Team> teams;
		// vector<Batches> batches;

	//	Flags

		bool isTrafficOn;
		bool isFatigueOn;
		bool isVerboseOn;
		bool isRandOn;
};

//	Operators

ostream& operator<<(ostream& out, const Parameters& p) {p.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	Parameters													*
*																			*
*	Purpose:	To construct a parameters object							*
*																			*
****************************************************************************/

Parameters::Parameters(string file) :
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
	out << "Output path = " << outputPath << endl;
	out << "Shift = " << shift << endl;
	out << "Number of replications = " << numReps << endl;
	out << "Traffic levels = ";

	return;
}

#endif
