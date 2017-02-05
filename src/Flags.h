/****************************************************************************
*																			*
*	File:		Flags.h														*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the Flags class.      					*
*																			*
****************************************************************************/

#ifndef FLAGS_H
#define FLAGS_H

#include <iostream>
#include <string>
#include <map>
#include "Util.h"

using namespace std;

/****************************************************************************
*																			*
*	Definition of Flags class     											*
*																			*
****************************************************************************/

class Flags
{
//	Public member functions

	public:

    //  Constructor

		Flags(map<string,bool> flags = {});

	//	Inspectors

        bool isOn(string key);

    //  Other member functions

		void output(ostream& out) const;

//	Data members

	private:
        map<string,bool> flags;
};

//	Operators

ostream& operator<<(ostream& out, const Flags& f) {f.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	Flags   													*
*																			*
*	Purpose:	To construct a parameters object							*
*																			*
****************************************************************************/

Flags::Flags(map<string,bool> flags) :
    flags{
        {"traffic", true},
        {"fatigue", true},
        {"verbose", false},
        {"rand", true}
    }
{
    for (const auto& pair : flags)
    {
		string key = util::toLower(pair.first);
        ASSERT(util::contains(this->flags, key), "Incompatible flag '" << key << "'");
		this->flags[key] = pair.second;
    }
}

/****************************************************************************
*																			*
*	Function:	output   													*
*																			*
*	Purpose:	To output flags                  							*
*																			*
****************************************************************************/

void Flags::output(ostream& out) const
{
//  Output true flags

	bool first = true;

    for (const auto& pair : flags)
    {
        if (pair.second)
        {
			if (first)
			{
				out << pair.first << " on";
				first = false;
			}
			else
			{
				out << ", " << pair.first << " on";
			}
        }
    }
}

/****************************************************************************
*																			*
*	Function:	isOn       													*
*																			*
*	Purpose:	To query if the specified flag is on                 		*
*																			*
****************************************************************************/

bool Flags::isOn(string key)
{
    key = util::toLower(key);
    ASSERT(util::contains(flags, key), "Incompatible flag '" << key << "'");
    return flags[key];
}

#endif
