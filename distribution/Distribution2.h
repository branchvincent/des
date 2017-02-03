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
#include "../Util.h"

using namespace std;

/****************************************************************************
*																			*
*	Definition of Distribution class										*
*																			*
****************************************************************************/

template <class T>
class Distribution
{
//	Public member functions

	public:

	//	Constructor

		Distribution() {}
		Distribution(string type, float p) : type(type), parameters{p} {}
		Distribution(string type, float p1, float p2) : type(type), parameters{p1, p2} {}

	//	Inspectors

		string getType() const {return type;}
		vector<float> getParameters() const {return parameters;}

	//	Other member functions

		float rand()
		{
			if (type == "exponential") return exp_distribution(util::randNumGen);
			else if (type == "lognormal") return log_distribution(util::randNumGen);
			else return uni_distribution(util::randNumGen);
		}

//	Data members

	private:
		string type;
		vector<float> parameters;
		exponential_distribution<float> exp_distribution;
		lognormal_distribution<float> log_distribution;
		uniform_real_distribution<float> uni_distribution;
};

#endif
