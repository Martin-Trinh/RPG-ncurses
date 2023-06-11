#pragma once

#include "Position.h"
#include <ncurses.h>
#include <string>
#include <vector>

typedef std::vector<std::string> vecStr;
class Entity{
protected:
    std::string m_Name;
    char m_Character;
    Position m_Pos;
public:
    Entity(const std::string& name, char character, int x, int y);
    Position getPos()const;
    const std::string& getName()const;
    char getCharacter()const;
    void setPosition(int x, int y);
    void displayEntity(WINDOW* win, int margin)const;
};