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
#include <string>
#include <algorithm>

using namespace std;

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
    
        string getOutFile() {return outFile;}
        vector<float> getTraffic() {return traffic;}
        vector<int> getOps() {return ops;}
        float getNumHours() {return numHours;}
        float getNumReps() {return numReps;}
	
	//	Other
	
		void readChar(fstream& fin, char& param);
		void readString(fstream& fin, string& param);
		void readInt(fstream& fin, int& param);
		void readFloat(fstream& fin, float& param);
		void readInt(fstream& fin, char& param);
		void readCharArr(fstream& fin, vector<char>& paramArr);
		void readIntArr(fstream& fin, vector<int>& paramArr);
		void readFloatArr(fstream& fin, vector<float>& paramArr);

//	Data members

	public:
	//	General settings
	
        string outFile;
        float numHours;
        vector<float> traffic;
        float numReps;
        vector<int> ops;
	
	//	Task settings
	
		int numTaskTypes;
        vector<string> taskNames;
        Matrix2D taskPrty;
        vector<char> arrDists;
        Matrix2D arrPms;
        vector<char> serDists;
        Matrix2D serPms;
        vector<char> expDists;
        Matrix2D expPmsLo;
        Matrix2D expPmsHi;
		Matrix2D affByTraff;
		Matrix2D opNums;
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
    
//  Initialize variables
    
    string paramName;
    
//	Read in output file
    
    fin >> paramName;
    fin.ignore();
    fin.ignore();
    getline(fin, outFile);
    
//  Read in number of hours
    
    fin >> paramName >> numHours;
    
//  Read in traffic
    
    char traffLevel;
    fin >> paramName;
    
    for (int i = 0; i < numHours; i++)
    {
        fin >> traffLevel;
        
        switch (traffLevel)
        {
            case 'l': traffic.push_back(0.5); break;
            case 'm': traffic.push_back(1); break;
            case 'h': traffic.push_back(2); break;
            default: break;
        }
    }
    
//	Read in number of replications
    
    fin >> paramName >> numReps;
    
//  Read in operators
    
    int opNum;
    fin >> paramName;
    
    while (fin >> opNum)
        ops.push_back(opNum);
    
//  Read in task parameters

	fin >> paramName >> numTaskTypes;
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
	
//	for (int i = 0; i < numTaskTypes; i++)
//	{
		readString(fin, taskNames[0]);		// name
//		readFloatArr(fin, taskPrty[i]);		// priority
//		readChar(fin, arrDists[i]);			// arrival dist
//		readFloatArr(fin, arrPms[i]);		// arrival params
//		readChar(fin, serDists[i]);			// service dist
//		readFloatArr(fin, serPms[i]);		// service params
//		readChar(fin, expDists[i]);			// expiration dist
//		readFloatArr(fin, expPmsLo[i]);		// expiration params
//		readFloatArr(fin, expPmsHi[i]);		// expiration params
//		readFloatArr(fin, affByTraff[i]);	// traffic
//		readFloatArr(fin, opNums[i]);		// operator nums
//	}
	
    return;
}

void readChar(fstream& fin, char& param)
{
	string paramName;
	fin >> paramName >> param;
	return;
}

void readCharArr(fstream& fin, vector<char>& paramArr)
{
	string paramName;
	fin >> paramName;
	
	char temp;
	while (fin >> temp)
		paramArr.push_back(temp);
	
	return;
}

void readString(fstream& fin, string& param)
{
	string paramName;
	fin >> paramName >> param;
	return;
}

void readInt(fstream& fin, int& param)
{
	string paramName;
	fin >> paramName >> param;
	return;
}

void readIntArr(fstream& fin, vector<int>& paramArr)
{
	string paramName;
	fin >> paramName;
	
	float temp;
	while (fin >> temp)
		paramArr.push_back(temp);
	
	return;
}

void readFloat(fstream& fin, float& param)
{
	string paramName;
	fin >> paramName >> param;
	return;
}

void readFloatArr(fstream& fin, vector<float>& paramArr)
{
	string paramName;
	fin >> paramName;
	
	float temp;
	while (fin >> temp)
		paramArr.push_back(temp);
	
	return;
}

#endif