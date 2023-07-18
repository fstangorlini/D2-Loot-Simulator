#pragma once

#include <vector>
#include <string>


/*
* Stores a single "line" in TreasureClassEx.txt file
*/
class TreasureClass
{
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

    
    TreasureClass(const std::vector<std::string>& line_data);

    std::vector<std::string> get_loot(std::vector<std::string>& loot, const int kills);

private:
    int NOT_A_NUMBER;
    std::string NO_DROP;

    int str_to_int(const std::string& in_str);

    std::vector<std::string> select_random_elements(const std::vector<std::string>& samples, const std::vector<int>& weights);

    void no_drop();

    std::string replace_tc_with_t(std::string& tcStr);
};

