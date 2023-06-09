#include "include/AttackSkill.h"

AttackSkill::AttackSkill(const std::string &name, int cooldown, int cost, int damage, bool magical)
: Skill{name,cooldown, cost}, m_Damage{damage}, m_Magical{magical}{}

void AttackSkill::use(Character* self, Character* enemy){
    m_CurrCooldown = m_Cooldown;
    self->attack(enemy, m_Damage, m_Magical);
}
std::string AttackSkill::toData()const{
    std::stringstream res;
    res << Skill::toData() << ',' << m_Damage << ',' << m_Magical;
    return res.str();
}