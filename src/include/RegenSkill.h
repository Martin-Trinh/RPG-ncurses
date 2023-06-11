#pragma once

#include "Skill.h"

class RegenSkill: public Skill{
private:
    int m_Amount;
    bool m_HP;
public:
    RegenSkill(const std::string &name, int cooldown, int cost, Type type, int amount, bool hp);
    virtual Skill* clone()const override;
    virtual void use(Character *self, Character *enemy) override;
    virtual std::string printDescription()const override;
    virtual std::string toData()const override;
};