/****************************************************************************
*																			*
*	File:		ExponentialDistribution.h									*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the ExponentialDistribution class.		*
*																			*
****************************************************************************/

#ifndef EXPONENTIALDISTRIBUTION_H
#define EXPONENTIALDISTRIBUTION_H

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "distribution.h"
#include "../Utility.h"

using namespace std;

/****************************************************************************
*																			*
*	Definition of ExponentialDistribution class		     					*
*																			*
****************************************************************************/

class ExponentialDistribution : public Distribution
{
//	Public member functions

	public:

    //  Constructor

        inline ExponentialDistribution(vector<float> parameters);
		ExponentialDistribution(float lambda) : dist(lambda)
            {ASSERT(lambda >= 0, "Lambda must be greater than 0");}

	//	Inspectors

        float getMean() const {return 1/dist.lambda();}
        float getBeta() const {return 1/dist.lambda();}
		float getLambda() const {return dist.lambda();}

    //  Other member functions

        float rand() {return dist(util::randNumGen);}
        inline void output(ostream& out) const;

//	Data members

	private:
		exponential_distribution<float> dist;
};

inline ostream& operator<<(ostream& out, const ExponentialDistribution& d) {d.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	ExponentialDistribution										*
*																			*
*	Purpose:	To help construct an exponential distribution				*
*																			*
****************************************************************************/

ExponentialDistribution::ExponentialDistribution(vector<float> parameters)
{
	ASSERT(parameters.size() == 1, "Exponential distribution requires 1 parameter");
    ASSERT(parameters[0] >= 0, "Lambda must be greater than 0");
	dist = exponential_distribution<float>(parameters[0]);
}

/****************************************************************************
*																			*
*	Function:	output														*
*																			*
*	Purpose:	To output an exponential distribution						*
*																			*
****************************************************************************/

void ExponentialDistribution::output(ostream& out) const
{
    out << "Exponential: lambda = " << dist.lambda();
}

#endif
