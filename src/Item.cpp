#include "include/Item.h"

Item::Item(const std::string& name, char character, int x, int y)
:Entity{name, character, x, y}{}
bool Item::operator == (const Item& other) const{
    return m_Pos == other.m_Pos;
}

