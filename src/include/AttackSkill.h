#pragma once

#include "Skill.h"

class AttackSkill: public Skill{
private:
    int m_Damage;
    bool m_Magical;
public:
    AttackSkill(const std::string &name, int cooldown, int cost, int damage, bool magical);
    virtual void use(Character* self, Character* enemy) override;
};