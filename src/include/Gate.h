#pragma once

#include "Position.h"
#include "Entity.h"
#include <ncurses.h>
#include <string>
#include <sstream>

class Gate: public Entity{
private:
    bool m_IsOpen;
public:
    Gate(char character, int x, int y, bool isOpen);
    // getters
    bool isOpen() const;
    void open();
    bool operator == (const Gate& other) const;
    std::string toData() const;
};