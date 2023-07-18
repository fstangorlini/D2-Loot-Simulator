#pragma once

#include <iostream>

#include "TreasureClass.h"
#include "DBTreasureClass.h"
#include "Random.h"

std::string m_treasureClass;
int m_group;
int m_level;
int m_picks;
int m_unique;
int m_set;
int m_rare;
int m_magic;
int m_noDrop;
std::vector<std::string> m_items;
std::vector<int> m_probabilities;
int m_sumItems;
int m_totalProb;
int m_dropChance;

int NOT_A_NUMBER;
std::string NO_DROP;

Random& rndInstance = Random::getInstance();

TreasureClass::TreasureClass(const std::vector<std::string>& line_data)
{
    NOT_A_NUMBER = -1;
    NO_DROP = "No Drop";

    m_treasureClass = line_data[0];
    m_group = str_to_int(line_data[1]);
    m_level = str_to_int(line_data[2]);
    m_picks = str_to_int(line_data[3]);
    m_unique = str_to_int(line_data[4]);
    m_set = str_to_int(line_data[5]);
    m_rare = str_to_int(line_data[6]);
    m_magic = str_to_int(line_data[7]);
    m_noDrop = str_to_int(line_data[8]);

    const int c_offset = 8;

    for (int i = 1; i < 11; i++)
    {
        int idxI = ((i - 1) * 2) + 1 + c_offset;
        auto& itemV = line_data[idxI];
        auto& probV = line_data[idxI + 1];
        if (!itemV.empty())
            m_items.push_back(itemV);
        if (!probV.empty())
            m_probabilities.push_back(str_to_int(probV));

    }

    m_sumItems = str_to_int(line_data[29]);
    m_totalProb = str_to_int(line_data[30]);
    m_dropChance = str_to_int(line_data[31]);
}

int TreasureClass::str_to_int(const std::string& in_str)
{
    if (!in_str.empty())
    {
        return std::stoi(in_str);
    }
    else
    {
        return NOT_A_NUMBER;
    }
}

std::vector<std::string> TreasureClass::select_random_elements(const std::vector<std::string>& samples, const std::vector<int>& weights)
{
    std::vector<std::string> elements;
    int sumOfWeight = 0;
    for (int w : weights)
        sumOfWeight += w;

    int picks = m_picks;
    if (picks < 0)
        picks = std::abs(m_picks);

    for (int i = 0; i < picks; i++)
    {
        int rnd = rndInstance.getInstance().getRandomNumber(sumOfWeight);
        for (size_t i = 0; i < samples.size(); i++)
        {
            if (rnd < weights[i])
            {
                if (samples[i] != NO_DROP)
                    elements.push_back(samples[i]);
                break;
            }
            rnd -= weights[i];
        }
    }
    return elements;
}

std::vector<std::string> TreasureClass::get_loot(const int kills)
{
    std::vector<std::string> loot;

    for (int i = 0; i < kills; i++)
    {
        //adds no drop
        no_drop();

        //get random weighted loot classes
        std::vector<std::string> single_loot = select_random_elements(m_items, m_probabilities);
        for (auto& l : single_loot)
            loot.push_back(l);
    }

    //replace loot classes with final loot
    for (auto& l : loot)
    {
        l = replace_tc_with_t(l);
    }


    std::cout << m_treasureClass << " loot: [";
    for (int i = 0; i < loot.size(); i++)
    {
        std::cout << loot[i];
        if (i != loot.size() - 1)
            std::cout << ", ";
    }
    std::cout << "]" << std::endl;
    return loot;
}

void TreasureClass::no_drop()
{
    //TODO implement players 1-8 to lower no drop
    //for now, it is considered players 1
    if (m_picks > 0)
    {
        if (m_noDrop > 0)
        {
            m_items.push_back(NO_DROP);
            m_probabilities.push_back(m_noDrop);
        }
    }
}

std::string TreasureClass::replace_tc_with_t(std::string& tcStr)
{
    //std::cout << "Starting replace_tc_with_t(" << tcStr << ")" << std::endl;
    TreasureClass* tc = DBTreasureClass::getInstance().getTreasureClass(tcStr);
    if (tc == NULL)
    {
        // found last level = treasure
        //std::cout << "reached lowest level at=[" << tcStr << "]" << std::endl;
        return tcStr;
    }
    else
    {
        // did not find last level yet, need to go deeper into this treasure class
        //std::cout << "going deeper..." << std::endl;
        auto nextTreasureClass = tc->select_random_elements(tc->m_items, tc->m_probabilities);
        if (nextTreasureClass.size() != 1)
        {
            std::cout << "ERROR! NOT SURE WHAT TO DO HERE, PLEASE CHECK!" << std::endl;
        }
        auto& ntcStr = nextTreasureClass[0];

        return replace_tc_with_t(ntcStr);
    }
    //std::cout << tc->m_treasureClass << std::endl;
    //TreasureClass& tc = DBTreasureClass::getInstance().getTreasureClass(tcStr);

}