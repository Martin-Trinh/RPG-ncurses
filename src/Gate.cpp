#include "include/Gate.h"

Gate::Gate(char character, int x, int y, bool isOpen)
: Entity{"Gate", character, x, y}, m_IsOpen{isOpen}{
    if(m_IsOpen)
        m_Character = '+';
    else
        m_Character = '-';
}
bool Gate::isOpen() const{return m_IsOpen;}
void Gate::open(){
    m_IsOpen = true;
    m_Character = '+';
}

bool Gate::operator == (const Gate& other) const{
    return m_Pos == other.m_Pos;
}