#pragma once

#include <sstream>
#include <string>
#include <ncurses.h>
#include <vector>
#include <set>
#include <fstream>

#include "Item.h"
#include "Potion.h"
#include "Equipment.h"
#include "Key.h"
#include "Monster.h"
#include "Hero.h"
#include "ncurses.h"
#include "LogMsg.h"
#include "Gate.h"

class Map{
private:
    std::vector<std::string> m_Map;
    static const int m_Margin = 2;

    Hero * m_Hero;
    std::vector<Item*> m_Items;
    std::vector<Monster*> m_Monsters;
    std::vector<Gate*> m_Gates;

    const std::set<char> m_CharItems {'^', 'p', 'b', 'w', 'o', 'h', 'm', 'e', '?'};
    const std::set<char> m_CharMonster {'S', 'X'};

public:
    Map(const std::string& mapFile);
    int save(const std::string& file);

    void loadEntity(const std::string &name,const Stats& stats);
    void addMonster(char tile, int x, int y);
    void addItem(char tile, int x, int y);
    size_t findItem(Position pos)const;
    size_t findMonster(Position pos)const;
    int getKey(WINDOW* win, WINDOW* control);
    // getters
    Hero* getHero() const;
    void display(WINDOW* win);
};