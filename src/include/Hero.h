#pragma once

#include "Character.h"
#include "Item.h"
#include "Equipment.h"
#include "Position.h"
#include "Skill.h"
#include "LogMsg.h"
#include <array>
#include <algorithm>

class Equipment;

class Hero: public Character{
private:
    static const size_t inventoryMax = 12;
    static const size_t skillMax = 3;
    static const size_t equipmentMax = 6;

    int m_Exp = 0;
    int m_NextLevelExp = 10;
    int m_Level = 1;

    std::vector<Item*> m_Inventory;
    std::vector<Skill*> m_Skills;
    std::array<Equipment*, equipmentMax> m_Equipments;

    LogMsg * m_Log = NULL;

public:
    Hero(const std::string& name, int x, int y, const Stats &stats);
    ~Hero();

    void gainExp(int amount);

    void openInventory(WINDOW * win, WINDOW *control);
    void displayBackPack(WINDOW * win, WINDOW* detail, int selected, bool backpack);
    void displayEquipment(WINDOW * win, WINDOW* detail, int selected, bool backpack);
    char move(WINDOW* win, int x, int y);

    bool addSkill(Skill * skill);
    bool addItem(Item* item);
    bool useSkill(size_t index, Character* monster);
    bool useItem(size_t index);
    bool unequip(size_t index);
    bool equip(Equipment* item, int type);
    void addLogWin(LogMsg* log);
    // getters
    void displayHero(WINDOW* win) const;
    void displayStats(WINDOW* win) const;
    void displaySkill(WINDOW* win) const;
    std::string toData() const;
    
};