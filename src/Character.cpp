#include "include/Character.h"

Character::Character(WINDOW * win,const std::string& name,char character, int x, int y, const Stats& stats)
: m_Win{win},m_Name{name}, m_Character{character}, m_Pos{x, y}, m_Stats{stats}{
    getmaxyx(m_Win, m_YMax, m_XMax);
}
bool Character:: moveUp(){
    mvwaddch(m_Win, m_Pos.m_Y, m_Pos.m_X, ' ');
    if(--m_Pos.m_Y > 0)
        return true;    
    ++m_Pos.m_Y;
    return false;
}
bool Character:: moveDown(){
    mvwaddch(m_Win, m_Pos.m_Y, m_Pos.m_X, ' ');
    if(++m_Pos.m_Y < m_YMax - 1)
        return true;
    --m_Pos.m_Y;
    return false;
}
bool Character:: moveRight(){
    mvwaddch(m_Win, m_Pos.m_Y, m_Pos.m_X, ' ');
    if(++m_Pos.m_X < m_XMax - 1)
        return true;
    --m_Pos.m_X;
    return false;
}
bool Character:: moveLeft(){
    mvwaddch(m_Win, m_Pos.m_Y, m_Pos.m_X, ' ');
    if(--m_Pos.m_X > 0)
        return true;
    ++m_Pos.m_X;
    return false;
}
int Character:: getMove(){
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
void Character::displayCharacter(){
    mvwaddch(m_Win, m_Pos.m_Y, m_Pos.m_X, m_Character);
}
vecStr Character::statsToVector() const{
        vecStr res;
        res.emplace_back("Name: " + m_Name);
        res.emplace_back("HP: " + std::to_string(m_Stats.m_HP));
        res.emplace_back("Mana: " + std::to_string(m_Stats.m_Mana));
        res.emplace_back("Strength: " + std::to_string(m_Stats.m_Strength));
        res.emplace_back("Magic: " + std::to_string(m_Stats.m_Magic));
        res.emplace_back("Armor: " + std::to_string(m_Stats.m_Armor));
        res.emplace_back("Resistance: "  + std::to_string(m_Stats.m_Resistance));
        return res;
    }