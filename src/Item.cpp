#include "include/Item.h"

Item::Item(std::string name, char character, int x, int y)
: m_Name{name}, m_Character{character}, m_Pos{x, y}{}