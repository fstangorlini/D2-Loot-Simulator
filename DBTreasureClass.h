// Database.h
#pragma once
#include <string>
#include <map>

#include "TreasureClass.h"

class DBTreasureClass {
public:
    DBTreasureClass(const DBTreasureClass&) = delete;

    static DBTreasureClass& getInstance();
    
    TreasureClass* getTreasureClass(std::string treasureClass);

private:
    std::map<std::string, TreasureClass> m_tcData;

    static DBTreasureClass s_Instance;
    DBTreasureClass();
    
    void split(const std::string& s, char delim, std::vector<std::string>& elems);
};
