#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <map>

#include "DBTreasureClass.h"

DBTreasureClass DBTreasureClass::s_Instance;
std::map<std::string, TreasureClass> m_tcData;

DBTreasureClass::DBTreasureClass()
{
    std::ifstream infile("./res/TreasureClassEx.txt");
    std::string line;
    std::getline(infile, line); //skip first line
    const int c_offset = 8;
    while (std::getline(infile, line))
    {
        std::vector<std::string> items;
        split(line, '\t', items);
        TreasureClass tc = TreasureClass(items);
        m_tcData.insert(std::pair<std::string, TreasureClass>(tc.m_treasureClass, tc));
    }
}

DBTreasureClass& DBTreasureClass::getInstance()
{
    return s_Instance;
}

void DBTreasureClass::split(const std::string& s, char delim, std::vector<std::string>& elems)
{
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
}

TreasureClass* DBTreasureClass::getTreasureClass(const std::string treasureClass)
{
    auto aa = s_Instance.m_tcData.find(treasureClass);
    if (aa == s_Instance.m_tcData.end())
    {
        return NULL; //Why doesn't it work?
    }
    else
    {
        TreasureClass *p = &s_Instance.m_tcData.at(treasureClass);
        //TreasureClass* tcPtr = tc;

        //return s_Instance.m_tcData.at(treasureClass);
        return p;
    }
}