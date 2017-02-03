#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <vector>
#include "Util.h"
#include "TaskType.h"
// #include "Parameters.h"

using namespace std;
using boost::property_tree::ptree;

// typedef boost::gregorian::date Date;

class MyClass
{
public:
    MyClass() : x(0) {}
    MyClass(int x) : x(x) {}
    int x;
};

struct Flight
{
    std::string  carrier;
    unsigned     number;
    // Date         date;
    bool         cancelled;
};

typedef std::vector<Flight> Sked;

int main()
{
    ptree pt;
    read_xml("params.xml", pt);

    for (auto& a : pt)
    {
        cout << '[' << a.first << "]\n";
        for (auto& b : a.second)
        {
            cout << b.first << "=" << b.second.data() << "\n";
        }
    }

    // traverse pt

    vector<Task> tasks;
    // for (ptree:value_type v: pt.get_child("task_types"))
    for (auto& v: pt.get_child("task_types"))
    {
        if (v.first == "task")
        {
            string name = v.second.get<string>("name");
            vector<int> priority = {1,1,1};
            string description = v.second.get<string>("description");
            cout << description << endl;
            // tasks.push_back(TaskType());
            MyClass c = v.second.get<MyClass>("x");
            cout << c.x << endl;
        }
    }


    Sked ans;
    for (ptree::value_type v : pt.get_child("sked"))
    {
        if(v.first == "flight")
        {
            Flight f;
            f.carrier = v.second.get<string>("carrier");
            f.number = v.second.get<unsigned>("number");
            // f.date = v.second.get<Date>("date");
            f.cancelled = v.second.get("<xmlattr>.cancelled", false);
            ans.push_back(f);
        }
    }

    cout << ans[0].carrier << endl;
    cout << ans[0].number << endl;
    cout << ans[1].cancelled << endl;

    return 0;
}

// class XMLParser
// {
// //	Public member functions
//
// 	public:
//
//     //  Constructor
//
// 		XMLParser(string file) {read_xml(file, data);}
//
// 	//	Inspectors
//
//
// 		ptree getData() const {return data;}
//
//
//     //  Mutators
//
//     //  Other member functions
//
// //	Data members
//
// 	private:
// 		ptree data;
// };

// int main()
// {
//     // XMLParser parser("params.xml");
//     // ptree params = parser.getData();
//     ptree params;
//     // // read_ini("params.ini", params);
//     // // read_json("params.json", params);
//     read_xml("params.xml", params);
//
//     for (auto& a : params)
//     {
//         cout << '[' << a.first << "]\n";
//         for (auto& b : a.second)
//         {
//             cout << b.first << "=" << b.second.data() << "\n";
//         }
//     }
//
//     for (auto& a : params.get_child("level1.level2"))
//     {
//         cout << '[' << a.first << a.size << "]\n";
//         for (auto& b : a.second)
//         {
//             cout << b.first << "=" << b.second.data() << "\n";
//         }
//     }
//
//     // vector<string> test;
//     // for (auto& section : params)
//     // {
//     //     cout << '[' << section.first << "]\n";
//     //     for (auto& key : section.second)
//     //     {
//     //         cout << key.first << "=" << key.second.data() << "\n";
//     //     }
//     // }
//
//     // cout << test << endl;
//
//     // try
//     // {
//         // ptree p = params.get<ptree>("parameters.teams");
//         // cout << params.get<string>("parameters.traffic") << endl;
//     // }
//     // catch (string exception)
//     // {
//     //     cout << exception << endl;
//     // }
// }
