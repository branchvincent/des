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

using namespace std;

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

		Distribution() {}
		// Distribution(float p) : parameters{p} {}
		// Distribution(float p1, float p2) : parameters{p1, p2} {}

	//	Destructor

		virtual ~Distribution() {}

	//	Inspectors

		// vector<float> getParameters() const {return parameters;}

	//	Other member functions

		virtual float rand() = 0;
        virtual void output(ostream& out) const = 0;

//	Data members

	// private:
		// vector<float> parameters;
};

// void Distribution::output(ostream& out) const
// {
// 	out << "Type: " << type << ", ";
// 	out << "Parameters: " << parameters;
// }

#endif
