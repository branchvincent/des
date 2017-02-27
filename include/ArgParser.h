/****************************************************************************
*																			*
*	File:		ArgParser.h													*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the ArgParser class.						*
*																			*
****************************************************************************/

#ifndef ARGPARSER_H
#define ARGPARSER_H

#include <iostream>
#include <string>
#include "../lib/EZOptionParser.h"
#include "Flags.h"

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

		const Flags& getFlags() {return flags;}

	//	Other member functions

		void parse(int argc, const char* argv[]);

//	Private member functions

	private:
		void addFlags();
		void readFlags();
		bool isValid();
		// void handleOpts();
		void printUsage();

//	Data members

	private:
		ezOptionParser p;
		Flags flags;
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

	p.overview = "SHOW command line options.";
	p.syntax = "show [parameterFile] [OPTIONS]";
	p.example = "show ~/Documents/params.xml\n\n";
	addFlags();
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

	p.parse(argc, argv);

//	Check for flag errors

	if (!isValid())
	{
		printUsage();
		exit(1);
	}

//	Handle options

	readFlags();

	return;
}

void ArgParser::addFlags()
{
	p.add(
		"", 	// Default
		false, 	// Required?
		0, 		// Number of args expected
		false, 	// Delimiter if expecting multiple args
		"Display usage instructions.",
		"-h",
		"-help",
		"--help"
	);

	p.add(
		"", 	// Default
		false, 	// Required?
		0, 		// Number of args expected
		false, 	// Delimiter if expecting multiple args
		"Print inputs for debugging.", 		// Help description
		"--debug"		// Flag tokens
	);

	p.add(
		"", 	// Default
		false, 	// Required?
		0, 		// Number of args expected
		false, 	// Delimiter if expecting multiple args
		"Print inputs for debugging.", 		// Help description
		"-v",		// Flag tokens
		"-verbose",
		"--verbose"
	);

	p.add(
		"", 	// Default
		false, 	// Required?
		0, 		// Number of args expected
		false, 	// Delimiter if expecting multiple args
		"Print inputs for debugging.", 		// Help description
		"-d"		// Flag tokens
	);
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

	// cout << "FirstArgs = " << p.firstArgs.size() << endl;
	// cout << "LastArgs = " << p.lastArgs.size() << endl;

	// if (p.firstArgs.size() + p.lastArgs.size() < 2)
	// {
	// 	cerr << "ERROR: Expected at least 1 argument.\n\n";
	// 	return false;
	// }

//	Check for required options

	vector<string> badOpts, badArgs;

//	if (!p.gotRequired(badOpts))
//	{
//		for (string missingOpt : badOpts)
//			cerr << "ERROR: Missing required option " << missingOpt << ".\n\n";
//		return false;
//	}
//
////	Check for correct number of arguments
//
//	if (!p.gotExpected(badOpts))
//	{
//		for (string unexpectedOpt : badOpts)
//			cerr << "ERROR: Got unexpected number of arguments for option " << unexpectedOpt << ".\n\n";
//		return false;
//	}

//	Check for unknown options

	if (p.unknownArgs.size() > 0)
	{
		for (string* unknownOpt : p.unknownArgs)
			cerr << "ERROR: " << &unknownOpt << ".\n\n";
		return false;
	}

	if (!p.gotValid(badOpts, badArgs))
	{
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
*	Function:	handleOpts													*
*																			*
*	Purpose:	To handle the specified options								*
*																			*
****************************************************************************/

void ArgParser::readFlags()
{
//	Check help flag

	if (p.isSet("-h"))
	{
		printUsage();
		exit(0);
	}

//	Check other flags

	flags.add("debug", p.isSet("--debug"));
	flags.add("verbose", p.isSet("-v"));
	flags.add("rand", !p.isSet("-d"));

	// string pretty;
	// p.prettyPrint(pretty);
	// cout << pretty;

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
	p.getUsage(usage);
	cout << usage;
}

#endif
