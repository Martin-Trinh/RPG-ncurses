#pragma once

#include <ncurses.h>
#include "Position.h"
#include "Stats.h"
#include <string>
#include <vector>

typedef std::vector<std::string> vecStr;    

class Character
{
protected:
    std::string m_Name;
    Position m_Pos;
    Stats m_Stats;
    
    int m_CurrHP;
    int m_CurrMana;
public:
    Character(const std::string& name, int x, int y, const Stats &stats);


    void statsBuff(const Stats& stat);
    void increaseHP(int amount);
    void increaseMana(int amount);

    void attack(Character * other, int damage, bool magical);
    char move(WINDOW* win, int x, int y);

    //getters 
    Position getPos() const;
    int getCurrHP() const;
    int getCurrMana() const;
    const std::string& getName()const;
    std::string toData() const;
};
