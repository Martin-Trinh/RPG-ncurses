#pragma once

#include "Character.h"
#include "Item.h"
#include "Skill.h"
#include "LogMsg.h"
#include "Equipment.h"

#include <array>
#include <algorithm>
#include <fstream>
#include <sstream>

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

    LogMsg * m_Log = nullptr;
    WINDOW* m_StatsWin;
public:
    Hero(const std::string& name, int x, int y, const Stats &stats);
    void setCurrAttributes(int currHP, int currMana, int exp, int nextLevelExp, int level);
    ~Hero();
    // copy constructor
    Hero(const Hero& hero);
    //getters
    LogMsg* getLog() const;
    WINDOW* getStatsWin()const;
    void gainExp(int amount);
    char move(WINDOW* win, int margin, int x, int y);
    void addSkill(Skill * skill);
    bool addItem(Item* item);
    void removeItem(size_t index);
    void useSkill(size_t index, Character* monster);
    void decreaseCooldown();
    bool useItem(size_t index);
    bool unequip(size_t index);
    bool equip(Equipment* item, int type);
    
    void addStatsWin(WINDOW* win);
    void addLogWin(LogMsg* log);
    void save(const std::string&filename) const;

    void openInventory(WINDOW * win, WINDOW *control);

    void displayBackPack(WINDOW * win, WINDOW* detail, int selected, bool backpack)const;
    void displayEquipment(WINDOW * win, WINDOW* detail, int selected, bool backpack)const;
    void displayDetail(WINDOW* win, const std::string& description)const;
    void displayStats() const;
    void displaySkill(WINDOW* win) const;
    void displayControls(WINDOW* win) const;
    
};