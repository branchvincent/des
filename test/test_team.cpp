#include <iostream>
#include <string>
#include <vector>
#include "../include/shift.h"
// #include "../src/Team.h"
// #include "../src/events/ArrivalEvent.h"

// #define ELPP_NO_DEFAULT_LOG_FILE
// #include "easylogging++.h"
// INITIALIZE_EASYLOGGINGPP
//
// float util::seed = rand();
// default_random_engine util::randNumGen = default_random_engine(util::seed);
// vector<float> util::TRAFFIC = {1,1,1};

using namespace std;

inline string toLower(string s)
    {transform(s.begin(), s.end(), s.begin(), ::tolower); return s;}

class Test
{
    public:
        Test() : _x() {}
        int* x() const {return _x;}
    private:
        int* _x;
};

/****************************************************************************
*																			*
*	Function:	main														*
*																			*
****************************************************************************/

int main()
{
    Shift s;
    cout << s;

    Shift s2;
    cout << s2;

    

	return 0;
}
