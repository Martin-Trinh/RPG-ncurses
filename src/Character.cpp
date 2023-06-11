#include "include/Character.h"

Character::Character(const std::string &name, char character, int x, int y, const Stats &stats)
: Entity{name, character, x, y}, m_Stats{stats}
{
    m_CurrHP = m_Stats.getHP();
    m_CurrMana = m_Stats.getMana();
}
const Stats& Character:: getStats() const {return m_Stats;}
int Character::getCurrHP() const{return m_CurrHP;}
int Character::getCurrMana() const{return m_CurrMana;}

void Character::attack(Character *other, int damage, bool magical)
{
    if (magical)
    {
        damage += m_Stats.getMagic();
        damage -= other->m_Stats.getResistance();
        if(damage < 0)
            damage = 0;
        other->m_CurrHP -= damage;
    }
    else
    {
        damage += m_Stats.getStrength();
        damage -= other->m_Stats.getArmor();
        if(damage < 0)
            damage = 0;
        other->m_CurrHP -= damage;
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
