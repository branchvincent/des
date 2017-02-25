/****************************************************************************
*																			*
*	File:		run.cpp													    *
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file executes the discrete event simulation for the    *
*               specified parameters.                                       *
*																			*
****************************************************************************/

#include <iostream>
#include <string>

using namespace std;

int* get() {return int(5);}

/****************************************************************************
*																			*
*	Function:	main														*
*																			*
****************************************************************************/

int main(int argc, const char* argv[])
{
    int* x = get();
    cout << x;
	return 0;
}
