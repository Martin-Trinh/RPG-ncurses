#pragma once

#include "Item.h"

class Potion: public Item{
private:
    int m_HP;
    int m_Mana;
    int m_Exp;
public:
    Potion(WINDOW* win, const std::string& name, char character, int x, int y,
             int hp, int mana, int exp);
    virtual bool use(Hero & hero) override;
    virtual std::string toData() const override;
};