#include "include/Hero.h"

Hero::Hero(WINDOW * win, int x, int y, char hero)
: m_Win{win}, m_X{x}, m_Y{y}, m_Hero{hero}{
    getmaxyx(m_Win, m_YMax, m_XMax);
}
bool Hero:: moveUp(){
    mvwaddch(m_Win, m_Y, m_X, ' ');
    if(--m_Y > 0)
        return true;    
    ++m_Y;
    return false;
}
bool Hero:: moveDown(){
    mvwaddch(m_Win, m_Y, m_X, ' ');
    if(++m_Y < m_YMax - 1)
        return true;
    --m_Y;
    return false;
}
bool Hero:: moveRight(){
    mvwaddch(m_Win, m_Y, m_X, ' ');
    if(++m_X < m_XMax - 1)
        return true;
    --m_X;
    return false;
}
bool Hero:: moveLeft(){
    mvwaddch(m_Win, m_Y, m_X, ' ');
    if(--m_X > 0)
        return true;
    ++m_X;
    return false;
}
int Hero:: getMove(){
    int move = wgetch(m_Win);
    switch (move)
    {
    case KEY_UP:
        this->moveUp();
        break;
    case KEY_DOWN:
        this->moveDown();
        break;
    case KEY_RIGHT:
        this->moveRight();
        break;
    case KEY_LEFT:
        this->moveLeft();
        break;
    default:
        break;
    }
    return move;
}
void Hero::display(){
    mvwaddch(m_Win, m_Y, m_X, m_Hero);
}