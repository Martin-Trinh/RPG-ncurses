#pragma once

#include <ncurses.h>
#include <vector>
#include <string>

class Menu
{
public:
    Menu(){
        getmaxyx(stdscr, yMax, xMax);
        WINDOW * m_Window = newwin(yMax/2, xMax/2, yMax/8, xMax/8);
        box(m_Window, 0, 0);
    }
    bool addOption(std::string option);
    void display();
    int getSelected();
    void next();
    void prev();
private:
    WINDOW * m_Window;
    int yMax, xMax;
    std::vector <std::string> m_Options;
    int m_Selected = 0;

};