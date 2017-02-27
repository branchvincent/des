#include "../lib/easylogging.h"
#include "myclass.h"
// INITIALIZE_EASYLOGGINGPP

MyClass::MyClass() : x(1)
{
    LOG(INFO) << "HERE";
}
