/****************************************************************************
*																			*
*	File:		OptionParser.h												*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the OptionParser class.					*
*																			*
****************************************************************************/

#ifndef OPTIONPARSER_H
#define OPTIONPARSER_H

#include <iostream>
#include <string>
#include "cxxopts.h"
// #include "flags.h"
#include "util.h"
#include "easylogging++.h"

using namespace std;

/****************************************************************************
*																			*
*	Definition of Options struct											*
*																			*
****************************************************************************/

struct Options
{
	Options(string in = "", string out = "", int reps = 100) :
		inputFile(in), outputPath(out), reps(reps), interval(10) {}
	string inputFile;
	string outputPath;
	int reps;
	int interval;
};

/****************************************************************************
*																			*
*	Definition of OptionParser class										*
*																			*
****************************************************************************/

class OptionParser
{
	public:
		OptionParser();
		Options parse(int argc, const char* argv[]);
	private:
		cxxopts::Options opts;
};

/****************************************************************************
*																			*
*	Function:	OptionParser												*
*																			*
*	Purpose:	To construct an option parser								*
*																			*
****************************************************************************/

OptionParser::OptionParser() : opts("shado", "SHADO command line options\n")
{
	opts.add_options()
	  ("h,help", "Display usage instructions")
	  ("i,input", "Configuration file", cxxopts::value<string>(), "FILE")
	  ("o,output", "Output path", cxxopts::value<string>()->default_value("data/"), "PATH")
	//   ("v,verbose", "Level of verposity", cxxopts::value<int>()->default_value("0"), "LEVEL")
	  ("s,seed", "Random seed", cxxopts::value<unsigned int>()->default_value(to_string(time(0))), "S")
	  ("d,debug", "Debugging mode")
	  //reps
	  //interval size
	  ("err", "erroneous option", cxxopts::value<vector<string>>());
}

/****************************************************************************
*																			*
*	Function:	parse														*
*																			*
*	Purpose:	To parse the command line options							*
*																			*
****************************************************************************/

Options OptionParser::parse(int argc, const char* argv[])
{
	LOG(DEBUG) << "Parsing command line options";

//	Parse options

	try
    {
        opts.parse_positional(vector<string>{"input", "output", "err"});
        opts.parse(argc, argv);
    }
    catch (const cxxopts::OptionException& e)
    {
        cout << "Error parsing options: " << e.what() << "\n\n";
		cout << opts.help() << endl;
        exit(1);
    }

//	Check for help flag

	if (opts.count("help"))
	{
		cout << opts.help() << endl;
		exit(0);
	}

//	Check for errors

	if (not opts.count("input"))
	{
		cout << "Please specify input file.\n\n";
		cout << opts.help() << endl;
  	  	exit(1);
	}
	else if (not util::exists(opts["input"].as<string>()))
	{
		cout << "Error parsing options: File '" << opts["input"].as<string>();
		cout << "' is not valid\n\n";
		cout << opts.help() << endl;
  	  	exit(1);
	}
	else if (opts.count("err"))
	{
		string badOpt = opts["err"].as<vector<string>>()[0];
		cout << "Error parsing options: ";
		cout << "Option '" << badOpt << "' does not exist\n\n";
		cout << opts.help() << endl;
  	  	exit(1);
	}

//	Handle options

	if (opts.count("debug"))
	{
		// cout << "Debug" << endl;
		el::Loggers::setLoggingLevel(el::Level::Debug);
	}
	// if (opts.count("verbose"))
	// {
	// 	cout << "Verbose" << endl;
	// }

//	Set verbosity

	// Loggers::setLoggingLevel(Level::Debug);
	// map<char,int> verbose = {{'l' : el::Level::Debug}, {'m' : el::Level::}, {}}

//	Set seed

	srand(opts["seed"].as<unsigned int>());
	util::seed = rand();
	util::randNumGen = default_random_engine(util::seed);

	LOG(DEBUG) << "Setting seed to " << util::seed;
	return Options(opts["input"].as<string>(), opts["output"].as<string>());
}

#endif
