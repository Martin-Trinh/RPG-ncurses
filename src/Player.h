#pragma once

#include <ncurses.h>

class Player
{
private:
    WINDOW * m_Win;
    int m_X, m_Y;
    int m_XMax, m_YMax;
    char m_Hero;
public:
    Player(WINDOW * win, int x = 1, int y = 1, char hero = '@');
    bool moveUp();
    bool moveDown();
    bool moveRight();
    bool moveLeft();
    int getMove();
    void display ();
};

