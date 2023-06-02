#include "include/Stats.h"

Stats::Stats(int HP, int mana, int strength, int magic, int armor, int resistance)
    : m_HP{HP},
      m_Mana{mana},
      m_Strength{strength},
      m_Magic{magic},
      m_Armor{armor},
      m_Resistance{resistance}
{}
std::string Stats::toData() const{
  std::stringstream res;
  res << m_HP << "," 
    << m_Mana << "," 
    << m_Strength << "," 
    << m_Magic << ","
    << m_Armor << ","
    << m_Resistance;
    return res.str();
}