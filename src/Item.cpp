#include "include/Item.h"

Item::Item(const std::string& name, char character, int x, int y)
:m_Name{name}, m_Character{character}, m_Pos{x, y}{
}

Position Item::getPos()const{return m_Pos;}
const std::string& Item::getName()const{return m_Name;}

void Item::displayItem(WINDOW* win)const {
    mvwaddch(win, m_Pos.m_Y, m_Pos.m_X, m_Character);
}
std::string Item::toData() const{
    std::stringstream res;
    res << m_Name << ',' << m_Pos.toData();
    return res.str();
}    