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
#include <stdlib.h>
#include <boost/log/included/trivial.hpp>
#include "src/Simulation.h"
#include "src/ArgParser.h"
#include "src/Timer.h"
#include "src/Utility.h"

using namespace std;

Flags getFlags(int argc, const char* argv[]);
string getAbsolutePath(string relativePath);

string PATH = "params_OLD.xml";
float util::seed = rand();
default_random_engine util::randNumGen = default_random_engine(util::seed);
vector<float> util::TRAFFIC = {1,1,1};

/****************************************************************************
*																			*
*	Function:	main														*
*																			*
****************************************************************************/

int main(int argc, const char* argv[])
{
    BOOST_LOG_TRIVIAL(trace) << "Starting sim...";
//  Read in parameter file

   Timer t;
   Flags flags = getFlags(argc, argv);
   // string file = getAbsolutePath(argv[1]);
   string file = getAbsolutePath(PATH);

//  Intialize and run simulation

   Simulation sim(file, flags);
   sim.run();
   // if (flags.isOn("verbose"))
   cout << "Runtime: " << t.elapsed() << " s" << endl;

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

/****************************************************************************
*																			*
*	Function:	getAbsolutePath 											*
*																			*
*	Purpose:	To get the absolute filepath from a relative filepath       *
*																			*
****************************************************************************/

string getAbsolutePath(string relativePath)
{
   ASSERT(util::exists(relativePath), "Cannot read " << relativePath);
   const char* absolutePath = realpath(relativePath.c_str(), NULL);
   ASSERT(absolutePath != NULL, "Cannot read " << relativePath);
   return absolutePath;
}
