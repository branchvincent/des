/****************************************************************************
*																			*
*	File:		Utility.cpp													*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the Util namespace.					    *
*																			*
****************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <sstream>
#include <algorithm>
#include "utility.h"

using namespace std;

/****************************************************************************
*																			*
*	Definition of Util namespace											*
*																			*
****************************************************************************/

//	Public member functions

string util::toLower(string s)
    {transform(s.begin(), s.end(), s.begin(), ::tolower); return s;}

// template <class T> bool util::contains(vector<T>& vec, const T& data)
//     {return find(vec.begin(), vec.end(), data) != vec.end();}

// template <class T, class P> bool util::contains(map<T,P>& m, const T& key)
//     {return m.find(key) != m.end();}

// template <typename T> void util::checkIndex(const vector<T>& vec, int index)
//     {ASSERT(index >= 0 && index < vec.size(), "Invalid array index");}

//  Data members
// float util::seed;// = rand();
// default_random_engine util::randNumGen(0);
// vector<float> util::TRAFFIC;// = {1,1,1};

/****************************************************************************
*																			*
*	Function:	toVector       												*
*																			*
*	Purpose:	To convert the string to a vector                           *
*																			*
****************************************************************************/

// template <class T>
// vector<T> util::toVector(string data, char delimiter)
// {
// //  Replace delimiter with white space
//
//     for (int i = 0; i < data.size(); i++)
//         if (data[i] == delimiter)
//             data[i] = ' ';
//
// //  Fill vector
//
//     T temp;
//     vector<T> vec;
//     istringstream in(data);
//     while (in >> temp)
//         vec.push_back(temp);
//
//     // string stemp;
//     // while (getline(in, stemp, delimiter))
//     // {
//     //     istringstream iss(stemp);
//     //     iss >> temp;
//     //     vec.push_back(temp);
//     // }
//
//     return vec;
// }

/****************************************************************************
*																			*
*	Function:	operator<<     												*
*																			*
*	Purpose:	To output a vector                                          *
*																			*
****************************************************************************/

// template <class T>
// ostream& operator<<(ostream& out, vector<T>& v)
// {
//     out << "[";
//     if (v.size() > 0)
//         out << v[0];
//     for (int i = 1; i < v.size(); i++)
//         out << ", " << v[i];
//     out << "]";
//     return out;
// }
//
// template <class T>
// ostream& operator<<(ostream& out, const vector<T>& v)
// {
//     out << "[";
//     if (v.size() > 0)
//         out << v[0];
//     for (int i = 1; i < v.size(); i++)
//         out << ", " << v[i];
//     out << "]";
//     return out;
// }
