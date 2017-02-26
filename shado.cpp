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
#include "lib/EasyLoggingInc.h"
#include "src/Simulation.h"
#include "src/ArgParser.h"
#include "src/Timer.h"
#include "src/Utility.h"
INITIALIZE_EASYLOGGINGPP

using namespace std;

Flags getFlags(int argc, const char* argv[]);
string getAbsolutePath(string relativePath);
void initLogger(int argc, const char** argv);

string PATH = "in/params_test.xml";
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
//  Read in parameter file

   Timer t;
   initLogger(argc, argv);
   Flags flags = getFlags(argc, argv);
   string file = getAbsolutePath(PATH); //(argv[1]);

//  Intialize and run simulation

   Simulation sim(file, flags);
   sim.run();
   LOG(INFO) << "Runtime: " << t.elapsed() << " s";

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

void initLogger(int argc, const char** argv)
{
    el::Configurations conf("lib/EasyLogging.conf");
    el::Loggers::reconfigureAllLoggers(conf);
    el::Loggers::addFlag(el::LoggingFlag::HierarchicalLogging);
    // conf.setToDefault();
    START_EASYLOGGINGPP(argc, argv);
}
