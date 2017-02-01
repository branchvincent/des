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
#include "Distribution.h"
#include "../Util.h"

using namespace std;

/****************************************************************************
*																			*
*	Definition of Exponential class		     								*
*																			*
****************************************************************************/

class ExponentialDistribution : public Distribution
{
//	Public member functions

	public:

    //  Constructor

		ExponentialDistribution(float lambda) :
			Distribution(lambda), distribution(lambda) {}

	//	Inspectors

		float getLambda() const {return distribution.lambda();}

    //  Other member functions

        float rand() {return distribution(util::randNumGen);}

//	Data members

	private:
		exponential_distribution<float> distribution;
};

#endif
