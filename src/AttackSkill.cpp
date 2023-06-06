#include "include/AttackSkill.h"

AttackSkill::AttackSkill(const std::string &name, int cooldown, int cost, int damage, bool magical)
: Skill{name,cooldown, cost}, m_Damage{damage}, m_Magical{magical}{}

void AttackSkill::use(Character* self, Character* enemy){
    self->attack(enemy, m_Damage, m_Magical);
}