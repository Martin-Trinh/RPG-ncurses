#pragma once
/**
 * Project Graphic RPG Engine
 * @author trinhdin
 */
#include "Skill.h"

/**
 * Attack skill class, inherit from Skill class
 */
class AttackSkill: public Skill{
private:
    /// @brief damage of skill
    int m_Damage;
    /// @brief type of skill
    bool m_Magical;
public:
    /// @brief Construct a new Attack Skill object
    AttackSkill(const std::string &name, int cooldown, int cost, Type type,int damage, bool magical);
    /// @brief return new copy of skill with same attributes
    virtual Skill* clone()const override;
    /**
     * @brief use skill on enemy or self, attack enemy with damage base on type of attack
     * 
     * @param self -> character that uses skill
     * @param enemy -> enemy to attack
     */
    virtual void use(Character* self, Character* enemy) override;
    /// @brief print description of skill, polymorphic method
    virtual std::string printDescription()const override;
};