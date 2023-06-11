#pragma once
/**
 * Project Graphic RPG Engine
 * @author trinhdin
 */
#include "Position.h"
#include "Entity.h"
#include <ncurses.h>
#include <string>
#include <sstream>

/**
 * @brief class representing gate as blocking entity on the map, that can be opened
 * 
 */
class Gate: public Entity{
private:
    /// @brief gate state if it is open or not
    bool m_IsOpen;
public:
    /// @brief Construct a new Gate object
    Gate(char character, int x, int y, bool isOpen);
    // getters
    bool isOpen() const;
    /// @brief change character to '+' and state to open
    void open();
    /// @brief compare two gates by their position
    bool operator == (const Gate& other) const;
};