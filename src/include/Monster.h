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
    Monster(const std::string& name, int x, int y, const Stats &stats, 
            Skill * skill, int expWorth, char character);

    void findHero();
    bool useSkill(Character* hero);
    int getExp()const;
    void displayMonster(WINDOW * win) const;
    std::string toData() const;
    void displayStats(WINDOW* win) const;

};