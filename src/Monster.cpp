#include "include/Monster.h"

Monster::Monster(WINDOW * win, const std::string& name, char character, int x, int y, const Stats &stats, 
                Skill * skill,int expWorth)
    :Character{win, name, character, x, y, stats}, m_Skill{skill}, m_ExpWorth{expWorth}{}
void Monster::useSkill(Hero& hero){

}