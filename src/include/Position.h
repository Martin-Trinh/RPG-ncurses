#pragma once

struct Position
{
    int m_X, m_Y;
    Position(int x, int y);
    bool operator == (const Position & rhs);
};
