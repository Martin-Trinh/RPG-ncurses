#pragma once

#include <string>
#include <sstream>

struct Position
{
    int m_X, m_Y;

    Position(int x, int y);
    bool operator == (const Position & rhs) const;
    std::string toData() const;
};
