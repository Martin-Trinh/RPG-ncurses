#pragma once

#include "Item.h"
#include "Stats.h"

class Equipment: public Item{
private:
    Stats m_Buff;
    int m_Durability;
public:
    Equipment(const std::string& name,char character, int x, int y, 
                const Stats& buff, int durability = 5);
    virtual bool use(Hero* hero) override;
    virtual std::string toData() const override;
};