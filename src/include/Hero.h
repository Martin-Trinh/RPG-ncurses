#pragma once
/**
 * Project Graphic RPG Engine
 * @author trinhdin
 */
#include "Character.h"
#include "Item.h"
#include "Skill.h"
#include "LogMsg.h"
#include "Equipment.h"

#include <array>
#include <algorithm>
#include <fstream>
#include <sstream>

class Equipment;
/**
 * Represent hero in game
 */

class Hero: public Character{
private:
    /// max number of items in inventory
    static const size_t inventoryMax = 12;
    /// max number of skills
    static const size_t skillMax = 3;
    /// max number of equipment
    static const size_t equipmentMax = 6;
    /// current exp of hero
    int m_Exp = 0;
    /// amount of exp to level up
    int m_NextLevelExp = 10;
    /// current level of hero
    int m_Level = 1;

    /// inventory of hero
    std::vector<Item*> m_Inventory;
    /// skills of hero
    std::vector<Skill*> m_Skills;
    /// wearable equipment on hero
    std::array<Equipment*, equipmentMax> m_Equipments;

    /// game log messages window
    LogMsg * m_Log = nullptr;
    /// window to display hero stats
    WINDOW* m_StatsWin;
public:
    /**
     * @brief Construct a new Hero object
     * @param name -> name of hero
     * @param x -> x position
     * @param y -> y position
     * @param stats -> stats of hero
     */
    Hero(const std::string& name, int x, int y, const Stats &stats);
    ///@brief Destroy the Hero object free pointers in attributes
    ~Hero();
    /**
     * @brief Deep copy of other hero
     * @param hero -> hero to copy
     */
    Hero(const Hero& hero);
    /// @return log message window
    LogMsg* getLog() const;
    /// @return window to display hero stats
    WINDOW* getStatsWin()const;
    ///Set the Curr Attributes object of hero
    void setCurrAttributes(int currHP, int currMana, int exp, int nextLevelExp, int level);
    /**
     * @brief gain exp and level up if possible then increase stats
     * @param amount -> amount of exp to gain
     */
    void gainExp(int amount);
    /**
     * @brief move hero to new position if possible 
     * 
     * @param win -> ncurses window to check if new position is valid
     * @param margin -> margin from start from map
     * @param x -> x position
     * @param y -> y position
     * @return char -> character at new position
     */
    char move(WINDOW* win, int margin, int x, int y);
    /**
     * @brief add skill to hero
     * @param skill -> skill
     */
    void addSkill(Skill * skill);
    /**
     * @brief add item to inventory
     * @param item -> item to add
     * @return true -> if item was added
     * @return false -> if item was not added
     */
    bool addItem(Item* item);
    /**
     * @brief remove item from inventory
     * @param index -> index of item to remove
     */
    void removeItem(size_t index);
    /**
     * @brief use skill on monster
     * @param index -> index of skill to use
     * @param monster ->target monster
     */
    void useSkill(size_t index, Character* monster);
     /// @brief decrease cooldown of every skill
    void decreaseCooldown();
    /**
     * @brief use item in inventory
     * @param index -> index of item to use
     * @return true -> if item was used
     * @return false -> if item was not used
     */
    bool useItem(size_t index);
   /**
    * @brief unequip item from equipment slot
    * 
    * @param index -> index of item to unequip
    * @return true -> if item was unequipped
    * @return false -> equipment slot has no equipment
    */
    bool unequip(size_t index);
     /**
     * @brief equip item in inventory to equipment slot
     * 
     * @param item -> item equip
     * @param type -> type of equipment slot
     * @return true -> if item was equipped
     * @return false -> if item was not equipped
     */
    bool equip(Equipment* item, int type);
    /// add ncurses stats window to hero
    void addStatsWin(WINDOW* win);
    /// add ncurses game log window to hero
    void addLogWin(LogMsg* log);
    /**
     * @brief save hero attributes to file (exp, level, inventory, equipments)
     * 
     * @param filename -> name of file to save to
     */
    void save(const std::string&filename) const;
    /**
     * @brief open inventory window, enable inventory mode
     * @param win -> ncurses window to display inventory
     * @param control -> ncurses window to display control keys
     */
    void openInventory(WINDOW * win, WINDOW *control);
    /// @brief display all item in inventory
    void displayBackPack(WINDOW * win, WINDOW* detail, int selected, bool backpack)const;
    /// @brief display all equipment in
    void displayEquipment(WINDOW * win, WINDOW* detail, int selected, bool backpack)const;
    /// @brief display description of all item in inventory
    void displayDetail(WINDOW* win, const std::string& description)const;
    /// @brief display hero stats
    void displayStats() const;
    /// @brief display hero skills
    void displaySkill(WINDOW* win) const;
    /// @brief display control key for inventory mode
    void displayControls(WINDOW* win) const;
    
};