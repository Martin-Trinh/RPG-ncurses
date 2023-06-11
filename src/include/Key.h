#pragma once
/**
 * Project Graphic RPG Engine
 * @author trinhdin
 */
#include "Item.h"
#include "Hero.h"
#include "Gate.h"
#include <algorithm>
#include <vector>

class Key: public Item{
private:
    /// @brief all the locked gates on map
    std::vector<Gate*>* m_Gates;
public:
    /// @brief Construct a new Key object
    Key(const std::string& name, char character, int x, int y, std::vector<Gate*>* gates);
    /// @brief set m_Gates to nullptr
    ~Key();
    /// @brief  return new copy of key with same attributes
    virtual Item* clone() const override;
    /**
     * @brief get position of gate base on hero position and use it automatically
     * 
     * @param hero -> hero standing at the gate
     * @param outMsg -> message to display on log
     * @return true -> if use successfully
     * @return false -> if use failed
     */
    virtual bool use(Hero* hero, std::string& outMsg) override;
    /// @brief print description of key, polymorphic method
    virtual std::string printDescription()const override;
};