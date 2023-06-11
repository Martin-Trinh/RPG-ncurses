#pragma once
/**
 * Project Graphic RPG Engine
 * @author trinhdin
 */

#include "Position.h"
#include "Stats.h"
#include "Entity.h"

/**
 *Abstract class representing character on the map
 */
class Character : public Entity{
protected:
    /// @brief stats of character
    Stats m_Stats;
    /// @brief current hp
    int m_CurrHP;
    /// @brief current mana
    int m_CurrMana;
public:
    /**
     * @brief Construct a new Character object
     * 
     * @param name -> name of character
     * @param character -> character to display on map
     * @param x -> x position
     * @param y ->  y position
     * @param stats -> stats of character
     */
    Character(const std::string& name, char character, int x, int y, const Stats &stats);
    // getters
    const Stats& getStats() const;
    int getCurrHP() const;
    int getCurrMana() const;
    /**
     * @brief increase stats of character
     * 
     * @param stat -> stats to increase
     */
    void statsBuff(const Stats& stat);
    /**
     * @brief increase HP of character
     * 
     * @param amount -> amount to increase
     */
    void increaseHP(int amount);
    /**
     * @brief increase mana of character
     * 
     * @param amount -> amount to increase
     */
    void increaseMana(int amount);
    /**
     * @brief attack other character
     * 
     * @param other -> other character
     * @param damage -> damage to deal
     * @param magical -> true if magical attack, false if physical attack
     */
    void attack(Character * other, int damage, bool magical);
};
