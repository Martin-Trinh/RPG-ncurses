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
    WINDOW * m_Win;
    int m_XMax, m_YMax;

    std::string m_Name;
    char m_Character;
    Position m_Pos;
    Stats m_Stats;
    
    int m_CurrHP;
    int m_CurrMana;
public:
    Character(WINDOW * win, const std::string& name, char character, int x, int y, const Stats &stats);
    bool moveUp();
    bool moveDown();
    bool moveRight();
    bool moveLeft();
    int getMove();
    void displayCharacter () const;
   vecStr statsToVector() const;
};
