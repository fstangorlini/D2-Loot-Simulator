// D2 Loot Simulator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <sstream>
#include <map>
#include <random>
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
    std::vector<std::string> loot;
    tc->get_loot(loot, kills);


    end();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
