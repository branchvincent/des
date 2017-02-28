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
#include "Shift.h"
// #include "Traffic.h"
#include "../deps/PugiXML.h"

using namespace std;
using pugi::xml_node;

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

		Parameters(xml_node& data);
		Parameters(string file);

	//	Inspectors

    //  Other member functions

		void output(ostream& out) const;

//	Data members

	public:
    //	General settings

        string outputPath;
		int numReps;
		// int numPhases;
		int intSize;
		// Shift shift;
		// Traffic traffic;
		// vector<Team> teams;
		// vector<Batches> batches;
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

Parameters::Parameters(xml_node& data) : intSize(600)
{
	outputPath = data.child_value("output_path");
    numReps = atoi(data.child_value("replications"));
}

Parameters::Parameters(string file) :
	numReps(2),		// TODO: 100
	// numPhases(3),
	intSize(10)
{
//	Read parameter file

	// ptree params;
	// read_xml(file, params);

//	Set parameters

	// outputPath = params.get<string>("parameters.output_path");
	// numReps = params.get<int>("parameters.replications");
	// traffic = util::toVector<char>(params.get<string>("parameters.traffic"));
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
	// out << "Shift = " << shift << endl;
	out << "Replications = " << numReps << endl;
	// out << "Traffic = " << traffic;
}

#endif
