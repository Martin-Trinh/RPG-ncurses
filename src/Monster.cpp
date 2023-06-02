#include "include/Monster.h"

Monster::Monster(WINDOW * win, const std::string& name, int x, int y, const Stats &stats, 
                Skill * skill,int expWorth, char character)
    :Character{win, name, x, y, stats}, m_Skill{skill}, m_ExpWorth{expWorth}, m_Character{character}{}
void Monster::useSkill(Hero& hero){

}
std::string Monster::toData() const{
    std::stringstream res;

    res << Character::toData() 
        << m_Skill << ',' << m_ExpWorth << ',' << m_Character << '\n';
    return res.str();
}