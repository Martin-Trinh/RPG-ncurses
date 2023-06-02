#pragma once

#include "Item.h"
#include "Stats.h"

class Equipment: public Item{
private:
    Stats m_Buff;
    int m_Durability = 5;
public:
    Equipment(WINDOW* win, const std::string& name, char character, int x, int y, 
                const Stats& buff, int durability);
    virtual bool use(Hero& hero) override;
};