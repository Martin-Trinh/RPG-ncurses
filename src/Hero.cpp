#include "include/Hero.h"


Hero::Hero (const std::string& name, int x, int y, const Stats &stats)
: Character {name, x, y, stats}{}

Hero::~Hero(){
    for(size_t i = 0; i < m_Inventory.size(); i++)
        delete m_Inventory.at(i);
    for(size_t i = 0; i < m_Skills.size(); i++)
        delete m_Skills.at(i);
    for(size_t i = 0; i < equipmentMax; i++)
        delete m_Equipments.at(i);
}

bool Hero::addSkill(Skill * skill){
    if(m_Skills.size() == skillMax)
        return false;
    m_Skills.push_back(skill);
    return true;
}
bool Hero::addItem(Item* item){
    if(m_Inventory.size() == inventoryMax)
        return false;
    m_Inventory.push_back(item);
    return true;
}
bool Hero::useItem(size_t index){
    if(index > m_Inventory.size())
        return false;
    m_Inventory.at(index)->use(this);
    return true;
}
void Hero::gainExp(int amount){
    while((m_Exp += amount) >= m_NextLevelExp){
        m_Exp -= m_NextLevelExp;
        m_Level++;
        m_NextLevelExp += 20;
    }
}
bool Hero::useSkill(size_t index, Character* monster){
    if(index >= m_Skills.size())
        return false;
    if(m_Skills.at(index)->getCooldown() == 0){
        // skill in cooldown
        return false;
    }
    if(m_Skills.at(index)->getCost() > m_CurrMana){
        // not enough mana
        return false;
    }
    m_Skills.at(index)->use(this, monster);
    return true;
}
bool Hero::unequip(size_t index){
    if(m_Inventory.size() == inventoryMax)
        return false;
    m_Inventory.push_back(m_Equipments.at(index));
    m_Equipments.at(index) = NULL;
    return true;
}

char Hero::move(WINDOW* win, int x, int y){
    char target = mvwinch(win, y, x);
    if(target == '#'){
        // hit to a wall
    }else if( target == '+'){
        // search for key in inventory
    }else{
        m_Pos.m_Y = y;
        m_Pos.m_X = x;
    }
    return target;
}
void Hero::openInventory(WINDOW * win, WINDOW* control, WINDOW*log){
    int key, selected = 0;
    std::vector<std::string> items = {
        "axe",
        "potion",
        "bread",
        "spear",
        "empty",
        "empty",
    };
    std::vector<std::string> equipments = {
        "Helmet",
        "Plate",
        "Weapon"};
    static std::vector<std::string> controls = {
        "Select:   <arrow key>",
        "Use item: <e>",
        "Close:    <i>",
    };

    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 0, 1, "Inventory");

    WINDOW *inven = newwin(items.size() + 2, 20, 4, 3);
    WINDOW *equip = newwin(8, 20, 4, 30);
    box(inven, 0, 0);
    box(equip, 0, 0);
    mvwprintw(inven, 0, 1, "Backpack");
    mvwprintw(equip, 0, 1, "Equipment");
    // sideWindow(control, "Control key", controls);
    bool inventory = true;
    while (1)
    {
        keypad(inven, true);
        keypad(equip, true);
        if (inventory)
        {
            for (size_t i = 0; i < items.size(); i++)
            {
                if ((int)i == selected)
                    wattron(inven, A_STANDOUT);
                mvwprintw(inven, i + 1, 2, "%s", items.at(i).c_str());
                wattroff(inven, A_STANDOUT);
            }
            wrefresh(win);
            wrefresh(inven);

            key = wgetch(inven);
            switch (key)
            {
            case KEY_DOWN:
                if (++selected > (int)items.size() - 1)
                    selected = 0;
                break;
            case KEY_UP:
                if (--selected < 0)
                    selected = items.size() - 1;
                break;
            case 's':
                inventory = false;
                selected = 0;
                break;
            case 'e':
                wmove(log, 1, 1);
                wclrtoeol(log);
                wprintw(log, "You used %s", items.at(selected).c_str());
                wrefresh(log);
                break;
            default:
                break;
            }
        }
        else
        {
            for (size_t i = 0; i < equipments.size(); i++)
            {
                if ((int)i == selected)
                    wattron(equip, A_STANDOUT);
                mvwprintw(equip, i + 1, 2, "%s", equipments.at(i).c_str());
                wattroff(equip, A_STANDOUT);
            }
            wrefresh(win);
            wrefresh(equip);

            key = wgetch(equip);
            switch (key)
            {
            case KEY_DOWN:
                if (++selected > (int)equipments.size() - 1)
                    selected = 0;
                break;
            case KEY_UP:
                if (--selected < 0)
                    selected = equipments.size() - 1;
                break;
            case 's':
                inventory = true;
                selected = 0;
                break;
            case 'e':
                wmove(log, 1, 1);
                wclrtoeol(log);
                wprintw(log, "You used %s", items.at(selected).c_str());
                wrefresh(log);
                break;
            default:
                break;
            }
        }
        if (key == 'i')
            break;
    };
    werase(win);
}
void Hero::displayHero(WINDOW * win) const{
    mvwaddch(win, m_Pos.m_Y, m_Pos.m_X, '@');
}

void Hero::displayStats(WINDOW* win) const
{
    werase(win);
    box(win, 0, 0);
    int line = 0;
    mvwprintw(win, line++, 1, "Name: %s", m_Name.c_str());
    line++;
    mvwprintw(win, line++, 1, "HP: %d / %d", m_Stats.getHP(), m_CurrHP);
    mvwprintw(win, line++, 1, "Mana: %d / %d", m_Stats.getMana(), m_CurrMana);
    mvwprintw(win, line++, 1, "Strength: %d", m_Stats.getStrength());
    mvwprintw(win, line++, 1, "Magic: %d", m_Stats.getMagic());
    mvwprintw(win, line++, 1, "Armor: %d", m_Stats.getArmor());
    mvwprintw(win, line++, 1, "Resistance: %d", m_Stats.getResistance());
    mvwprintw(win, line++, 1, "Exp: %d", m_Exp);
    mvwprintw(win, line++, 1, "Level: %d", m_Level);
    wrefresh(win);
}

void Hero::displaySkill(WINDOW* win) const{
    werase(win);
    box(win, 0, 0);
    for(size_t i = 0; i < m_Skills.size(); i++){
        mvwprintw(win, int(i + 1), 1,"%s %d %d",
        m_Skills.at(i)->getName().c_str(),
        m_Skills.at(i)->getCooldown(),
        m_Skills.at(i)->getCost());
    }
}

std::string Hero::toData() const{
    std::stringstream res;

    res << Character::toData() 
        << m_Exp << ',' << m_Level << '\n';

    for(size_t i = 0; i < m_Inventory.size(); i++)
        res << m_Inventory.at(i)->toData() << '\n';
    for(size_t i = 0; i < m_Skills.size(); i++)
        res << m_Skills.at(i)->toData() << '\n';
    for(size_t i = 0; i < m_Equipments.size(); i++)
        res << m_Equipments.at(i)->toData() << '\n';
    return res.str();
}

