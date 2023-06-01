#pragma once

// #include "Hero.h"
#include "Position.h"
#include <string>
class Hero;

class Item{
private:
    std::string m_Name;
    char m_Character;
    Position m_Pos;
public:
    Item(std::string name, char character, int x, int y);
    virtual bool use(Hero & hero) = 0;
};