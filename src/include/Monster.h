#pragma once

#include "Character.h"
#include "Hero.h"
#include "Skill.h" //attack skill

class Monster: public Character{
private:
    Skill * m_Skill;
    int m_ExpWorth;
public:
    Monster(WINDOW * win, const std::string& name, char character, int x, int y, const Stats &stats, 
            Skill * skill, int expWorth);
    void findHero();
    void useSkill(Hero& hero);
};