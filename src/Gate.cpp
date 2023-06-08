#include "include/Gate.h"

Gate::Gate(int id, int x, int y, bool isOpen)
:m_Id{id}, m_Pos{x, y}, m_IsOpen{isOpen}{
    if(m_IsOpen)
        m_Character = '+';
}

int Gate::getId() const{return m_Id;}
bool Gate::isOpen() const{return m_IsOpen;}
Position Gate::getPos() const{return m_Pos;}
void Gate::open(){
    m_IsOpen = true;
    m_Character = '+';
}
void Gate::displayGate(WINDOW* win){
    mvwaddch(win, m_Pos.m_Y, m_Pos.m_X, m_Character);
}
bool Gate::operator == (const Gate& other) const{
    return m_Pos == other.m_Pos;
}
std::string Gate::toData() const{
    std::stringstream res;
    res << m_Id << "," << m_Pos.toData() << "," << m_IsOpen;
    return res.str();
}