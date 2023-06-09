#pragma once

#include "Skill.h"

class HealSkill: public Skill{
private:
    int m_Health;
public:
    HealSkill(const std::string &name, int cooldown, int cost, int health);
    virtual void use(Character *self, Character *enemy) override;
    virtual std::string toData()const override;
};