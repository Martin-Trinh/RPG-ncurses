#pragma once

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


typedef std::map<std::string, Hero*> mapHero;
typedef std::map<char, Monster*> mapMonster;
typedef std::map<char, Equipment*> mapEquipment;
typedef std::map<char, Potion*> mapPotion;
typedef std::map<std::string, Skill*> mapSkill;

class GameConfig{
private:
    std::ifstream m_File;

    mapHero m_Heroes;
    mapMonster m_Monsters;
    mapEquipment m_Equipments;
    mapPotion m_Potions;
    mapSkill m_Skills;

public:
    GameConfig(const std::string& file);
    ~GameConfig();
    //getters
    const mapHero& getHeroes() const;
    void readStats(std::istringstream& iss, Stats& stats);
    void readHero();

    void readMonster();
    void readEquipment();
    void readPotion();
    void readAttackSkill();
    void readRegenSkill();

    Hero* getHero(const std::string& name);
    Monster* getMonster(char tile);
    Equipment* getEquipment(char tile);
    Potion* getPotion(char tile);
    Skill* getSkill(const std::string& name) const;
};