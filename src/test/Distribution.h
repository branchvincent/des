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

using namespace std;

// vector<string> valid_distributions = {"exponential", "lognormal", "uniform"};

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

		Distribution();
		Distribution(string type, vector<float> p);
		Distribution(string type, float p);
		Distribution(string type, float p1, float p2);

	//	Inspectors

		const string& getType();
		const vector<float>& getParameters();

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

ostream& operator<<(ostream& out, const Distribution& d);

#endif
