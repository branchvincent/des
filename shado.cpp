/****************************************************************************
*																			*
*	File:		run.cpp													    *
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file executes the discrete event simulation for the    *
*               specified parameters.                                       *
*																			*
****************************************************************************/

#include <iostream>
#include <string>
#include "src/Simulation.h"
#include "src/ArgParser.h"
#include "src/Timer.h"

using namespace std;

Flags getFlags(int argc, const char* argv[]);

/****************************************************************************
*																			*
*	Function:	main														*
*																			*
****************************************************************************/

int main(int argc, const char* argv[])
{
//  Read in parameter file

    Timer t;
    Flags flags = getFlags(argc, argv);
    string file = argv[2];

//  Intialize and run simulation

    Simulation sim(file, flags);
	// sim.run();
    if (flags.isOn("verbose")) cout << "Runtime: " << t.elapsed() << " s";

	return 0;
}

/****************************************************************************
*																			*
*	Function:	getFlags    												*
*																			*
*	Purpose:	To get the flags from the command line                      *
*																			*
****************************************************************************/

Flags getFlags(int argc, const char* argv[])
{
    ArgParser parser;
	parser.parse(argc, argv);
    return parser.getFlags();
}
