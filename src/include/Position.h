#pragma once

#include <string>
#include <sstream>

struct Position
{
    int m_X, m_Y;

    Position(int x, int y);
    bool operator == (const Position & rhs);
    std::string toData() const;
};
