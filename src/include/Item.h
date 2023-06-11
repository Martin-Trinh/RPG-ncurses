#pragma once

#include "Entity.h"
#include <ncurses.h>
#include <string>
class Hero;

class Item : public Entity{
public:
    Item(const std::string& name, char character, int x, int y);
    virtual ~Item() = default;
    void removeItem(WINDOW * win) const;
    virtual Item* clone()const = 0;
    virtual bool use(Hero* hero, std::string& outMsg) = 0;
    virtual std::string printDescription()const = 0;
    bool operator == (const Item& other) const;
};