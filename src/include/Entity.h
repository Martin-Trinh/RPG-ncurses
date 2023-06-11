#pragma once
/**
 * Project Graphic RPG Engine
 * @author trinhdin
 */
#include "Position.h"
#include <ncurses.h>
#include <string>
#include <vector>

// alias for vector of strings
typedef std::vector<std::string> vecStr;
/**
 * Entity class, base class for all entity in game
 */
class Entity{
protected:
    ///@brief Name of entity
    std::string m_Name;
    /// @brief to display on map
    char m_Character;
    /// @brief Position of entity on map
    Position m_Pos;
public:
    /**
     * @brief Construct a new Entity object
     * 
     * @param name -> name of entity
     * @param character -> character to display on map
     * @param x -> x position
     * @param y ->  y position
     */
    Entity(const std::string& name, char character, int x, int y);
    // getters
    Position getPos()const;
    const std::string& getName()const;
    char getCharacter()const;
    /// @brief set position for entity
    void setPosition(int x, int y);
    /**
     * @brief Display entity on map
     * 
     * @param win -> ncurses window to display on
     * @param margin -> margin from start position of window
     */
    void displayEntity(WINDOW* win, int margin)const;
};