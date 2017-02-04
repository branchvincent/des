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
#include <iterator>
#include "Util.h"

using namespace std;
// typedef pair<string,bool> value_type;

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
        // bool isFatigueOn() const {return fatigue;}
        // bool isVerboseOn() const {return verbose;}
        // bool isRandOn() const {return rand;}

    //  Other member functions

		void output(ostream& out) const;

//	Data members

	private:
        map<string,bool> flags;
		// bool traffic;
		// bool fatigue;
		// bool verbose;
		// bool rand;
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
//
    for (const auto &pair : flags)
    {
        ASSERT(util::contains(this->flags, pair.first), "Incompatible flag " << pair.first);
        cout << pair.first << " => " << pair.second << endl;
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

    // multimap<string,bool>::iterator it;
    //
    // for(it = next(flags.begin()); it != flags.end(); ++it)
    // {
    //     out << it->first << " on" << endl;
    // }

    for (const auto &pair : flags)
    {
        if (pair.second)
        {
            out << pair.first << " on" << endl;
        }
    }
    return;
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
    ASSERT(util::contains(flags, key), "Incompatible flag " << key);
    return flags[key];
}

#endif
