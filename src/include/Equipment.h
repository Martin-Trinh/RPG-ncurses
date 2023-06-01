#pragma once

#include "Item.h"

class Equipment: public Item{
private:
    int m_Durability = 5;
public:
    virtual bool use(Hero& hero) override;
};