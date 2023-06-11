#include "include/Monster.h"

Monster::Monster(const std::string& name, char character ,int x, int y, const Stats &stats, 
                Skill * skill,int expWorth)
    :Character{name, character,x, y, stats}, m_Skill{skill}, m_ExpWorth{expWorth}{}
Monster::~Monster(){
    delete m_Skill;
}
Monster::Monster(const Monster& other): Character(other){
    m_Skill = other.m_Skill->clone();
    m_ExpWorth = other.m_ExpWorth;
    m_Character = other.m_Character;
}
int Monster::getExp() const{return m_ExpWorth;}
bool Monster::useSkill(Character* hero, std::string& outMsg){
    if(m_Skill->getCurrCooldown() != 0){
        outMsg = "Monster's skill is in cooldown";
        // skill in cooldown
        return false;
    }
    if(m_Skill->getCost() > m_CurrMana){
        outMsg = "Monster doesn't have enough mana";
        // not enough mana
        return false;
    }
    outMsg = m_Name + " used " + m_Skill->getName() + " skill";
    m_Skill->use(this, hero);
    return true;
}
void Monster::decreaseCooldown(){
    m_Skill->decreaseCooldown();
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
    line++;
    mvwprintw(win, line++, 1, "Exp worth: %d", m_ExpWorth);
    wrefresh(win);
}
void Monster::displaySkills(WINDOW* win) const{
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 0, 1, "Monster's skill");
    std::string line;
    int row = 1, col = 1;
        line = m_Skill->printDescription();
        for(char i: line){
            if(col >= getmaxx(win) - 1 || i == '\n'){
                col = 1;
                row++;
            }
            if(i != '\n'){
                mvwaddch(win, row, col, i);
                col++;
            }
        }
        if(m_Skill->getType() == Skill::Type::ACTIVE)
            mvwprintw(win, ++row, 1, "Curr cooldown: %d", m_Skill->getCurrCooldown());
        else
            mvwprintw(win, ++row, 1, "Passive skill");
    wrefresh(win);
}
