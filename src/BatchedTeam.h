/****************************************************************************
*																			*
*	File:		BatchedTeam.h												*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the BatchedTeam class.					*
*																			*
****************************************************************************/

#ifndef TEAM_H
#define TEAM_H

#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "Team.h"

using namespace std;
using boost::property_tree::ptree;

/****************************************************************************
*																			*
*	Definition of BatchedTeam class		     						        	*
*																			*
****************************************************************************/

//  Notes
//  - Shared task to op with current lowest priority
//  - Add fatigue for just human operators
//  - Add shared task ID as a subset
//  - Pass all queues to each operator for interruptions

class BatchedTeam
{
//  Friend class

//    friend Operator;

//	Public member functions

	public:

	//	Constructor

		BatchedTeam();

	// 	Inspector


    // 	Mutators


    //  Other member functions

        void output(ostream& out) const;

//	Data members

	private:


};

ostream& operator<<(ostream& out, const BatchedTeam& b) {b.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	BatchedTeam													*
*																			*
*	Purpose:	To construct a new team										*
*																			*
****************************************************************************/

BatchedTeam::BatchedTeam() :
{

}

#endif
