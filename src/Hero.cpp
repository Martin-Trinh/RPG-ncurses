#include "include/Hero.h"

Hero::Hero(const std::string &name, int x, int y, const Stats &stats)
    : Character{name, x, y, stats}
{
    m_Equipments.fill(NULL);
}

Hero::~Hero()
{
    for (size_t i = 0; i < m_Inventory.size(); i++)
        delete m_Inventory.at(i);
    for (size_t i = 0; i < m_Skills.size(); i++)
        delete m_Skills.at(i);
    for (size_t i = 0; i < equipmentMax; i++)
        delete m_Equipments.at(i);
    delete m_Log;
}

bool Hero::addSkill(Skill *skill)
{
    if (m_Skills.size() == skillMax)
        return false;
    m_Skills.push_back(skill);
    return true;
}
bool Hero::addItem(Item *item)
{
    if (m_Inventory.size() == inventoryMax)
    {
        m_Log->displayMsg("Inventory full");
        return false;
    }
    m_Inventory.push_back(item);
    m_Log->displayMsg("Picked up " + item->getName());
    return true;
}
void Hero::gainExp(int amount)
{
    while ((m_Exp += amount) >= m_NextLevelExp)
    {
        m_Exp -= m_NextLevelExp;
        m_Level++;
        m_NextLevelExp += 20;
    }
}
bool Hero::useSkill(size_t index, Character *monster)
{
    if (index >= m_Skills.size())
        return false;
    if (m_Skills.at(index)->getCooldown() == 0)
    {
        // skill in cooldown
        return false;
    }
    if (m_Skills.at(index)->getCost() > m_CurrMana)
    {
        // not enough mana
        return false;
    }
    m_Skills.at(index)->use(this, monster);
    return true;
}
bool Hero::useItem(size_t index)
{
    std::string msg;
    if (m_Inventory.at(index) && m_Inventory.at(index)->use(this, msg))
    {
        m_Log->displayMsg(msg);
        return true;
    }
    return false;
}
bool Hero::equip(Equipment *item, int type)
{
    auto it = std::find(m_Inventory.begin(), m_Inventory.end(), item);
    if (m_Equipments[type] != NULL)
    {
        return false;
    }
    m_Equipments[type] = dynamic_cast<Equipment *>(*it);
    m_Stats += m_Equipments[type]->getBuff();
    *it = NULL;
    return true;
}
bool Hero::unequip(size_t index)
{
    if (m_Inventory.size() == inventoryMax)
        return false;
    m_Stats -= m_Equipments.at(index)->getBuff();
    addItem(m_Equipments.at(index));
    m_Equipments.at(index) = NULL;
    return true;
}

