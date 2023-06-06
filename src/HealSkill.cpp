#include "include/HealSkill.h"

HealSkill::HealSkill(const std::string &name, int cooldown, int cost, int health)
: Skill{name,cooldown, cost}, m_Health{health}{}

void HealSkill::use(Character *self, Character *enemy){
    self->increaseHP(m_Health);
}