#include <iostream>
#include <string>
 // #include "Task.cpp"
// #include "Distribution.h"
// #include "Task.h"
#include "TaskType.h"
// #include "test/Task.h"
// #include "test/Utility.h"
// #include "test/Distribution.h"
// #include "Parameters.h"
// #include "Flags.h"
// #include "Simulation.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
using boost::property_tree::ptree;

using namespace std;

class A
{   public:
    A(int x = 1) : x(x) {}
    int& getX() {return x;}
    int x;
};

// float util::seed = rand();
// default_random_engine util::randNumGen = default_random_engine(util::seed);
// vector<float> util::TRAFFIC = {1,1,1};

int main()
{
    ptree data;
    read_xml("/Users/Branch/Documents/Research/fra/shado/params.xml", data);

   // Distribution t;
   // Task t(2, 1, 3, 40);
   TaskType t(data.get_child("task"));
   // Team t(pt.get_child("teadm"));
   // Parameters t("params.xml");

    // if (static_cast<bool>(s))
    //     cout << "TRUE" << endl;
   // Simulation t("params.xml");
   cout << t << endl;

    return 0;
}
