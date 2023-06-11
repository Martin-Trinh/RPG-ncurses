#pragma once
/**
 * Project Graphic RPG Engine
 * @author trinhdin
 */
#include <string>
#include <sstream>
#include "Character.h"
/**
 * @brief Abstract class representing skill of character
 */
class Skill
{
public:
    /// @brief type of skill passice used every round and active used manually
    enum class Type {ACTIVE, PASSIVE};
    /// @brief Construct a new Skill object
    Skill(const std::string &name, int cooldown, int cost, Type type);
    virtual ~Skill() = default;

    // getters
    const std::string &getName() const;
    int getCurrCooldown() const;
    int getCost() const;
    Type getType() const;
    // polymorfism
    /// @brief return new copy of skill with same attributes
    virtual Skill *clone() const = 0;
    /**
     * @brief use skill on enemy or self, 
     * @param self -> character that uses skill
     * @param enemy -> enemy
     */
    virtual void use(Character *self, Character *enemy) = 0;
    /// @brief print description of skill, polymorphic method
    virtual std::string printDescription() const;
    /// @brief decrease cooldown of skill
    void decreaseCooldown();
protected:
    /// @brief name of skill
    std::string m_Name;
    /// @brief cooldown of skill
    int m_Cooldown;
    /// @brief current cooldown of skill
    int m_CurrCooldown = 0; 
    /// @brief cost of skill
    int m_Cost;
    /// @brief type of skill
    Type m_Type;
};