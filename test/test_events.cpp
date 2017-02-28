#include <iostream>
#include <string>
#include "Event.h"
#include "../src/events/DepartureEvent.h"
#include "../src/events/ArrivalEvent.h"
#include <vector>
#define ELPP_NO_DEFAULT_LOG_FILE
#include "../deps/EasyLogging.h"
INITIALIZE_EASYLOGGINGPP

/****************************************************************************
*																			*
*	Function:	main														*
*																			*
****************************************************************************/

int main()
{
    DateTime t;

    vector<Event*> events = {new ArrivalEvent(t,NULL);}

    for (Event* e : events)
    {
        e->process();
    }


	return 0;
}
