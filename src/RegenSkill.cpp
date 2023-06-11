#include "include/RegenSkill.h"

RegenSkill::RegenSkill(const std::string &name, int cooldown, int cost, Type type,int amount, bool hp)
: Skill{name,cooldown, cost, type},m_Amount{amount}, m_HP{hp}{}
Skill* RegenSkill::clone()const{
    return new RegenSkill(*this);
}
void RegenSkill::use(Character *self, Character *enemy){
    m_CurrCooldown = m_Cooldown;
    if(m_HP)
        self->increaseHP(m_Amount);
    else
        self->increaseMana(m_Amount);
}
std::string RegenSkill::printDescription()const{
    std::stringstream res;
    res << Skill::printDescription() << "\n" << "Amount: " << m_Amount << " | " 
    << "Type: ";
    m_HP ? res << "HP" : res<< "Mana" ;
    return res.str();
}
std::string RegenSkill::toData()const{
    std::stringstream res;
    res << Skill::toData() << ',' << m_Amount << ',' << m_HP;
    return res.str();
}