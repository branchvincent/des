/****************************************************************************
*																			*
*	File:		Distribution.h												*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the Distribution class.					*
*																			*
****************************************************************************/

#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "Util.h"

using namespace std;

vector<string> valid_distributions = {"exponential", "lognormal", "uniform"};

/****************************************************************************
*																			*
*	Definition of Distribution class										*
*																			*
****************************************************************************/

class Distribution
{
//	Public member functions

	public:

	//	Constructor

		Distribution(string type, vector<float> p) : type(type), parameters(p) {construct();}
		Distribution(string type, float p) : type(type), parameters{p} {construct();}
		Distribution(string type, float p1, float p2) : type(type), parameters{p1, p2} {construct();}

	//	Inspectors

		string getType() const {return type;}
		vector<float> getParameters() const {return parameters;}

	//	Other member functions

		float rand();
		void output(ostream& out) const;

//	Private member functions

	private:
		void construct();

//	Data members

	private:
		string type;
		vector<float> parameters;
		exponential_distribution<float> exp_distribution;
		lognormal_distribution<float> log_distribution;
		uniform_real_distribution<float> uni_distribution;
};

//	Operators

ostream& operator<<(ostream& out, const Distribution& d) {d.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	construct													*
*																			*
*	Purpose:	To help construct a distribution							*
*																			*
****************************************************************************/

void Distribution::construct()
{
//	Check distribution type

	type = util::toLower(type);
	bool validDistribution = (find(valid_distributions.begin(), valid_distributions.end(), type) != valid_distributions.end());
	ASSERT(validDistribution, "'" << type << "' is not a valid distribution");

//	Set distribution

	if (type == "exponential")
		exp_distribution = exponential_distribution<float>(parameters[0]);
	else if (type == "lognormal")
		log_distribution = lognormal_distribution<float>(parameters[0], parameters[1]);
	else
		uni_distribution = uniform_real_distribution<float>(parameters[0], parameters[1]);
}

/****************************************************************************
*																			*
*	Function:	rand														*
*																			*
*	Purpose:	To return a random number									*
*																			*
****************************************************************************/

float Distribution::rand()
{
	if (type == "exponential")
		return exp_distribution(util::randNumGen);
	else if (type == "lognormal")
		return log_distribution(util::randNumGen);
	else
		return uni_distribution(util::randNumGen);
}

/****************************************************************************
*																			*
*	Function:	output														*
*																			*
*	Purpose:	To output a distribution									*
*																			*
****************************************************************************/

void Distribution::output(ostream& out) const
{
	out << "Type: " << type << ", ";
	out << "Parameters: " << parameters;
	return;
}

#endif
