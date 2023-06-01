#include "include/Item.h"

Item::Item(WINDOW* win, const std::string& name, char character, int x, int y)
:m_Win{win}, m_Name{name}, m_Character{character}, m_Pos{x, y}{
}
void Item::displayItem() const{
    mvwaddch(m_Win, m_Pos.m_Y, m_Pos.m_X, m_Character);
}