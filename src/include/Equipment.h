#pragma once

#include "Item.h"
#include "Stats.h"
#include "Hero.h"

class Equipment: public Item{
public:
    Equipment(const std::string& name,char character, int x, int y, 
                const Stats& buff);
    virtual Item* clone() const override;
    virtual bool use(Hero* hero, std::string& outMsg) override;
    virtual std::string printDescription() const override;
    // getters
    const Stats& getBuff() const;
private:
    Stats m_Buff;
};