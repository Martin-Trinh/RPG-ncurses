#pragma once

// #include "Hero.h"
#include "Position.h"
#include <ncurses.h>
#include <string>
class Hero;

class Item{
protected:
    WINDOW * m_Win;

    std::string m_Name;
    char m_Character;
    Position m_Pos;
public:
    Item(WINDOW* win, const std::string& name, char character, int x, int y);
    void displayItem() const;
    virtual bool use(Hero & hero) = 0;
    virtual std::string toData() const;
};