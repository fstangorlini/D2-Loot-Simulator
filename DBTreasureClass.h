#pragma once
#include <string>
#include <map>

#include "TreasureClass.h"

/* Stores a data structure of map {k,v}
* k = "Treasure Class" as string
* v = TreasureClass object
*/
class DBTreasureClass
{
    /* Public Class variables */
public:
    static DBTreasureClass& getInstance();

    /* Public methods */
public:
    /* Singleton - marks copy constructor as delete */
    DBTreasureClass(const DBTreasureClass&) = delete;

    /* Gets a pointer to the TreasureClass, from the "table" */
    TreasureClass* getTreasureClass(std::string treasureClass);

    /* Private Class variables */
private:
    /* Map */
    std::map<std::string, TreasureClass> m_tcData;
    /* Singleton instance */
    static DBTreasureClass s_Instance;

    /* Private methods */
private:
    /* Private constructor - singleton */
    DBTreasureClass();

    /* Split aux method to split elements on the txt file into array */
    void split(const std::string& s, char delim, std::vector<std::string>& elems);
};
