#include "include/AttackSkill.h"

AttackSkill::AttackSkill(const std::string &name, int cooldown, int cost, Type type, int damage, bool magical)
: Skill{name, cooldown, cost, type}, m_Damage{damage}, m_Magical{magical}{}
Skill* AttackSkill::clone()const{
    return new AttackSkill(*this);
}
void AttackSkill::use(Character* self, Character* enemy){
    m_CurrCooldown = m_Cooldown;
    self->attack(enemy, m_Damage, m_Magical);
}
std::string AttackSkill::printDescription()const{
    std::stringstream res;
    res << Skill::printDescription() << "\n" << "Damage: " << m_Damage << " | " 
    << "Type: ";
    m_Magical ? res << "Magical" : res << "Physical";
    return res.str();
}