#pragma once

#include <string>
#include <sstream>
#include <vector>

const int DEFAULT_STAT = 1;

struct Stats
{
    int m_HP;         // max HP
    int m_Mana;       // energy for abilities
    int m_Strength;   // physical damage
    int m_Magic;      // magical damage
    int m_Armor;      // physical defence
    int m_Resistance; // magical defence

    Stats(  int HP = DEFAULT_STAT,
            int mana = DEFAULT_STAT,
            int strength = DEFAULT_STAT,
            int magic = DEFAULT_STAT,
            int armor = DEFAULT_STAT,
            int resistance = DEFAULT_STAT);
    std::string toData() const;

};