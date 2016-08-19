/****************************************************************************
*																			*
*	File:		LoadParameters.h                                            *
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jul 12, 2016												*
*																			*
*	Purpose:	This file defines the LoadParameters class.                 *
*																			*
****************************************************************************/

#ifndef LOADPARAMETERS_H
#define LOADPARAMETERS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

//	Type definitions

template <typename T>
using Matrix2D = vector<vector<T> >;
template <typename T>
using Matrix3D = vector<vector<vector<T> > >;

/****************************************************************************
*																			*
*	Definition of LoadParameters class                                      *
*																			*
****************************************************************************/

class LoadParameters
{
//	Public member functions

	public:

	//	Constructor
		
		LoadParameters(string file);

	//	Inspectors
    
//        string getOutPath() {return outputPath;}
//		float getNumHours() {return numHours;}
//        vector<float> getTraffic() {return traffic;}
//        float getNumReps() {return numReps;}
//		vector<int> getOps() {return ops;}

//	Private member functions
	
	private:
		void readTraff(fstream& fin, vector<float>& traff);
		void readLine(fstream& fin, string& line);
		void readString(fstream& fin, string& paramStrg);
		template <typename T> void readVal(fstream& fin, T& paramVal);
		template <typename T> void readArr(fstream& fin, vector<T>& paramArr, bool invert = false);
		bool isInverted(char c) {return c == 'E';}
	
//	Public data members

	public:
	//	General settings
	
        string outputPath;
        float numHours;
        vector<float> traffic;
        float numReps;
        vector<int> ops;
	
	//	Task settings
	
		int numTaskTypes;
        vector<string> taskNames;
        Matrix2D<int> taskPrty;
        vector<char> arrDists;
        Matrix2D<float> arrPms;
        vector<char> serDists;
        Matrix2D<float> serPms;
        vector<char> expDists;
        Matrix2D<float> expPmsLo;
        Matrix2D<float> expPmsHi;
		Matrix2D<int> affByTraff;
		Matrix2D<int> opNums;
};

/****************************************************************************
*																			*
*	Function:	LoadParameters                                              *
*																			*
*	Purpose:	To construct new parameters                                 *
*																			*
****************************************************************************/

LoadParameters::LoadParameters(string file)
{
//  Open parameter file
    
    fstream fin(file);
    
    if (!fin)
    {
        cerr << "Error: Cannot open parameter file. Exiting..." << endl;
        exit(1);
    }
    
//	Read parameter file
	
	readString(fin, outputPath);
	readVal(fin, numHours);
	readTraff(fin, traffic);
	readVal(fin, numReps);
	readArr(fin, ops);
	readVal(fin, numTaskTypes);
	
//	Resize matrices
	
	taskNames.resize(numTaskTypes);
	taskPrty.resize(numTaskTypes);
	arrDists.resize(numTaskTypes);
	arrPms.resize(numTaskTypes);
	serDists.resize(numTaskTypes);
	serPms.resize(numTaskTypes);
	expDists.resize(numTaskTypes);
	expPmsLo.resize(numTaskTypes);
	expPmsHi.resize(numTaskTypes);
	affByTraff.resize(numTaskTypes);
	opNums.resize(numTaskTypes);
	
//	Read in task parameters
	
	for (int i = 0; i < numTaskTypes; i++)
	{
		readString(fin, taskNames[i]);						// name
		readArr(fin, taskPrty[i]);							// priority
		readVal(fin, arrDists[i]);							// arrival dist
		readArr(fin, arrPms[i], isInverted(arrDists[i]));	// arrival params
		readVal(fin, serDists[i]);							// service dist
		readArr(fin, serPms[i], isInverted(serDists[i]));	// service params
		readVal(fin, expDists[i]);							// expiration dist
		readArr(fin, expPmsLo[i], isInverted(expDists[i]));	// expiration params
		readArr(fin, expPmsHi[i], isInverted(expDists[i]));	// expiration params
		readArr(fin, affByTraff[i]);						// traffic
		readArr(fin, opNums[i]);							// operator nums
	}
	
//  Read in traffic
	
//    for (int i = 0; i < numHours; i++)
//    {
//        fin >> traffLevel;
//        
//        switch (traffLevel)
//        {
//            case 'l': traffic.push_back(0.5); break;
//            case 'm': traffic.push_back(1); break;
//            case 'h': traffic.push_back(2); break;
//            default: break;
//        }
//    }
	
    return;
}

/****************************************************************************
*																			*
*	Function:	readLine													*
*																			*
*	Purpose:	To read and save the line as a string from the specified 	*
*				file stream													*
*																			*
****************************************************************************/

void LoadParameters::readLine(fstream& fin, string& line)
{
//	Ignore commented lines
	
//	while (fin.peek() == '/')
//		getline(fin, line);

//	Ignore parameter name
	
	string paramName;
	fin >> paramName;
//	cout << "'" << paramName << "', ";
	
//	Read line as string
	
	ws(fin);
	getline(fin, line);
	
	return;
}

/****************************************************************************
*																			*
*	Function:	readString													*
*																			*
*	Purpose:	To read and save a string from the specified file stream	*
*																			*
****************************************************************************/

void LoadParameters::readString(fstream& fin, string& paramStrg)
{
//	Read line
	
	readLine(fin, paramStrg);
//	cout << paramStrg << endl;

	return;
}

/****************************************************************************
*																			*
*	Function:	readVal														*
*																			*
*	Purpose:	To read and save a value from the specified file stream		*
*																			*
****************************************************************************/

template <typename T>
void LoadParameters::readVal(fstream& fin, T& paramVal)
{
//	Read line
	
	string line;
	readLine(fin, line);
	istringstream iss(line);
	iss >> paramVal;
//	cout << paramVal << endl;
	
	return;
}

/****************************************************************************
*																			*
*	Function:	readArr														*
*																			*
*	Purpose:	To read and save an array from the specified file stream	*
*																			*
****************************************************************************/

template <typename T>
void LoadParameters::readArr(fstream& fin, vector<T>& paramArr, bool invert)
{
//	Read line
	
	string line;
	readLine(fin, line);
	istringstream iss(line);
	
//	Parse line for parameter values
	
	T val;
	while (iss >> val)
	{
		if (invert && val != 0)
			val = 1/val;
		paramArr.push_back(val);
	}
	
//	for (int i = 0; i < paramArr.size(); i++)
//		cout <<  paramArr[i] << " ";
//	cout << endl;
	
	return;
}

/****************************************************************************
*																			*
*	Function:	readTraff													*
*																			*
*	Purpose:	To read and save the traffic array from the specified file	*
*				stream														*
*																			*
****************************************************************************/

void LoadParameters::readTraff(fstream& fin, vector<float>& traff)
{
//	Read in character array
	
	vector<char> temp;
	readArr(fin, temp);
	
//	Replace characters with floats
	
	for (int i = 0; i < temp.size(); i++)
	{
		switch (temp[i])
		{
			case 'l': traff.push_back(0.5); break;
			case 'm': traff.push_back(1); break;
			case 'h': traff.push_back(2); break;
			default: break;
		}
	}
	
	return;
}


#endif