#pragma once
/**
 * Project Graphic RPG Engine
 * @author trinhdin
 */
#include "Entity.h"
#include <ncurses.h>
#include <string>
class Hero;
/**
 * @brief Abstract class representing item on the map
 * 
 */
class Item : public Entity{
public:
    /// @brief Construct a new Item object
    Item(const std::string& name, char character, int x, int y);
    /// @brief virtual destructor for derived classes
    virtual ~Item() = default;
    /// @brief deep copy of other item
    /// @return pointer to new item
    virtual Item* clone()const = 0;
    /**
     * @brief use item on hero, polymorphic method
     * 
     * @param hero -> hero to use item on
     * @param outMsg -> message to display on log
     * @return true 
     * @return false 
     */
    virtual bool use(Hero* hero, std::string& outMsg) = 0;
    /**
     * @brief print description of item, polymorphic method
     * 
     * @return std::string -> description of item
     */
    virtual std::string printDescription()const = 0;
    /// @brief compare 2 items if they are equal base on their position on map
    bool operator == (const Item& other) const;
};