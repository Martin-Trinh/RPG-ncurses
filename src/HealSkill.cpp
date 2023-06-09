#include "include/HealSkill.h"

HealSkill::HealSkill(const std::string &name, int cooldown, int cost, int health)
: Skill{name,cooldown, cost}, m_Health{health}{}

void HealSkill::use(Character *self, Character *enemy){
    m_CurrCooldown = m_Cooldown;
    self->increaseHP(m_Health);
}
std::string HealSkill::toData()const{
    std::stringstream res;
    res << Skill::toData() << ',' << m_Health;
    return res.str();
}