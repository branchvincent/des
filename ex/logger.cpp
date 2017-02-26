
//  Logger
#define ELPP_NO_DEFAULT_LOG_FILE
#include "libs/easylogging++.h"
INITIALIZE_EASYLOGGINGPP

using namespace std;

void initLogger(int argc, char** argv)
{
    el::Configurations conf("libs/EasyLogging++.conf");
    el::Loggers::reconfigureAllLoggers(conf);
    el::Loggers::addFlag(el::LoggingFlag::HierarchicalLogging);
    // conf.setToDefault();
    START_EASYLOGGINGPP(argc, argv);
}

int main(int argc, char** argv)
{
    initLogger(argc, argv);
    // el::Loggers::setVerboseLevel(0);
    // el::Loggers::setLoggingLevel(el::Level::Info);
    LOG(TRACE) << "This is trace";
    LOG(DEBUG) << "This is debug";
    LOG(INFO) << "This is info";
    LOG(WARNING) << "This is warning";
    LOG(ERROR) << "This is error";
    // LOG_IF(false, FATAL) << "This is fatal";
    for (int i = 0; i <= 9; i++)
        VLOG(i) << "This is verbose " << i;

    return 0;
}
