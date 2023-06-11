#pragma once
/**
 * Project Graphic RPG Engine
 * @author trinhdin
 */
#include "Entity.h"
#include "Item.h"
#include "Hero.h"

class Potion: public Item{
private:
    /// @brief hp to increase when use
    int m_HP;
    /// @brief mana to increase when use
    int m_Mana;
    /// @brief exp to increase when use
    int m_Exp;
public:
    /// @brief  Construct a new Potion object
    Potion(const std::string& name, char character, int x, int y,
             int hp, int mana, int exp);
    /// @brief  return new copy of potion with same attributes
    virtual Item* clone() const override;
    /**
     * @brief apply potion to hero, polymorphic method
     * 
     * @param hero -> hero to apply potion on
     * @param outMsg -> message to display on log
     * @return true 
     * @return false -
     */
    virtual bool use(Hero* hero, std::string& outMsg) override;
    /// @brief print description of potion, polymorphic method
    virtual std::string printDescription()const override;
};