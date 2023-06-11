#pragma once

#include <sstream>
#include <string>
#include <ncurses.h>
#include <vector>
#include <fstream>
#include <iostream>

#include "Item.h"
#include "Potion.h"
#include "Equipment.h"
#include "Key.h"
#include "Monster.h"
#include "Hero.h"
#include "ncurses.h"
#include "LogMsg.h"
#include "Gate.h"
#include "AttackSkill.h"
#include "RegenSkill.h"
#include "GameConfig.h"

class Map{
private:
    static const int m_Margin = 2;
    bool m_Winning = false;
    std::vector<std::string> m_Map;

    Hero * m_Hero = nullptr;
    std::vector<Item*> m_Items;
    std::vector<Monster*> m_Monsters;
    std::vector<Gate*> m_Gates;
    
    GameConfig* m_GameConfig = nullptr;
public:
    Map(const std::string& mapFile, GameConfig* config);
    ~Map();
    void save(const std::string& file);
    void loadEntity(const std::string& heroName, bool newGame);
    void loadHeroFromFile(const std::string& filename, GameConfig* config);
    bool combat(WINDOW* win, Hero* hero, Monster* monster);
    void displayControl(WINDOW* win) const;
    int getKey(WINDOW* win, WINDOW* control);
    // getters
    Hero* getHero() const;
    bool heroWon() const;
    void display(WINDOW* win);
};