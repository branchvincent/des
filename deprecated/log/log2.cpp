#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

#include <string>
#include <cstring>
using namespace std;

void log_init(const string &log_file)
{
  logging::add_file_log
  (
    keywords::file_name = log_file,
    keywords::format = "%TimeStamp% %Message%"
  );
  logging::add_common_attributes();
}

#define MY_LOG(lg) BOOST_LOG(lg) \
  << (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__) \
  << " " << __LINE__ \
  << " " << __FUNCTION__ << ": "

int main(int argc, char *argv[])
{
  src::logger lg;
  string log_file = argv[0];
  log_init(log_file.substr(0, log_file.rfind('.')) + ".log");

  MY_LOG(lg) << "blahblah";
  MY_LOG(lg) << "blahblah";

  return 0;
}
