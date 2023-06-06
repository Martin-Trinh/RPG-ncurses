#include "include/Monster.h"

Monster::Monster(const std::string& name, int x, int y, const Stats &stats, 
                Skill * skill,int expWorth, char character)
    :Character{name, x, y, stats}, m_Skill{skill}, m_ExpWorth{expWorth}, m_Character{character}{}

bool Monster::useSkill(Character* hero){
    if(m_Skill->getCooldown() == 0){
        // skill in cooldown
        return false;
    }
    if(m_Skill->getCost() > m_CurrMana){
        // not enough mana
        return false;
    }
    m_Skill->use(this, hero);
    return true;
}

int Monster::getExp() const{return m_ExpWorth;}

void Monster::displayMonster(WINDOW* win) const{
    mvwaddch(win, m_Pos.m_Y, m_Pos.m_X, m_Character);
}
std::string Monster::toData() const{
    std::stringstream res;

    res << Character::toData() 
        << m_Skill << ',' << m_ExpWorth << ',' << m_Character << '\n';
    return res.str();
}

void Monster::displayStats(WINDOW* win) const{
    werase(win);
    box(win, 0, 0);
    int line = 0;
    mvwprintw(win, line++, 1, "Monster stats");
    mvwprintw(win, line++, 1, "Name: %s", m_Name.c_str());
    mvwprintw(win, line++, 1, "HP: %d / %d", m_Stats.getHP(), m_CurrHP);
    mvwprintw(win, line++, 1, "Mana: %d / %d", m_Stats.getMana(), m_CurrMana);
    mvwprintw(win, line++, 1, "Strength: %d", m_Stats.getStrength());
    mvwprintw(win, line++, 1, "Magic: %d", m_Stats.getMagic());
    mvwprintw(win, line++, 1, "Armor: %d", m_Stats.getArmor());
    mvwprintw(win, line++, 1, "Resistance: %d", m_Stats.getResistance());
    mvwprintw(win, line++, 1, "Exp worth: %d", m_ExpWorth);
    wrefresh(win);
}
