#pragma once

class Position
{
private:
    int m_X, m_Y;
public:
    Position(int x, int y);
    bool operator == (const Position & rhs);
};