char Hero::move(WINDOW *win, int x, int y)
{
    char target = mvwinch(win, y, x);
    if (target == '#')
    {
        // hit to a wall
    }
    else if (target == '-')
    {
        
        // search for key in inventory
    }
    else
    {
        m_Pos.m_Y = y;
        m_Pos.m_X = x;
    }
    return target;
}
void Hero::openInventory(WINDOW *win, WINDOW *control)
{

    int line = 0;
    werase(control);
    box(control, 0, 0);
    mvwprintw(control, line++, 1, "Control keys");
    line++;
    mvwprintw(control, line++, 1, "Select:     <arrow key>");
    mvwprintw(control, line++, 1, "Use item:   <e>");
    mvwprintw(control, line++, 1, "Unequip :   <e>");
    mvwprintw(control, line++, 1, "Toggle tab: <s>");
    mvwprintw(control, line++, 1, "Close:      <i>");
    wrefresh(control);

    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 0, 1, "Inventory");

    WINDOW *inven = newwin(inventoryMax + 2, 28, 2, 2);
    WINDOW *equip = newwin(equipmentMax + 2, 30, 2, 30);
    WINDOW *detail = newwin(8, 50, inventoryMax + 4, 2);

    keypad(inven, true);
    keypad(equip, true);
    box(detail, 0, 0);
    mvwprintw(detail, 0, 1, "Item detail");

    int key, selected = 0;
    bool backpack = true;
    while (1)
    {
        displayBackPack(inven, detail, selected, backpack);
        displayEquipment(equip, detail, selected, backpack);
        if (backpack)
        {
            key = wgetch(inven);
            switch (key)
            {
            case KEY_DOWN:
                if (++selected > (int)m_Inventory.size() - 1)
                    selected = 0;
                break;
            case KEY_UP:
                if (--selected < 0)
                    selected = m_Inventory.size() - 1;
                break;
            case 'e':
                if (m_Inventory.size() > 0 && this->useItem(selected))
                {
                    delete m_Inventory.at(selected);
                    m_Inventory.erase(m_Inventory.begin() + selected);
                }else{
                    m_Log->displayMsg("No item to use");
                }
                break;
            default:
                break;
            }
        }
        else
        {
            key = wgetch(equip);
            switch (key)
            {
            case KEY_DOWN:
                if (++selected > (int)m_Equipments.size() - 1)
                    selected = 0;
                break;
            case KEY_UP:
                if (--selected < 0)
                    selected = m_Equipments.size() - 1;
                break;
            case 'e':
                if(m_Equipments.at(selected)){
                    if (this->unequip(selected))
                        m_Log->displayMsg("Unequip " + m_Equipments.at(selected)->getName());
                }else{
                    m_Log->displayMsg("No equipment to unequip");
                }
                break;
            default:
                break;
            }
        }
        if (key == 'i')
            break;
        if (key == 's'){
            backpack = !backpack;
            selected = 0;
        }
    };
    delwin(inven);
    delwin(equip);
    delwin(detail);
}
void Hero::displayBackPack(WINDOW *win, WINDOW *detail, int selected, bool backpack)
{
    werase(win);
    box(win, 0, 0);
    if(backpack)
        wattron(win, A_STANDOUT);
    mvwprintw(win, 0, 1, "Backpack");
    wattroff(win, A_STANDOUT);
    for (size_t i = 0; i < m_Inventory.size(); i++)
    {
        if (backpack && (int)i == selected)
        {
            wattron(win, A_STANDOUT);
            // print detail
        }
        mvwprintw(win, i + 1, 2, "%s", m_Inventory.at(i)->getName().c_str());
        wattroff(win, A_STANDOUT);
    }
    wrefresh(win);
    wrefresh(detail);

}
void Hero::displayEquipment(WINDOW *win, WINDOW *detail, int selected, bool backpack)
{
    werase(win);
    box(win, 0, 0);
    if(!backpack)
        wattron(win, A_STANDOUT);
    mvwprintw(win, 0, 1, "Equipment");
    wattroff(win, A_STANDOUT);
    mvwprintw(win, 1, 1, "Head:");
    mvwprintw(win, 2, 1, "Chest:");
    mvwprintw(win, 3, 1, "Leg:");
    mvwprintw(win, 4, 1, "Foot:");
    mvwprintw(win, 5, 1, "Weapon:");
    mvwprintw(win, 6, 1, "Amulet:");

    for (size_t i = 0; i < m_Equipments.size(); i++)
    {
        if (!backpack && (int)i == selected)
            wattron(win, A_STANDOUT);
        if (m_Equipments.at(i) == NULL)
            mvwprintw(win, i + 1, 10, "Empty");
        else
            mvwprintw(win, i + 1, 10, "%s", m_Equipments.at(i)->getName().c_str());
        wattroff(win, A_STANDOUT);
    }
    wrefresh(win);
}
void Hero::addLogWin(LogMsg *log) { m_Log = log; }
void Hero::displayHero(WINDOW *win) const
{
    mvwaddch(win, m_Pos.m_Y, m_Pos.m_X, '@');
}
void Hero::displayStats(WINDOW *win) const
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
void Hero::displaySkill(WINDOW *win) const
{
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 0, 1, "Hero's skill");
    for (size_t i = 0; i < m_Skills.size(); i++)
    {
        mvwprintw(win, int(i + 1), 1, "%s %d %d",
                  m_Skills.at(i)->getName().c_str(),
                  m_Skills.at(i)->getCooldown(),
                  m_Skills.at(i)->getCost());
    }
    wrefresh(win);
}

std::string Hero::toData() const
{
    std::stringstream res;

    res << Character::toData()
        << m_Exp << ',' << m_Level << '\n';

    for (size_t i = 0; i < m_Inventory.size(); i++)
        res << m_Inventory.at(i)->toData() << '\n';
    for (size_t i = 0; i < m_Skills.size(); i++)
        res << m_Skills.at(i)->toData() << '\n';
    for (size_t i = 0; i < m_Equipments.size(); i++)
        res << m_Equipments.at(i)->toData() << '\n';
    return res.str();
}
