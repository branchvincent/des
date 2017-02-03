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

#define ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            cerr << "ASSERTION ERROR: " << message << "." << endl; \
            cerr << "In " << __FILE__ << ", line " << __LINE__ << ": '" << #condition << "' failed" << endl; \
			cerr << "Exiting..." << endl; \
            terminate(); \
        } \
    } while (false)

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

// void Assert(bool condition, string message)
// {
// 	if (!condition)
// 	{
// 		cout << message << endl;
// 		assert(condition);
// 	// 	cerr << "Assertion `" #condition "` failed in " << __FILE__ << " line " << __LINE__ << ": " << message << endl;
// 	// 	terminate();
// 	}
// }

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
