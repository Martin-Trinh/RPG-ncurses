#pragma once

#include <string>

class Skill{
protected:
    std::string m_Name;
    int m_Cooldown;
    int m_Cost;
public:
    Skill(const std::string& name, int cooldown, int cost);
    bool decreaseCooldown();
    virtual bool use() = 0;
};