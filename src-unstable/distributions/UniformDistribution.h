/****************************************************************************
*																			*
*	File:		UniformDistribution.h										*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the UniformDistribution class.			*
*																			*
****************************************************************************/

#ifndef UNIFORMDISTRIBUTION_H
#define UNIFORMDISTRIBUTION_H

#include <iostream>
#include <string>
#include <random>
#include "Distribution.h"
#include "../Utility.h"

using namespace std;

/****************************************************************************
*																			*
*	Definition of UniformDistribution class		     						*
*																			*
****************************************************************************/

class UniformDistribution : public Distribution
{
//	Public member functions

	public:

    //  Constructor

        inline UniformDistribution(vector<float> parameters);
		UniformDistribution(float min, float max) : dist(min, max) {}

	//	Inspectors

        float getMean() const {return (dist.a()+dist.b())/2;}
		float getMin() const {return dist.a();}
		float getMax() const {return dist.b();}

    //  Other member functions

        float rand() {return dist(util::randNumGen);}
        inline void output(ostream& out) const;

//	Data members

	private:
		uniform_real_distribution<float> dist;
};

inline ostream& operator<<(ostream& out, const UniformDistribution& d) {d.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	ExponentialDistribution										*
*																			*
*	Purpose:	To help construct an exponential distribution				*
*																			*
****************************************************************************/

UniformDistribution::UniformDistribution(vector<float> parameters)
{
	ASSERT(parameters.size() == 2, "Uniform distribution requires 2 parameters");
	dist = uniform_real_distribution<float>(parameters[0], parameters[1]);
}

/****************************************************************************
*																			*
*	Function:	output														*
*																			*
*	Purpose:	To output an exponential distribution						*
*																			*
****************************************************************************/

void UniformDistribution::output(ostream& out) const
{
    out << "Uniform: min = " << dist.a();
    out << ", max = " << dist.b();
}

#endif
