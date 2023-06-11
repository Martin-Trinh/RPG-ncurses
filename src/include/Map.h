#pragma once
/**
 * Project Graphic RPG Engine
 * @author trinhdin
 */
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
#include "LogMsg.h"
#include "Gate.h"
#include "AttackSkill.h"
#include "RegenSkill.h"
#include "GameConfig.h"

class Map{
private:
    static const int m_Margin = 2;
    /// @brief player winning status
    bool m_Winning = false;
    /// @brief map of character to display
    std::vector<std::string> m_Map;
    /// @brief Hero on map
    Hero * m_Hero = nullptr;
    /// @brief vector of all items on map
    std::vector<Item*> m_Items;
    /// @brief vector of all monsters on map
    std::vector<Monster*> m_Monsters;
    /// @brief vector of all gates on map
    std::vector<Gate*> m_Gates;
    ///@brief configuration for loading entities
    GameConfig* m_GameConfig = nullptr;
public:
    /**
     * @brief load map from file and store it in vector of strings
     * 
     * @param mapFile -> name of map file
     * @param config -> config pointer initialization
     */
    Map(const std::string& mapFile, GameConfig* config);
    /// @brief delete all entities on map
    ~Map();
    /**
     * @brief save map with every entity on it to file
     * 
     * @param file -> name of file to save map
     */
    void save(const std::string& file);
    /**
     * @brief load map from file, and every entity on it based on configuration
     * 
     * @param heroName -> name of hero to find in configuration
     * @param newGame -> flag to check if it is new game or load game
     */
    void loadEntity(const std::string& heroName, bool newGame);
    /**
     * @brief load hero from saved file and store it in m_Hero
     * 
     * @param filename -> name of file to load hero
     * @param config -> pointer to GameConfig class for hero configuring
     */
    void loadHeroFromFile(const std::string& filename, GameConfig* config);
    /**
     * @brief get into combat mode between hero and monster
     * 
     * @param win -> window to display comabt on
     * @param hero -> hero in combat
     * @param monster -> monster in combat
     * @return true -> hero won
     * @return false -> hero lost
     */
    bool combat(WINDOW* win, Hero* hero, Monster* monster);
    /**
     * @brief display control key for combat mode
     * 
     * @param win -> window to display control key
     */
    void displayControl(WINDOW* win) const;
    /**
     * @brief handle the key pressed by user
     * 
     * @param win -> window to getkey
     * @param control -> window to display control key
     * @return int -> key pressed
     */
    int getKey(WINDOW* win, WINDOW* control);
    // getters
    Hero* getHero() const;
    bool heroWon() const;
    /**
     * @brief display map with every entity on it
     * 
     * @param win -> window to display map
     */
    void display(WINDOW* win);
};