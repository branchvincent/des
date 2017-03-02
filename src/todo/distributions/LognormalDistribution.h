/****************************************************************************
*																			*
*	File:		LognormalDistribution.h										*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the LognormalDistribution class.			*
*																			*
****************************************************************************/

#ifndef LOGNORMALDISTRIBUTION_H
#define LOGNORMALDISTRIBUTION_H

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <cmath>
#include "distribution.h"
#include "../Utility.h"

using namespace std;

/****************************************************************************
*																			*
*	Definition of LognormalDistribution class		     					*
*																			*
****************************************************************************/

class LognormalDistribution : public Distribution
{
//	Public member functions

	public:

    //  Constructor

        inline LognormalDistribution(vector<float> parameters);
		LognormalDistribution(float mean, float stdDev) : dist(mean, stdDev) {}

	//	Inspectors

        float getMean() const {log(d.m()) - pow(dist.s(), 2)/2;}
        float getStdDev() const {}
		float getLogMean() const {return dist.m();}
		float getLogStdDev() const {return dist.s();}

    //  Other member functions

        float rand() {return dist(util::randNumGen);}
        inline void output(ostream& out) const;

//	Data members

	private:
		lognormal_distribution<float> dist;
};

inline ostream& operator<<(ostream& out, const LognormalDistribution& d) {d.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	ExponentialDistribution										*
*																			*
*	Purpose:	To help construct an exponential distribution				*
*																			*
****************************************************************************/

LognormalDistribution::LognormalDistribution(vector<float> parameters)
{
	ASSERT(parameters.size() == 2, "Lognormal distribution requires 2 parameters");
	dist = lognormal_distribution<float>(parameters[0], parameters[1]);
}

/****************************************************************************
*																			*
*	Function:	output														*
*																			*
*	Purpose:	To output an exponential distribution						*
*																			*
****************************************************************************/

void LognormalDistribution::output(ostream& out) const
{
    out << "Lognormal: mean = " << dist.m();
    out << ", stddev = " << dist.s();
}

#endif
