#pragma once

#include <ncurses.h>
#include "Position.h"
#include "Stats.h"
#include <string>
#include <vector>

typedef std::vector<std::string> vecStr;

class Character
{
private:
    WINDOW * m_Win;
    int m_XMax, m_YMax;

    std::string m_Name;
    char m_Character;
    Position m_Pos;
    Stats m_Stats;
public:
    Character(WINDOW * win, const std::string& name, char character, int x, int y, const Stats &stats);
    bool moveUp();
    bool moveDown();
    bool moveRight();
    bool moveLeft();
    int getMove();
    void displayCharacter ();
   vecStr statsToVector() const;
};
