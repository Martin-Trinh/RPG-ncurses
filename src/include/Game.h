#pragma once 


#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>

#include "GameConfig.h"
#include "Map.h"
#include "Hero.h"
#include "Potion.h"
#include "LogMsg.h"
#include "Item.h"
#include "AttackSkill.h"
#include "RegenSkill.h"


class Game{
private:
    Map * m_Map = nullptr;
    GameConfig * m_GameConfig = nullptr;
    bool m_Exit = false;
    std::string m_DefaultMap = "map1";
    std::string m_ConfigFile = "config1";
public:
    Game();
    ~Game();
    void displayMenu();
    void displayGame();
    void createHero();
    void displayControl(WINDOW* win) const;
    void getInput(const vecStr& Description, std::string& input);
    void saveGame();
    void loadGame();
    bool warning()const;
    void msgPopUp(const std::string& msg);

};