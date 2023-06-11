#pragma once
/**
 * Project Graphic RPG Engine
 * @author trinhdin
 */
#include <string>
#include <sstream>
#include <vector>

#define DEFAULT_STAT 0
/**
 * grouping stat of hero
 * 
 */
class Stats
{
private:
    /// @brief max hp 
    int m_HP;
    /// @brief  max mana
    int m_Mana;       
    /// @brief physical damage
    int m_Strength;
    /// @brief magical damage
    int m_Magic;
    /// @brief physical defense
    int m_Armor;   
    /// @brief magical defense  
    int m_Resistance; 
public:
    /// @brief Construct a new Stats object
    Stats(  int HP = DEFAULT_STAT,
            int mana = DEFAULT_STAT,
            int strength = DEFAULT_STAT,
            int magic = DEFAULT_STAT,
            int armor = DEFAULT_STAT,
            int resistance = DEFAULT_STAT);
    // getters
    int getHP () const;
    int getMana () const;
    int getStrength () const;
    int getMagic ()const;
    int getArmor ()const;
    int getResistance ()const;
    /// @brief increase stats
    Stats& operator += (const Stats& rhs);
    /// @brief decrease stats
    Stats& operator -= (const Stats& rhs);
};