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
#include "Distribution.h"
#include "../Util.h"

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

		UniformDistribution(float min, float max) :
			Distribution(min, max), distribution(min, max) {}

	//	Inspectors

		float getMin() const {return distribution.a();}
		float getMax() const {return distribution.b();}

    //  Other member functions

        float rand() {return distribution(util::randNumGen);}

//	Data members

	private:
		uniform_real_distribution<float> distribution;
};

#endif
