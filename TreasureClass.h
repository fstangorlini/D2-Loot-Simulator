#pragma once

#include <vector>
#include <string>


/* Stores a single "line" in TreasureClassEx.txt file
* as a TreasureClass object */
class TreasureClass
{
    /* Public Class variables */
public:

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

public:
    /* Constructor declaration */
    TreasureClass(const std::vector<std::string>& line_data);

    /* Returns array with loot regarding this specific TreasureClass */
    std::vector<std::string> get_loot(const int kills);

    /* Private Class variables */
private:
    int NOT_A_NUMBER;
    std::string NO_DROP;

    /* Private Methods */
private:

    /* Custom string to int converter makes easier to handle data conversion */
    int str_to_int(const std::string& in_str);

    /* Selects random elements considering weights */
    std::vector<std::string> select_random_elements(const std::vector<std::string>& samples, const std::vector<int>& weights);

    /* Adds No Drop to the loot array */
    void no_drop();

    /* Replaces Treasure Class with final treasure */
    std::string replace_tc_with_t(std::string& tcStr);
};

