#pragma once

#include "Character.h"
#include "Item.h"
#include "Skill.h"
#include "Equipment.h"



typedef std::vector<Item*> vecItem;
typedef std::vector<Equipment*> vecEquip;
typedef std::vector<Skill*> vecSkill;

class Hero: public Character{
private:
    vecItem m_Inventory;
    vecSkill m_Skills;
    vecEquip m_Equipment;

    size_t inventoryMax = 12;
    size_t equipmentMax = 4;
    int m_Exp = 0;
    int m_Level = 1;
public:
    Hero(WINDOW * win, const std::string& name, char character, int x, int y, const Stats &stats);
    bool addSkill(Skill * skill);
    bool pickUp(Item* item);
    bool useItem(size_t index);
    bool useSkill(size_t index);
    bool unequip(size_t index);
};