#pragma once

#include "Character.h"
#include "Item.h"
#include "Skill.h"
#include "Equipment.h"

#include <array>

typedef std::vector<Item*> vecItem;
typedef std::vector<Equipment*> vecEquip;
typedef std::vector<Skill*> vecSkill;

class Hero: public Character{
private:
    int m_Exp = 0;
    int m_Level = 1;

    static size_t inventoryMax;
    static size_t skillMax;
    static size_t equipmentMax;

    vecItem m_Inventory;
    vecEquip m_Skills;
    vecSkill m_Equipment;

public:
    Hero(WINDOW * win, const std::string& name, int x, int y, const Stats &stats);
    bool addSkill(Skill * skill);
    void levelUp();
    bool pickUp(Item* item);
    bool useItem(size_t index);
    bool useSkill(size_t index);
    bool unequip(size_t index);
    void openInventory();
    void displayHero() const;
    std::string toData() const;
    
};