#pragma once

#include "Position.h"

#include <ncurses.h>
#include <string>
#include <sstream>

class Gate{
private:
    int m_Id;
    Position m_Pos;
    bool m_IsOpen;
    char m_Character = '-';
public:
    Gate(int id, int x, int y, bool isOpen);
    // getters
    int getId() const;
    bool isOpen() const;
    Position getPos() const;
    void open();
    void displayGate(WINDOW* win);
    bool operator == (const Gate& other) const;
    std::string toData() const;
};