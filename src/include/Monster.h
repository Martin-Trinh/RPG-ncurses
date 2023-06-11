#pragma once
/**
 * Project Graphic RPG Engine
 * @author trinhdin
 */
#include "Character.h"
#include "Hero.h"
#include "Skill.h" //attack skill

class Monster: public Character{
private:
    /// skill of monster
    Skill * m_Skill;
    /// exp for hero when monster is killed
    int m_ExpWorth;
    /// character to display on map
    char m_Character;
public:
    /// @brief Construct a new Monster object
    Monster(const std::string& name, char character, int x, int y, const Stats &stats, 
            Skill * skill, int expWorth);
    /// @brief Delete skill
    ~Monster();
    /// @brief Deep copy of other monster
    Monster(const Monster& other);
    /// @brief Get the exp worth of monster
    /// @return return exp worth
    int getExp()const;
    /// @brief decrease cooldown of 
    void decreaseCooldown();
    /// @brief use skill 
    /// @param hero -> hero to attack
    /// @param outMsg -> out message to log console
    bool useSkill(Character* hero, std::string& outMsg);
    /// @brief display monster on window
    void displayMonster(WINDOW * win) const;
    /// @brief display monster stats on window
    void displayStats(WINDOW* win) const;
    /// @brief display monster skills on window
    void displaySkills(WINDOW* win) const;
};