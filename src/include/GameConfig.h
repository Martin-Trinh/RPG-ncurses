#pragma once
/**
 * Project Graphic RPG Engine
 * @author trinhdin
 */
#include "Hero.h"
#include "Monster.h"
#include "Skill.h"
#include "Equipment.h"
#include "Potion.h"
#include "RegenSkill.h"
#include "AttackSkill.h"

#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <iomanip>
#include <iostream>
/// aliases for maps storing pointer to game objects
typedef std::map<std::string, Hero*> mapHero;
typedef std::map<char, Monster*> mapMonster;
typedef std::map<char, Equipment*> mapEquipment;
typedef std::map<char, Potion*> mapPotion;
typedef std::map<std::string, Skill*> mapSkill;

/**
 * @brief class for configuration entities in game for other classes to use
 */
class GameConfig{
private:
    /// @brief file with configuration
    std::ifstream m_File;
    /// @brief map of pointer to all type of heroes in configuration
    mapHero m_Heroes;
    /// @brief map of pointer to all type of monsters in configuration
    mapMonster m_Monsters;
    /// @brief map of pointer to all type of equipments in configuration
    mapEquipment m_Equipments;
    /// @brief map of pointer to all type of potions in configuration
    mapPotion m_Potions;
    /// @brief map of pointer to all type of skills in configuration
    mapSkill m_Skills;

public:
    /**
     *@brief load configuration defined in file and then create each entity and store it in map
     * 
     * @param file -> file with configuration
     */
    GameConfig(const std::string& file);
    ///@brief delete all entities in maps
    ~GameConfig();
    //getters
    const mapHero& getHeroes() const;
    /// @brief read stats from string stream and store it in stats object
    void readStats(std::istringstream& iss, Stats& stats);
    /**
     * @brief read hero configuration from file and then create it and store it in map
     * add their name as key in map, so it can be used to get hero from map
     */
    void readHero();
    /**
     * @brief read monster configuration from file and then create it and store it in map
     * add their character as key in map, so it can be used to get monster from map
     */
    void readMonster();
    /**
     * @brief read equipment configuration from file and then create it and store it in map
     * add their character as key in map, so it can be used to get equipment from map
     */
    void readEquipment();
    /**
     * @brief read potion configuration from file and then create it and store it in map
     * add their character as key in map, so it can be used to get potion from map
     */
    void readPotion();
    /**
     * @brief read attack skill configuration from file and then create it and store it in map
     * aa their name as key in map, so it can be used to get skill from map
     */
    void readAttackSkill();
    /**
     * @brief read regeneration skill configuration from file and then create it and store it in map
     * add their name as key in map, so it can be used to get skill from map
     */
    void readRegenSkill();
    /**
     * @brief get hero from map by name
     * 
     * @param name -> name of hero
     * @return Hero* -> pointer to newly created hero
     */
    Hero* getHero(const std::string& name);
    /**
     * @brief get monster from map by character
     * 
     * @param tile -> character of monster
     * @return Monster* -> pointer to newly created monster
     */
    Monster* getMonster(char tile);
    /**
     * @brief get equipment from map by character
     * 
     * @param tile -> character of equipment
     * @return Equipment* -> pointer to newly created equipment
     */
    Equipment* getEquipment(char tile);
    /**
     * @brief get potion from map by character
     * 
     * @param tile -> character of potion
     * @return Potion* -> pointer to newly created potion
     */
    Potion* getPotion(char tile);
    /**
     * @brief get skill from map by name
     * 
     * @param name -> name of skill
     * @return Skill* -> pointer to newly created skill using clone method
     */
    Skill* getSkill(const std::string& name) const;
};