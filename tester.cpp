#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "Task.h"
//#include "TaskType.h"
// #include "src/Agent.h"
// #include "Utility.h"

using namespace std;
using boost::property_tree::ptree;

// class A
// {
// public:
//     friend class B;
//     friend class C;
//     A(int a = 1) : a(a) {}
// private: int a;
// };
//
// class B
// {
// public:
//     friend class C;
//     B(int b = 2) : a(b) {}
//     void print() {cout << a.a << endl;}
// private:
//     A a;
// };
//
// class C
// {
// public:
//     C(int c = 3) : b() {}
//     void print() {cout << b.a.a << endl;}
// private:
//     B b;
// };

int main()
{
    ptree data;
    read_xml("/Users/Branch/Documents/Research/fra/shado/params.xml", data);

    // cout << util::seed << endl;
    Task t(2, 1, 3, 40);
//     TaskType t(data.get_child("task"));
    // Team t(pt.get_child("team"));
    // Parameters t("params.xml");
   cout << t << endl;

    return 0;
}

// struct Flight
// {
//     std::string  carrier;
//     unsigned     number;
//     // Date         date;
//     bool         cancelled;
// };
// typedef std::vector<Flight> Sked;

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
