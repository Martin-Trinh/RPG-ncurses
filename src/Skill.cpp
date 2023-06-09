#include "include/Skill.h"

Skill::Skill (const std::string& name, int cooldown, int cost)
    :m_Name{name}, m_Cooldown{cooldown}, m_Cost{cost} {}

const std::string& Skill::getName() const{return m_Name;}
int Skill::getCurrCooldown() const{return m_CurrCooldown;}
int Skill::getCost() const{return m_Cost;}

void Skill::decreaseCooldown(){
    if(m_CurrCooldown)
        m_CurrCooldown--;
    if(m_CurrCooldown < 0)
        throw "Cooldown below 0";
}

std::string Skill::toData() const{
    std::stringstream res;
    res << m_Name << ',' << m_Cooldown << ',' << m_Cost;
    return res.str();
}