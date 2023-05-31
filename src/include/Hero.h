#pragma once

#include <ncurses.h>
#include "Position.h"

class Hero
{
private:
    WINDOW * m_Win;
    int m_XMax, m_YMax;
     
    int m_X, m_Y;
    char m_Hero;
public:
    Hero(WINDOW * win, int x = 1, int y = 1, char hero = '@');
    bool moveUp();
    bool moveDown();
    bool moveRight();
    bool moveLeft();
    int getMove();
    void display ();
};

