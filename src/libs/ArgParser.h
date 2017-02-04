/****************************************************************************
*																			*
*	File:		ArgParser.h													*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jan 6, 2016													*
*																			*
*	Purpose:	This file defines the ArgParser class.						*
*																			*
****************************************************************************/

#ifndef ARGPARSER_H
#define ARGPARSER_H

#include <iostream>
#include <string>
#include "argParserLib.h"

using namespace std;
using namespace ez;

/****************************************************************************
*																			*
*	Definition of ArgParser class											*
*																			*
****************************************************************************/

class ArgParser
{
//	Public member functions

	public:

	//	Constructor

		ArgParser();

	//	Inspectors

		const ezOptionParser& getParser() {return opt;}

	//	Other member functions

		void parse(int argc, const char* argv[]);

//	Private member functions

	private:
		bool isValid();
		void handleOpts();
		void printUsage();

//	Data members

	private:
		ezOptionParser opt;
};

/****************************************************************************
*																			*
*	Function:	ArgParser													*
*																			*
*	Purpose:	To construct an argument parser								*
*																			*
****************************************************************************/

ArgParser::ArgParser()
{
//	Set details
	
	opt.overview = "SHOW command line options.";
	opt.syntax = "show [parameterFile] [OPTIONS]";
	opt.example = "show ~/Documents/params.txt\n\n";
	
//	Add options

	opt.add(
		"", 	// Default
		false, 	// Required?
		0, 		// Number of args expected
		false, 	// Delimiter if expecting multiple args
		"Display usage instructions.", 		// Help description
		"-h",		// Flag tokens
		"-help",
		"--help"
	);
	
	opt.add(
		"", 	// Default
		false, 	// Required?
		0, 		// Number of args expected
		false, 	// Delimiter if expecting multiple args
		"Print inputs for debugging.", 		// Help description
		"--debug"		// Flag tokens
	);
	
	opt.add(
		"", 	// Default
		false, 	// Required?
		0, 		// Number of args expected
		false, 	// Delimiter if expecting multiple args
		"Print inputs for debugging.", 		// Help description
		"-v",		// Flag tokens
		"-verbose",
		"--verbose"
	);
}

/****************************************************************************
*																			*
*	Function:	parse														*
*																			*
*	Purpose:	To parse the command line options							*
*																			*
****************************************************************************/

void ArgParser::parse(int argc, const char* argv[])
{
//	Parse arguments
	
	opt.parse(argc, argv);
	
//	Check for flag errors
	
	if (!isValid())
	{
		printUsage();
		exit(1);
	}
	
//	Handle options
	
	handleOpts();
	
	return;
}

/****************************************************************************
*																			*
*	Function:	isValid														*
*																			*
*	Purpose:	To check the validity of the provided options				*
*																			*
****************************************************************************/

bool ArgParser::isValid()
{
//	Check for required argument
	
	cout << "FirstArgs = " << opt.firstArgs.size() << endl;
	cout << "LastArgs = " << opt.lastArgs.size() << endl;
	
	if (opt.firstArgs.size() + opt.lastArgs.size() < 2)
	{
		cerr << "ERROR: Expected at least 1 argument.\n\n";
		return false;
	}
	
//	Check for required options
	
	vector<string> badOpts, badArgs;
	
//	if (!opt.gotRequired(badOpts))
//	{
//		for (string missingOpt : badOpts)
//			cerr << "ERROR: Missing required option " << missingOpt << ".\n\n";
//		return false;
//	}
//	
////	Check for correct number of arguments
//	
//	if (!opt.gotExpected(badOpts))
//	{
//		for (string unexpectedOpt : badOpts)
//			cerr << "ERROR: Got unexpected number of arguments for option " << unexpectedOpt << ".\n\n";
//		return false;
//	}
//	
////	Check for unknown options
//	
	if (opt.unknownArgs.size() > 0)
	{
		for (string* unknownOpt : opt.unknownArgs)
			cerr << "ERROR: " << &unknownOpt << ".\n\n";
		return false;
	}
	
	if (!opt.gotValid(badOpts, badArgs))
	{
		cout << "HERE" << endl;
		for (string badOpt : badOpts)
			cerr << "ERROR: " << badOpt << ".\n\n";
		for (string badArg : badArgs)
			cerr << "ERROR: " << badArg << ".\n\n";
		return false;
	}
	
	return true;
}

/****************************************************************************
*																			*
*	Function:	handleOpts()												*
*																			*
*	Purpose:	To handle the specified options								*
*																			*
****************************************************************************/

void ArgParser::handleOpts()
{
//	Check help flag
	
	if (opt.isSet("-h"))
	{
		printUsage();
		exit(0);
	}
	
//	Check debug flag
	
	if (opt.isSet("--debug"))
	{
		string pretty;
		opt.prettyPrint(pretty);
		cout << pretty;
	}
	
//	Check for verbose flag
	
	if (opt.isSet("-v"))
	{
		cout << "Verbose" << endl;
	}
	
	return;
}

/****************************************************************************
*																			*
*	Function:	printUsage													*
*																			*
*	Purpose:	To print the usage of the program's command line arguments	*
*																			*
****************************************************************************/

void ArgParser::printUsage()
{
	string usage;
	opt.getUsage(usage);
	cout << usage;
	return;
}

#endif
