#pragma once

#include "Item.h"
#include "Hero.h"
#include "Gate.h"
#include <algorithm>
#include <vector>

class Key: public Item{
private:
    std::vector<Gate*>* m_Gates;
public:
    Key(const std::string& name, char character, int x, int y, std::vector<Gate*>* gates);
    virtual bool use(Hero* hero, std::string& outMsg) override;
    virtual std::string printDescription()const override;
    virtual std::string toData() const override;
};