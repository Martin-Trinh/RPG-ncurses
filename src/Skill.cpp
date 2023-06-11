#include "include/Skill.h"

Skill::Skill (const std::string& name, int cooldown, int cost, Type type)
    :m_Name{name}, m_Cooldown{cooldown}, m_Cost{cost}, m_Type{type}{
        if(type == Type::PASSIVE && (cost != 0))
            throw "Passive skill cannot have cost";
}

const std::string& Skill::getName() const{return m_Name;}
int Skill::getCurrCooldown() const{return m_CurrCooldown;}
int Skill::getCost() const{return m_Cost;}
Skill::Type Skill::getType() const{return m_Type;}
void Skill::decreaseCooldown(){
    if(m_CurrCooldown)
        m_CurrCooldown--;
    if(m_CurrCooldown < 0)
        throw "Cooldown below 0";
}
std::string Skill::printDescription() const{
    std::stringstream res;
    res << "Name: " << m_Name << "\n" << "Cooldown: " << m_Cooldown << " | " << "Cost: " << m_Cost;
    return res.str();
}