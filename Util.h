/****************************************************************************
*																			*
*	File:		Util.h														*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the Util class.							*
*																			*
****************************************************************************/

#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>
#include <random>

using namespace std;

/****************************************************************************
*																			*
*	Definition of Util namespace											*
*																			*
****************************************************************************/

namespace util
{
//	Public member functions

	float seed = rand();
	default_random_engine randNumGen(seed);
	string x = "hi";

	vector<float> TRAFFIC = {1,1,1};
}




template <class T>
ostream& operator <<(ostream& out, vector<T>& v)
{
    out << "[";
	for (auto const& vi : v)
        out << " " << vi;
    out << " ]";
    return out;
}

#endif
