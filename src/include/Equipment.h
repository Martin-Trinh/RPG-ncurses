#pragma once
/**
 * Project Graphic RPG Engine
 * @author trinhdin
 */
#include "Item.h"
#include "Stats.h"
#include "Hero.h"
/**
 * @brief Equipment class, derived class from Item class
 * 
 */
class Equipment: public Item{
public:
    /// @brief Construct a new Equipment object
    Equipment(const std::string& name,char character, int x, int y, 
                const Stats& buff);
    /**
     * @brief  return new equipment with same attributes
     * @return Item* -> pointer to new equipment
     */
    virtual Item* clone() const override;
    /**
     * @brief use equipment on hero, polymorphic method, equip item to hero
     * 
     * @param hero -> hero to equip item on
     * @param outMsg -> message to display on log
     * @return true -> if equip successfully
     * @return false -> if equip failed
     */
    virtual bool use(Hero* hero, std::string& outMsg) override;
    ///@brief print description of equipment, polymorphic method
    ///@return std::string -> description of equipment
    virtual std::string printDescription() const override;
    /// @brief  get buff of equipment
    /// @return stats-> stats to increase when equip
    const Stats& getBuff() const;
private:
    /// @brief stats to increase when equip
    Stats m_Buff;
};