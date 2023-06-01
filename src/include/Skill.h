#pragma once

#include <string>

class Skill{
private:
    std::string m_Name;
    int m_Cooldown;
    int m_Cost;
public:
    Skill(std::string name, int cooldown, int cost);
    bool decreaseCooldown();
    virtual bool use() = 0;
};