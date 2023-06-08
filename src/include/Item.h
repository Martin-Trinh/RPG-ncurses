#pragma once

#include "Position.h"
#include "Character.h"
// #include "Hero.h"
#include <ncurses.h>
#include <string>
class Hero;

class Item{
protected:
    std::string m_Name;
    char m_Character;
    Position m_Pos;
public:
    Item(const std::string& name, char character, int x, int y);
    virtual ~Item() = default;
    void removeItem(WINDOW * win) const;
    // getters 
    Position getPos()const;
    const std::string& getName()const;
    
    virtual bool use(Hero* hero, std::string& outMsg) = 0;
    virtual void displayItem(WINDOW * win) const;
    virtual std::string toData() const;
    bool operator == (const Item& other) const;
};