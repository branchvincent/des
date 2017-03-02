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
#include "flags.h"
#include "util.h"

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
*	Purpose:	To construct an argument parser								*
*																			*
****************************************************************************/

OptionParser::OptionParser() : opts("shado", "SHADO command line options\n")
{
	opts.add_options()
	  ("h,help", "Display usage instructions")
	  ("i,input", "Configuration file", cxxopts::value<string>(), "FILE")
	  ("o,output", "Output path", cxxopts::value<string>()->default_value("data/"), "PATH")
	  ("d,debug", "Debugging mode")
	  ("v,verbose", "Be verpose")
	  ("s,seed", "Random seed", cxxopts::value<unsigned int>()->default_value(to_string(time(0))), "S")
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
		//TODO
		cout << "Debug" << endl;
	}
	if (opts.count("verbose"))
	{
		//TODO
		cout << "Verbose" << endl;
	}

	srand(opts["seed"].as<unsigned int>());
	util::seed = rand();
	util::randNumGen = default_random_engine(util::seed);

	return Options(opts["input"].as<string>(), opts["output"].as<string>());
}

#endif
