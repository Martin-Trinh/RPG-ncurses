#pragma once

#include "Skill.h"

class AttackSkill: public Skill{
private:
    int m_Damage;
    bool m_Magical;
public:
    AttackSkill(const std::string &name, int cooldown, int cost, Type type,int damage, bool magical);
    virtual Skill* clone()const override;
    virtual void use(Character* self, Character* enemy) override;
    virtual std::string printDescription()const override;
    virtual std::string toData()const override; 
};