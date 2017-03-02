#include "pugixml.h"
#include <iostream>
#include <string.h>

using namespace std;

void readSim(pugi::xml_document& doc);
void readParams(pugi::xml_node& data);
void readTeam(pugi::xml_node& data);
void readAgent(pugi::xml_node& data);
void readTaskType(pugi::xml_node& data);
void readDist(pugi::xml_node& data);

int main()
{
    pugi::xml_document doc;
    if (!doc.load_file("params.xml")) cerr << "Failed to read." << endl;

    readSim(doc);
    // readParams(data);

    // for (pugi::xml_node child: tools.children("Tool"))
    // {
    //
    // }

    // pugi::xml_document doc;
    // if (!doc.load_file("my_xml_file.xml")) cerr << "Failed to read." << endl;
    // pugi::xml_node tools = doc.child("Profile").child("Tools");
    //
    // // tag::basic[]
    // for (pugi::xml_node tool = tools.first_child(); tool; tool = tool.next_sibling())
    // {
    //     std::cout << "Tool:";
    //
    //     for (pugi::xml_attribute attr = tool.first_attribute(); attr; attr = attr.next_attribute())
    //     {
    //         std::cout << " " << attr.name() << "=" << attr.value();
    //     }
    //
    //     std::cout << std::endl;
    // }
    // // end::basic[]
    //
    // std::cout << std::endl;
    //
    // // tag::data[]
    // for (pugi::xml_node tool = tools.child("Tool"); tool; tool = tool.next_sibling("Tool"))
    // {
    //     std::cout << "Tool " << tool.attribute("Filename").value();
    //     std::cout << ": AllowRemote " << tool.attribute("AllowRemote").as_bool();
    //     std::cout << ", Timeout " << tool.attribute("Timeout").as_int();
    //     std::cout << ", Description '" << tool.child_value("Description") << "'\n";
    // }
    // // end::data[]
    //
    // std::cout << std::endl;
    //
    // // tag::contents[]
    // std::cout << "Tool for *.dae generation: " << tools.find_child_by_attribute("Tool", "OutputFileMasks", "*.dae").attribute("Filename").value() << "\n";
    //
    // for (pugi::xml_node tool = tools.child("Tool"); tool; tool = tool.next_sibling("Tool"))
    // {
    //     std::cout << "Tool " << tool.attribute("Filename").value() << "\n";
    // }
    // // end::contents[]
}

void readSim(pugi::xml_document& doc)
{
    pugi::xml_node data = doc.child("parameters");
    readParams(data);

    for (pugi::xml_node& child : doc.child("teams"))
    {
        if ((string)child.name() == "team")
        {
            readTeam(child);
        }
        else
        {
            cout << "No team found for " << child.name() << endl;
        }
    }
}

void readParams(pugi::xml_node& data)
{
    string data_path = data.child_value("output_path");
    string reps = data.child_value("replications");
    cout << "Params" << endl;
    cout << "Out " << data_path << endl;
    cout << "Reps " << reps << endl << endl;
}

void readTeam(pugi::xml_node& data)
{
    string name = data.attribute("name").value();

    for (pugi::xml_node& child : data.child("agents"))
    {
        if ((string)child.name() == "agent")
        {
            readAgent(child);
        }
    }

    for (pugi::xml_node& child : data.child("tasks"))
    {
        if ((string)child.name() == "task")
        {
            readTaskType(child);
        }
    }

    cout << "Team" << endl;
    cout << "Name = " << name << endl;
}

void readAgent(pugi::xml_node& data)
{
    string name = data.attribute("name").value();
    string task_ids = data.attribute("task_ids").value();

    cout << "Agent" << endl;
    cout << "Name = " << name << endl;
    cout << "Task Ids = " << task_ids << endl;
}

void readTaskType(pugi::xml_node& data)
{
    string name = data.attribute("name").value();
    int id = data.attribute("id").as_int();
    string priority = data.child_value("priority");
    string traffic = data.child_value("traffic");

    cout << "Name = " << name;
    cout << "Id = " << id;
    cout << "P = " << priority;
    cout << "T = " << traffic;
}

void readDist(pugi::xml_node& data)
{
    string type = data.attribute("type").value();
}
