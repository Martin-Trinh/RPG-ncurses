#pragma once

#include <string>
#include <sstream>
#include <vector>

const int DEFAULT_STAT = 1;

class Stats
{
private:
    int m_HP;         // max HP
    int m_Mana;       // max energy for abilities
    int m_Strength;   // physical damage
    int m_Magic;      // magical damage
    int m_Armor;      // physical defence
    int m_Resistance; // magical defence
public:
    Stats(  int HP = DEFAULT_STAT,
            int mana = DEFAULT_STAT,
            int strength = DEFAULT_STAT,
            int magic = DEFAULT_STAT,
            int armor = DEFAULT_STAT,
            int resistance = DEFAULT_STAT);
    // gettes
    int getHP () const;
    int getMana () const;
    int getStrength () const;
    int getMagic ()const;
    int getArmor ()const;
    int getResistance ()const;
    // increase stats
    Stats& operator += (const Stats& rhs);
    Stats& operator -= (const Stats& rhs);
    // data for saving into file
    void loadStats(std::istringstream& iss);
};