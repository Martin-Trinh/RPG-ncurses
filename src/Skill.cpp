#include "include/Skill.h"

Skill::Skill (std::string name, int cooldown, int cost)
    :m_Name{name}, m_Cooldown{cooldown}, m_Cost{cost} {}

bool Skill::decreaseCooldown(){
    if (m_Cooldown == 0)    
        return false;
    m_Cooldown--;
    return true;
}