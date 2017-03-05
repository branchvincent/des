/****************************************************************************
*																			*
*	File:		Distribution.h												*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the Distribution class.					*
*																			*
****************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "distribution.h"
#include "utility.h"

using namespace std;

vector<string> valid_distributions = {"exponential", "lognormal", "uniform"};

//	Constuctors

Distribution::Distribution() : type("exponential"), parameters{0.1} {construct();}
Distribution::Distribution(string type, vector<float> p) : type(type), parameters(p) {construct();}
Distribution::Distribution(string type, float p) : type(type), parameters{p} {construct();}
Distribution::Distribution(string type, float p1, float p2) : type(type), parameters{p1, p2} {construct();}

//	Inspectors

// const string& Distribution::getType() const {return type;}
// const vector<float>& Distribution::getParameters() const {return parameters;}

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
	ASSERT(util::contains(valid_distributions, type), "'" << type << "' is not a valid distribution");

//	Set distribution

	if (type == "exponential")
	{
		ASSERT(parameters.size() == 1, "Exponential distribution requires 1 parameter");
		exp_distribution = exponential_distribution<float>(parameters[0]);
	}
	else if (type == "lognormal")
	{
		ASSERT(parameters.size() == 2, "Lognormal distribution requires 2 parameters");
		log_distribution = lognormal_distribution<float>(parameters[0], parameters[1]);
	}
	else
	{
		ASSERT(parameters.size() == 2, "Uniform distribution requires 2 parameters");
		uni_distribution = uniform_real_distribution<float>(parameters[0], parameters[1]);
	}
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
	out << type << " distribution with " << parameters;
}

//	Operators

ostream& operator<<(ostream& out, const Distribution& d) {d.output(out); return out;}
