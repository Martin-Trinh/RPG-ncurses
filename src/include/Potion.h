#pragma once

#include "Item.h"
#include "Hero.h"

class Potion: public Item{
private:
    int m_HP;
    int m_Mana;
    int m_Exp;
public:
    Potion(const std::string& name, char character, int x, int y,
             int hp, int mana, int exp);
    virtual bool use(Hero* hero, std::string& outMsg) override;
    virtual std::string printDescription()const override;
    virtual std::string toData() const override;
};