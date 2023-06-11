#pragma once
/**
 * Project Graphic RPG Engine
 * @author trinhdin
 */
#include "Skill.h"

class RegenSkill: public Skill{
private:
    /// @brief amount hp or mana for regeneration
    int m_Amount;
    /// @brief hp or mana regeneration
    bool m_HP;
public:
    /// @brief Construct a new Regen Skill object
    RegenSkill(const std::string &name, int cooldown, int cost, Type type, int amount, bool hp);
    /// @brief return new copy of skill with same attributes
    virtual Skill* clone()const override;
    /**
     * @brief use skill on enemy or self, regen hp or mana for self
     * 
     * @param self -> character that uses skill
     * @param enemy -> enemy
     */
    virtual void use(Character *self, Character *enemy) override;
    /// @brief print description of skill, polymorphic method
    virtual std::string printDescription()const override;
};