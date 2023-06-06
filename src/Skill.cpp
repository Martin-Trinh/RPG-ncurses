#include "include/Skill.h"

Skill::Skill (const std::string& name, int cooldown, int cost)
    :m_Name{name}, m_Cooldown{cooldown}, m_Cost{cost} {}

const std::string& Skill::getName() const{return m_Name;}
int Skill::getCooldown() const{return m_Cooldown;}
int Skill::getCost() const{return m_Cost;}

void Skill::decreaseCooldown(){
    if(!m_Cooldown)
        m_Cooldown--;
}

std::string Skill::toData() const{
    std::stringstream res;
    res << m_Name << ',' << m_Cooldown << ',' << m_Cost;
    return res.str();
}