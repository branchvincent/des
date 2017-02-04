#include <iostream>
#include <string>
// #include <boost/property_tree/ptree.hpp>
// #include <boost/property_tree/xml_parser.hpp>
#include <vector>
#include "Util.h"
#include "TaskType.h"
#include "Distribution.h"
#include <random>
#include <typeinfo>
#include "Parameters.h"
#include <queue>

using namespace std;

// struct Flight
// {
//     std::string  carrier;
//     unsigned     number;
//     // Date         date;
//     bool         cancelled;
// };
// typedef std::vector<Flight> Sked;

typedef priority_queue<Task,vector<Task>> Queue;

int main()
{
    // ptree pt;
    // read_xml("params.xml", pt);

    // Parameters p("params.xml");

    // TaskType t(pt.get_child("task"));
    //
    // for (int i = 0; i < 4; i++)
    //     cout << t.genTask(0) << endl;

    // Task t1("t1", 8, 0, 4, 100);
    // Task t2("t2", 10, 0, 4, 100);
    //
    // if (t1 < t2)
    //     cout << t1 << " is of lesser priority than " << t2 << endl;
    // else
    //     cout << t1 << " is of higher priority than " << t2 << endl;
    //
    // Queue q;
    // q.push(t1);
    // q.push(t2);
    // cout << q.top() << endl;

    // for (auto& a : pt)
    // {
    //     cout << '[' << a.first << "]\n";
    //     for (auto& b : a.second)
    //     {
    //         cout << b.first << "=" << b.second.data() << "\n";
    //     }
    // }

    // Sked ans;
    // for (ptree::value_type v : pt.get_child("sked"))
    // {
    //     if(v.first == "flight")
    //     {
    //         Flight f;
    //         f.carrier = v.second.get<string>("carrier");
    //         f.number = v.second.get<unsigned>("number");
    //         // f.date = v.second.get<Date>("date");
    //         f.cancelled = v.second.get("<xmlattr>.cancelled", false);
    //         ans.push_back(f);
    //     }
    // }

    return 0;
}
