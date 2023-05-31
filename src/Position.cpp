#include "include/Position.h"

Position::Position(int x, int y)
: m_X{x}, m_Y{y}{}
bool Position::operator == (const Position & rhs){
    return m_X == rhs.m_X && m_Y == rhs.m_Y;
}