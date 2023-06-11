#include "include/Stats.h"

Stats::Stats(int HP, int mana, int strength, int magic, int armor, int resistance)
    : m_HP{HP},
      m_Mana{mana},
      m_Strength{strength},
      m_Magic{magic},
      m_Armor{armor},
      m_Resistance{resistance}
{
}

int Stats::getHP() const { return m_HP; }
int Stats::getMana() const { return m_Mana; }
int Stats::getStrength() const { return m_Strength; }
int Stats::getMagic() const { return m_Magic; }
int Stats::getArmor() const { return m_Armor; }
int Stats::getResistance() const { return m_Resistance; }

Stats &Stats::operator+=(const Stats &rhs)
{
  m_HP += rhs.m_HP;
  m_Mana += rhs.m_Mana;
  m_Strength += rhs.m_Strength;
  m_Magic += rhs.m_Magic;
  m_Armor += rhs.m_Armor;
  m_Resistance += rhs.m_Resistance;
  return *this;
}
Stats &Stats::operator-=(const Stats &rhs)
{
  m_HP -= rhs.m_HP;
  m_Mana -= rhs.m_Mana;
  m_Strength -= rhs.m_Strength;
  m_Magic -= rhs.m_Magic;
  m_Armor -= rhs.m_Armor;
  m_Resistance -= rhs.m_Resistance;
  return *this;
}

void Stats::loadStats(std::istringstream& iss){
    iss >> m_HP >> m_Mana >> m_Strength >> m_Magic >> m_Armor >> m_Resistance;
}
