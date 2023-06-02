#include "include/Hero.h"

Hero::Hero (WINDOW * win, const std::string& name, int x, int y, const Stats &stats)
: Character {win, name, x, y, stats}{}

std::string Hero::toData() const{
    std::stringstream res;

    res << Character::toData() 
        << m_Exp << ',' << m_Level << '\n';

    for(size_t i = 0; i < inventoryMax; i++)
        res << m_Inventory.at(i)->toData() << '\n';
    for(size_t i = 0; i < skillMax; i++)
        res << m_Skills.at(i)->toData() << '\n';
    for(size_t i = 0; i < equipmentMax; i++)
        res << m_Equipment.at(i)->toData() << '\n';
    return res.str();
}
void Hero::displayHero() const{
    mvwaddch(m_Win, m_Pos.m_Y, m_Pos.m_X, '@');
}
