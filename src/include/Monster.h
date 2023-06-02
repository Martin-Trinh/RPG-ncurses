#pragma once

#include "Character.h"
#include "Hero.h"
#include "Skill.h" //attack skill

class Monster: public Character{
private:
    Skill * m_Skill;
    int m_ExpWorth;
    char m_Character;
public:
    Monster(WINDOW * win, const std::string& name, int x, int y, const Stats &stats, 
            Skill * skill, int expWorth, char character);
    void findHero();
    void useSkill(Hero& hero);
    std::string toData() const;
};