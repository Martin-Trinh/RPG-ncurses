#pragma once

#include <string>
#include <sstream>
#include "Character.h"

class Skill
{

protected:
    std::string m_Name;
    int m_Cooldown;
    int m_CurrCooldown = 0; 
    int m_Cost;

public:
    Skill(const std::string &name, int cooldown, int cost);
    virtual ~Skill() = default;

    // getters
    const std::string &getName() const;
    int getCurrCooldown() const;
    int getCost() const;
    // polymorfism
    virtual void use(Character *self, Character *enemy) = 0;
    void decreaseCooldown();
    virtual std::string toData() const;

};