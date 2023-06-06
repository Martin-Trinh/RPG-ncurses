#pragma once 

#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>

#include "Hero.h"
#include "Stats.h"
#include "Map.h"
#include "Potion.h"
#include "Monster.h"

class Game{
private:
    WINDOW * m_Win;
    Map * m_Map = NULL;
public:
    Game();
    ~Game();
    void run();
    void displayMenu();
    void createHero();
    bool loadGame(const std::string& file);
    void displayGame();
    void displayControl(WINDOW* win) const;
    bool saveGame();
    bool warning();

};