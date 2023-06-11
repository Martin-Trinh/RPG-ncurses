#include "include/GameConfig.h"

GameConfig::GameConfig(const std::string& file){
    m_File.open("./examples/" + file);
    try{
        if(!m_File.is_open())
        throw "Cannot open file " + file;

        std::string line;
        while(std::getline(m_File, line)){
            if(line.empty() || line[0] == '#') 
                continue;
            if(line == "<Hero>")
                readHero();
            else if(line == "<Monster>")
                readMonster();
            else if(line == "<Equipment>")
                readEquipment();
            else if(line == "<Potion>")
                readPotion();
            else if(line == "<AttackSkill>")
                readAttackSkill();
            else if(line == "<RegenSkill>")
                readRegenSkill();
            else
                throw "Unknown class " + line;
        }
        if(!m_File.eof() || m_File.bad())
            throw "Error reading file " + file;
    }catch(const std::string& e){
        for(auto& hero : m_Heroes)
            delete hero.second;
        for(auto& monster : m_Monsters)
            delete monster.second;
        for(auto& equipment : m_Equipments)
            delete equipment.second;
        for(auto& potion : m_Potions)
            delete potion.second;
        for(auto& skill : m_Skills)
            delete skill.second;    
        throw e;
    }
    m_File.close();
}
GameConfig::~GameConfig(){
    for(auto& hero : m_Heroes)
        delete hero.second;
    for(auto& monster : m_Monsters)
        delete monster.second;
    for(auto& equipment : m_Equipments)
        delete equipment.second;
    for(auto& potion : m_Potions)
        delete potion.second;
    for(auto& skill : m_Skills)
        delete skill.second;
}
const mapHero& GameConfig::getHeroes() const{return m_Heroes;}
void GameConfig::readStats(std::istringstream& iss, Stats& stats){
    int hp, mana, strength, magic, armor, resistance;
    iss >> hp >> mana >> strength >> magic >> armor >> resistance;
    stats = Stats{hp, mana, strength, magic, armor, resistance};
}
void GameConfig::readHero(){
    std::vector<std::string> skills;
    std::string name, line;
    Stats stats;
    while(std::getline(m_File, line) && line != "</Hero>"){
        if(line[0] == '#' || line.empty())
            continue;
        std::istringstream iss(line);
        std::getline(iss, line, '=');
        if(line == "name"){
            std::getline(iss, name);
        }else if(line == "stats"){
            readStats(iss, stats);
        }else if(line == "skills"){
            while(std::getline(iss, line, ','))
                skills.push_back(line);
        }else{
            throw "Read hero failed " + line;
        }
    }
    if(m_Heroes.find(name) == m_Heroes.end())
        m_Heroes[name] = new Hero(name, 0, 0, stats);
    else
        throw "Duplicate hero name " + name;
    // add skills to hero
    for(auto& skill : skills)
        m_Heroes[name]->addSkill(getSkill(skill));
}
void GameConfig::readMonster(){
    std::string name, skillName, line;
    char character;
    int expWorth;
    Stats stats; 
    while(std::getline(m_File, line) && line != "</Monster>"){
        if(line[0] == '#' || line.empty())
            continue;
        std::istringstream iss(line);
        std::getline(iss, line, '=');
        if(line == "name"){
            std::getline(iss, name);
        }else if(line == "stats"){
            readStats(iss, stats);
        }else if(line == "skill"){
            std::getline(iss, skillName);
        }else if(line == "expWorth"){
            iss >> expWorth;
        }else if(line == "char"){
            std::getline(iss, line);
            character = line[0];
        }else{
            throw "Read monster failed " + line;
        }
    }
    if (m_Monsters.find(character) == m_Monsters.end()){
        m_Monsters[character] = new Monster(name, character,0, 0, stats,getSkill(skillName), expWorth);
    }else{
        throw "Duplicate monster character " + character;
    }
}
void GameConfig::readEquipment(){
    std::string name, line;
    char character;
    Stats stats;
    while(std::getline(m_File, line) && line != "</Equipment>" ){
        if(line[0] == '#' || line.empty())
            continue;
        std::istringstream iss(line);
        std::getline(iss, line, '=');
        if(line == "name"){
            std::getline(iss, name);
        }else if(line == "char"){
            std::getline(iss, line);
            character = line[0];
        }else if(line == "stats"){
            readStats(iss, stats);
        }else{
            throw "Read equipment failed " + line;
        }
    }
    if(m_Equipments.find(character) == m_Equipments.end())
        m_Equipments[character] = new Equipment(name,character, 0, 0, stats);
    else
        throw "Duplicate equipment character " + character;
}
void GameConfig::readPotion(){
    std::string name, line;
    char character;
    int hp, mana, exp;
    while(std::getline(m_File, line) && line != "</Potion>"){
        if(line[0] == '#' || line.empty())
            continue;
       
        std::istringstream iss(line);
        std::getline(iss, line, '=');
        if(line == "name"){
            std::getline(iss, name);
        }else if(line == "char"){
            std::getline(iss, line);
            character = line[0];
        }else if(line == "hp"){
            iss >> hp;
        }else if(line == "mana"){
            iss >> mana;
        }else if(line == "exp"){
            iss >> exp;
        }else{
            throw "Read potion failed";
        }
    }
    if(m_Potions.find(character) == m_Potions.end())
        m_Potions[character] = new Potion(name, character, 0, 0, hp, mana, exp);
    else
        throw "Duplicate potion character " + character;
}
void GameConfig::readAttackSkill(){
    std::string name, line;
    int cooldown, cost, damage;
    bool magical;
    Skill::Type type = Skill::Type::ACTIVE;
    while(std::getline(m_File, line) && line != "</AttackSkill>"){
        if(line[0] == '#' || line.empty())
            continue;
       
        std::istringstream iss(line);
        std::getline(iss, line, '=');
        if(line == "name"){
            std::getline(iss, name);
        }else if(line == "cooldown"){
            iss >> cooldown;
        }else if(line == "cost"){
            iss >> cost;
        }else if(line == "damage"){
            iss >> damage;
        }else if(line == "magical"){
            iss >> std::boolalpha >> magical;
        }else if(line == "type"){
            std::getline(iss, line);
            if(line == "active")
                type = Skill::Type::ACTIVE;
            else if(line == "passive")
                type = Skill::Type::PASSIVE;
            else
                throw "Skill type unknown " + line;
        }else{

            throw "Read attack skill failed " + line;
        }
    }
    if(m_Skills.find(name) == m_Skills.end())
        m_Skills[name] = new AttackSkill(name, cooldown, cost, type, damage, magical);
    else
        throw "Duplicate name for skill " + name;
}
void GameConfig::readRegenSkill(){
    std::string name, line;
    int cooldown, cost, amount;
    bool hp;
    Skill::Type type = Skill::Type::ACTIVE;
    while(std::getline(m_File, line) && line != "</RegenSkill>"){
        if(line[0] == '#' || line.empty())
            continue;
       
        std::istringstream iss(line);
        std::getline(iss, line, '=');
        if(line == "name"){
            std::getline(iss, name);
        }else if(line == "cooldown"){
            iss >> cooldown;
        }else if(line == "cost"){
            iss >> cost;
        }else if(line == "amount"){
            iss >> amount;
        }else if(line == "hp"){
            iss >> std::boolalpha >> hp;
        }else if(line == "type"){
            std::getline(iss, line);
            if(line == "active")
                type = Skill::Type::ACTIVE;
            else if(line == "passive")
                type = Skill::Type::PASSIVE;
            else
                throw "Skill type unknown " + line;
        }else{
            throw "Read regen skill failed " + line;
        }
    }
    if(m_Skills.find(name) == m_Skills.end())
        m_Skills[name] = new RegenSkill(name, cooldown, cost, type,amount, hp);
    else
        throw "Duplicate name for skill" + name;
}
Hero* GameConfig::getHero(const std::string& name){
    auto it = m_Heroes.find(name);
    if(it != m_Heroes.end())
        return new Hero(*(it->second));
    return nullptr;
}
Monster* GameConfig::getMonster(char tile){
    auto it = m_Monsters.find(tile);
    if(it != m_Monsters.end())
        return new Monster(*(it->second));
    return nullptr;
}
Equipment* GameConfig::getEquipment(char tile){
    auto it = m_Equipments.find(tile);
    if(it != m_Equipments.end())
        return new Equipment(*(it->second));
    return nullptr;
}
Potion* GameConfig::getPotion(char tile){
    auto it = m_Potions.find(tile);
    if(it != m_Potions.end())
        return new Potion(*(it->second));
    return nullptr;
}
Skill* GameConfig::getSkill(const std::string& name) const{
    auto it = m_Skills.find(name);
    if(it == m_Skills.end())
        throw "Skill not found " + name;
    else
        return it->second->clone();
}
