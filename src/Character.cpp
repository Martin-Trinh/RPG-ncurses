#include "include/Character.h"

Character::Character(const std::string &name, int x, int y, const Stats &stats)
    : m_Name{name}, m_Pos{x, y}, m_Stats{stats}
{
    m_CurrHP = m_Stats.getHP();
    m_CurrMana = m_Stats.getMana();
}

Position Character:: getPos() const {return m_Pos;}

std::string Character::toData() const
{
    std::stringstream res;
    res << m_Name << ","
        << m_Pos.toData()
        << m_Stats.toData()
        << m_CurrHP << "," << m_CurrMana;
    return res.str();
}

void Character::attack(Character *other, int damage, bool magical)
{
    if (magical)
    {
        other->m_CurrHP -= (damage + other->m_Stats.getResistance());
    }
    else
    {
        other->m_CurrHP -= (damage - other->m_Stats.getArmor());
    }
    if (other->m_CurrHP < 0)
        other->m_CurrHP = 0;
}

void Character::statsBuff(const Stats &stat)
{
    m_Stats += stat;
}
void Character::increaseHP(int amount){
    if(amount < 0)
        amount = 0;
    m_CurrHP += amount;
    if(m_CurrHP > m_Stats.getHP())
        m_CurrHP = m_Stats.getHP();
}
void Character::increaseMana(int amount){
    if(amount < 0)
        amount = 0;
    m_CurrMana += amount;
    if(m_CurrMana > m_Stats.getMana())
        m_CurrMana = m_Stats.getMana();
}
int Character::getCurrHP() const{return m_CurrHP;}
int Character::getCurrMana() const{return m_CurrMana;}