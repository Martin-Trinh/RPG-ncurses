#pragma once

#include "Position.h"
#include "Stats.h"
#include "Entity.h"
#include <ncurses.h>


class Character : public Entity{
protected:
    Stats m_Stats;
    
    int m_CurrHP;
    int m_CurrMana;
public:
    Character(const std::string& name, char character, int x, int y, const Stats &stats);

    void statsBuff(const Stats& stat);
    void increaseHP(int amount);
    void increaseMana(int amount);

    void attack(Character * other, int damage, bool magical);
    char move(WINDOW* win, int x, int y);

    const Stats& getStats() const;
    int getCurrHP() const;
    int getCurrMana() const;
};
