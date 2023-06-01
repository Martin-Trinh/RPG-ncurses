#pragma once

#include "Item.h"

class Potion: public Item{
private:
public:
    Potion(std::string name, char character, int x, int y);
    virtual bool use(Hero & hero);
};