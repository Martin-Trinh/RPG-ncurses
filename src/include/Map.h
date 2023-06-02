#pragma once

#include <sstream>
#include <string>
#include <ncurses.h>
#include <vector>
#include <fstream>

#include "Item.h"
#include "Monster.h"
#include "Hero.h"

class Map{
private:
    std::vector<std::string> m_Map;
    

    Hero * m_Hero;
    std::vector<Item*> m_Items;
    std::vector<Monster*> m_Monsters;

public:
    Map(std::string mapFile);
    int save(std::string file);
    void display(WINDOW* win);
    int removeMonster();
    int removeItem();
};