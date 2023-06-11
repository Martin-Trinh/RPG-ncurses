#pragma once
/**
 * Project Graphic RPG Engine
 * @author trinhdin
 */
#include <string>
#include <sstream>



struct Position
{
    /// @brief x coordinate on map
    int m_X;
    /// @brief y coordinate on map
    int m_Y;
    /**
     * Construct a new Position object
     * 
     * @param x x coordinate on map
     * @param y y coordinate on map
     */
    Position(int x, int y);
    /**
     * Check if 2 positions are equal
     * 
     * @param rhs ->other position
     * @return true if 2 positions are equal
     * @return false if 2 positions are not equal
     */
    bool operator == (const Position & rhs) const;
};
