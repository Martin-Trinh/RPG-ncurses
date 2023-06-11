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
    Monster(const std::string& name, char character, int x, int y, const Stats &stats, 
            Skill * skill, int expWorth);
    ~Monster();
    Monster(const Monster& other);
    int getExp()const;
    
    void findHero();
    void decreaseCooldown();
    bool useSkill(Character* hero, std::string& outMsg);

    void displayMonster(WINDOW * win) const;
    void displayStats(WINDOW* win) const;
    void displaySkills(WINDOW* win) const;
    std::string toData() const;

};