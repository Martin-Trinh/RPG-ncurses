#pragma once 
/**
 * Project Graphic RPG Engine
 * @author trinhdin
 */

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

/**
 * Reponsible for game loop, display game screen, handle input
 */
class Game{
private:
    /// @brief minimal size screen
    static const int m_SrcHeight = 35, m_SrcWidth = 120;
    /// @brief pointer to map storing all entities in game
    Map * m_Map = nullptr;
    /// @brief pointer to GameConfig class, that return all configuration to create entities
    GameConfig * m_GameConfig = nullptr;
    /// @brief Exit flag
    bool m_Exit = false;
    /// @brief Name of defalut map
    std::string m_DefaultMap = "map1";
    /// @brief Name of default configuration file
    std::string m_ConfigFile = "config1";
public:
    /// @brief Init ncurses and load configuration using GameConfig class
    Game();
    /// @brief delete map and end ncurses window
    ~Game();
    /// @brief display start menu for loading game, creating new game, exit game
    void displayMenu();
    /// @brief display window for selecting type of hero
    void createHero();
    /// @brief display game screen and handle input
    void displayGame();
    /// @brief display control key for game screen
    /// @param win -> window to display control key
    void displayControl(WINDOW* win) const;
    /// @brief display display a screen to get input from user
    void getInput(const vecStr& Description, std::string& input);
    /// @brief save game to file entered by user
    void saveGame();
    /**
     * @brief load game from file entered by user
     * 
     * @return true -> if game is loaded
     * @return false -> if game failed to load
     */
    bool loadGame();
    /**
     * @brief display warning about exiting the game
     * 
     * @return true -> if user want to exit the game
     * @return false -> if user want to continue the game
     */
    bool warning()const;
    /// @brief display message in pop up window and endgame
    void msgPopUp(const std::string& msg);
};