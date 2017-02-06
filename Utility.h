/****************************************************************************
*																			*
*	File:		Utility.h													*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the Util namespace.					    *
*																			*
****************************************************************************/

#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <sstream>
#include <algorithm>

using namespace std;

//  Assert function to output error message

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

    template <class T> vector<T> toVector(string data, char delimiter = ',');
    string toLower(string s);
    template <class T> bool contains(vector<T>& vec, const T& data);
    template <class T, class P> bool contains(map<T,P>& m, const T& key);
    template <typename T> void checkIndex(const vector<T>& vec, int index);

//  Data members

    extern float seed; //= rand();
    extern default_random_engine randNumGen;
    extern vector<float> TRAFFIC; // = {1,1,1};
}

//  Operators

template <class T> ostream& operator<<(ostream& out, vector<T>& v);
template <class T> ostream& operator<<(ostream& out, const vector<T>& v);

#endif
