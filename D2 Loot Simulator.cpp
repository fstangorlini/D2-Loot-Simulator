// D2 Loot Simulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <Windows.h>
#include <stdio.h>

#include "TreasureClass.h"
#include "DBTreasureClass.h"
#include "Random.h"

int getConsoleWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
    {
        // an error occourred
        return 80;
    }
    else
    {
        return csbi.srWindow.Right - csbi.srWindow.Left;
    }
}

void printLtoRMsg(const std::string& msg, const char& c)
{
    int cs = (getConsoleWidth() - msg.length()) / 2;
    std::cout << std::string(cs, c) << msg << std::string(cs, c);
    if (msg.length() % 2 == 0)
    {
        std::cout << c;
    }
    std::cout << std::endl;
}

void init()
{
    const std::string& msg = "START";
    const char& c = '-';
    printLtoRMsg(msg, c);
}

void end()
{
    const std::string& msg = "END";
    const char& c = '-';
    printLtoRMsg(msg, c);
}

int main()
{
    init();

    DBTreasureClass& dbInst = DBTreasureClass::getInstance();
    Random& rndInstance = Random::getInstance();

    const std::string monster = "Diablo (H)";
    const int kills = 10;

    auto* tc = dbInst.getTreasureClass(monster);
    const std::vector<std::string>& loot = tc->get_loot(kills);

    end();
    return 0;
}