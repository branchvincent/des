/****************************************************************************
*																			*
*	File:		Batch.h														*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the Batch struct.							*
*																			*
****************************************************************************/

#ifndef BATCH_H
#define BATCH_H

#include <iostream>
#include <string>
#include "shift.h"
#include "utility.h"
#include "pugixml.h"

using namespace std;
using pugi::xml_document;
using pugi::xml_node;

/****************************************************************************
*																			*
*	Definition of Batch struct		     						        	*
*																			*
****************************************************************************/

struct Batch
{
	Batch(const xml_node& data);
    string type;
	int count;
	Shift shift;
	string partnerType;
};

Batch::Batch(const xml_node& data)
{
//	Read attributes

	xml_node team = data.child("team");
	xml_node shift = data.child("shift");
	xml_node traffic = data.child("traffic");

	type = util::toLower((string)team.attribute("type").value());
	partnerType = util::toLower(team.attribute("partner").value());
	string count_s = team.attribute("num").value();
	string start_s = shift.attribute("start").value();
	string stop_s = shift.attribute("stop").value();

//	Check for errors

	LOG_IF(type == "", FATAL) << "XML Error: Could not read batch attribute 'type'";
	LOG_IF(partnerType == "", FATAL) << "XML Error: Could not read batch attribute 'partner'";
	LOG_IF(count_s == "", FATAL) << "XML Error: Could not read batch attribute 'num'";
	LOG_IF(start_s == "", FATAL) << "XML Error: Could not read batch attribute 'start'";
	LOG_IF(stop_s == "", FATAL) << "XML Error: Could not read batch attribute 'stop'";

//	Update

	count = atoi(count_s.c_str());
	this->shift = Shift(start_s, stop_s);
}

#endif
