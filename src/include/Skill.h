#pragma once

#include <string>
#include <sstream>
#include "Character.h"

class Skill
{
public:
    enum class Type {ACTIVE, PASSIVE};
    Skill(const std::string &name, int cooldown, int cost, Type type);
    virtual ~Skill() = default;

    // getters
    const std::string &getName() const;
    int getCurrCooldown() const;
    int getCost() const;
    Type getType() const;
    // polymorfism
    virtual Skill *clone() const = 0;
    virtual void use(Character *self, Character *enemy) = 0;
    virtual std::string printDescription() const;
    void decreaseCooldown();
    virtual std::string toData() const;
protected:
    std::string m_Name;
    int m_Cooldown;
    int m_CurrCooldown = 0; 
    int m_Cost;
    Type m_Type;
};