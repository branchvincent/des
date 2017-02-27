#include <iostream>
#include <string>
#include "../src/Team.h"
#include "../src/events/ArrivalEvent.h"

#define ELPP_NO_DEFAULT_LOG_FILE
#include "../lib/EasyLogging.h"
INITIALIZE_EASYLOGGINGPP

float util::seed = rand();
default_random_engine util::randNumGen = default_random_engine(util::seed);
vector<float> util::TRAFFIC = {1,1,1};

/****************************************************************************
*																			*
*	Function:	main														*
*																			*
****************************************************************************/

int main()
{
    Team t;
	return 0;
}
