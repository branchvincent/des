/****************************************************************************
*																			*
*	File:		shado.cpp													*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file executes the discrete event simulation for the    *
*               specified parameters.                                       *
*																			*
****************************************************************************/

// #define ELPP_NO_DEFAULT_LOG_FILE
// #define ELPP_THREAD_SAFE
#include <iostream>
#include <string>
#include <stdlib.h>
#include <random>
#include "../lib/EasyLogging.h"
#include "Simulation.h"
#include "ArgParser.h"
#include "Timer.h"
#include "Utility.h"
INITIALIZE_EASYLOGGINGPP

using namespace std;

Flags getFlags(int argc, const char* argv[]);
string getAbsolutePath(string relativePath);
void initLogger(int argc, const char** argv);

// srand((unsigned int) time(0));
string PATH = "/Users/Branch/Documents/Research/fra/shado/config/params_test.xml";
float util::seed = rand();
default_random_engine util::randNumGen = default_random_engine(util::seed);
// vector<float> util::TRAFFIC = {1,1,1};

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
    string file = PATH; //getAbsolutePath(PATH); //(argv[1]);

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
   LOG_IF(!util::exists(relativePath), FATAL) << "Cannot read " << relativePath;
   const char* absolutePath = realpath(relativePath.c_str(), NULL);
   LOG_IF(absolutePath == NULL, FATAL) << "Cannot read " << relativePath;
   return absolutePath;
}

void initLogger(int argc, const char** argv)
{
    // el::Configurations conf("lib/EasyLogging.conf");
	el::Configurations conf("/Users/Branch/Documents/Research/fra/shado/config/logger.conf");
    el::Loggers::reconfigureAllLoggers(conf);
    // el::Loggers::addFlag(el::LoggingFlag::HierarchicalLogging);
    // conf.setToDefault();
    START_EASYLOGGINGPP(argc, argv);
}
