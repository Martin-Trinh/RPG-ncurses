#include "include/Map.h"


Map::Map(const std::string& mapFile, GameConfig* config)
:m_GameConfig{config}{
    std::ifstream inFile {"./examples/maps/" + mapFile + ".map"};
    if(!inFile){
        throw "Cannot open file " + mapFile;
    }
    std::string tmp;
    // load map int o vector of string
    while(std::getline(inFile, tmp)){
        m_Map.push_back(tmp);
    }
    if(!inFile.eof()){
        throw "Read error";
    }
    inFile.close();
}

Map::~Map(){
    delete m_Hero;
    for(size_t i = 0; i < m_Monsters.size(); i++)
        delete m_Monsters.at(i);
    for(size_t i = 0; i < m_Gates.size(); i++)
        delete m_Gates.at(i);
    for(size_t i = 0; i < m_Items.size(); i++)
        delete m_Items.at(i);
}
Hero* Map::getHero()const {return m_Hero;}
bool Map::heroWon() const{return m_Winning;}

void Map::loadEntity(const std::string& heroName, bool newGame){
    int heroCnt = 0;

    Equipment* equip;
    Potion* potion;
    Monster* monster;
    for(size_t i = 0; i < m_Map.size(); i++){
        for(size_t j = 0; j < m_Map.at(i).size(); j++){
            char tile = m_Map.at(i).at(j);
            if(tile == '@'){
                heroCnt++;
                if(newGame)
                    m_Hero = m_GameConfig->getHero(heroName);
                m_Hero->setPosition(j,i);
                m_Map.at(i).at(j) = '.';
            }else if(tile == '?'){
                m_Items.push_back(new Key{"Key", tile, (int)j, (int)i, &m_Gates});
                m_Map.at(i).at(j) = '.';
            }else if(tile == '-' || tile == '+'){
                if(tile == '+')
                    m_Gates.push_back(new Gate{tile, (int)j, (int)i, true});
                else
                    m_Gates.push_back(new Gate{tile, (int)j, (int)i, false});
                m_Map.at(i).at(j) = '.';
            }else if((equip = m_GameConfig->getEquipment(tile))){
                m_Items.push_back(equip);
                equip->setPosition(j, i);
                m_Map.at(i).at(j) = '.';
            }else if((potion = m_GameConfig->getPotion(tile))){
                m_Items.push_back(potion);
                potion->setPosition(j, i);
                m_Map.at(i).at(j) = '.';
            }else if((monster = m_GameConfig->getMonster(tile))){
                m_Monsters.push_back(monster);
                monster->setPosition(j, i);
                m_Map.at(i).at(j) = '.';
            }else if (tile != '#' && tile != '.' && tile != ' '){
                throw std::string {"Uknown character on map: "} + tile; 
            }
        }
    }
    if(heroCnt == 0){
        throw "Hero not found";
    }else if(heroCnt > 2){
        throw "More than 1 hero on map";
    }
    
}
// save map to file
void Map::save(const std::string& mapFile){
    std::ofstream outFile {"./examples/maps/" + mapFile + ".map"};
    if(!outFile.is_open())
        throw "Cannot open file " + mapFile;

    for(const auto&monster: m_Monsters)
        m_Map.at(monster->getPos().m_Y).at(monster->getPos().m_X) = monster->getCharacter();
    for(const auto&item: m_Items)
        m_Map.at(item->getPos().m_Y).at(item->getPos().m_X) = item->getCharacter();
    for(const auto&gate: m_Gates)
        m_Map.at(gate->getPos().m_Y).at(gate->getPos().m_X) = gate->getCharacter();
    m_Map.at(m_Hero->getPos().m_Y).at(m_Hero->getPos().m_X) = m_Hero->getCharacter();

    for(const auto& line: m_Map){
        outFile << line << std::endl;
    }

    if(outFile.bad())
        throw "Write error";
    outFile.close();
}
void Map::loadHeroFromFile(const std::string& filename,GameConfig* config){
    std::ifstream inFile {"./examples/hero/" + filename + ".hero"};
    if(!inFile)
        throw "Cannot open file " + filename;
    size_t invenSize = 0;
    //Hero attributes
    std::string name;
    int currHP, currMana, exp, nextLevelExp, level;

    std::string line;
    while(std::getline(inFile, line)){
        if(line.empty()) 
            continue; 
        std::istringstream iss(line);
        std::getline(iss, line, '=');
        if(line == "name"){
            std::getline(iss, name);
        }else if(line == "levelStats"){
            iss >> exp >> nextLevelExp >> level;
        }else if(line == "currStats"){
            iss >> currHP >> currMana;
            m_Hero = m_GameConfig->getHero(name);
            m_Hero->setCurrAttributes(currHP, currMana, exp, nextLevelExp, level);
        }else if(line == "inventory"){
            char c;
            Item * item;
            while (iss >> c){
                if(c == '?'){
                    m_Hero->addItem(new Key{"Key", '?', 0, 0, &m_Gates});
                    invenSize++;
                }
                else if((item = config->getEquipment(c))){
                    m_Hero->addItem(item);
                    invenSize++;
                }
                else if((item = config->getPotion(c))){
                    m_Hero->addItem(item);
                    invenSize++;
                }
                else
                    throw "Unknown item in inventory: " + c;
            }
        }else if(line == "equipment"){
            char c;
            Equipment* equip;
            while (iss >> c){
                if((equip = config->getEquipment(c))){
                    m_Hero->addItem(equip);
                    equip->use(m_Hero, line);
                    m_Hero->removeItem(invenSize);
                }
                else
                    throw "Unknown item in equipment: " + c;
            }
        }else{
            throw "Unknown attribute: " + line;
        }
    }
    if(!inFile.eof())
        throw "Read error";
    inFile.close();
}
int Map::getKey(WINDOW* win, WINDOW* control){
    
    int move = wgetch(win);
    switch (move)
    {
    case KEY_UP:
        m_Hero->move(win, m_Margin,m_Hero->getPos().m_X, m_Hero->getPos().m_Y - 1);
        break;
    case KEY_DOWN:
        m_Hero->move(win, m_Margin,m_Hero->getPos().m_X, m_Hero->getPos().m_Y + 1);
        break;
    case KEY_RIGHT:
        m_Hero->move(win, m_Margin,m_Hero->getPos().m_X + 1, m_Hero->getPos().m_Y);
        break;
    case KEY_LEFT:
        m_Hero->move(win, m_Margin,m_Hero->getPos().m_X - 1, m_Hero->getPos().m_Y);
        break;
    case 'i':
        m_Hero->openInventory(win, control);
        break;
    default:
        break;
    }
    auto itItem = std::find_if(m_Items.begin(), m_Items.end(), [this](Item* item){
        return item->getPos() == m_Hero->getPos();
    });
    if(itItem != m_Items.end()){
        if( m_Hero->addItem(*itItem)){
            m_Hero->getLog()->displayMsg("You picked up " + (*itItem)->getName());
            m_Items.erase(itItem);
        }else{
            m_Hero->getLog()->displayMsg("Inventory is full");
        }
    }
    auto itMonster = std::find_if(m_Monsters.begin(), m_Monsters.end(), [this](Monster* monster){
        return monster->getPos() == m_Hero->getPos();
    });
    if(itMonster != m_Monsters.end()){
        // enter combat
        this->displayControl(control);
        if(!this->combat(win,m_Hero, *itMonster)){
            // hero loses
            move = KEY_END;
        }else{
            if(m_Monsters.empty()){
                // hero wins
                move = KEY_END;
                m_Winning = true;
            }
        }
    }
    return move;
}
void Map::displayControl(WINDOW* win) const{
    int line = 0;
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, line++, 1, "Combat keys");
    line++;
    mvwprintw(win, line++, 1, "1.skill:     <q>");
    mvwprintw(win, line++, 1, "2.skill:     <w>");
    mvwprintw(win, line++, 1, "3.skill:     <e>");
    wrefresh(win);
}
bool Map::combat(WINDOW* win, Hero* hero, Monster* monster){
    LogMsg * log = hero->getLog();
    WINDOW *heroSkill = newwin(16, 30, 1, 83);
    WINDOW *enemyStats = newwin(11, 20, 12, 63);
    WINDOW* enemySkill = newwin(6, 30, 17, 83);

    bool playerWin = true;
    std::string outMsg;
    size_t turn = 0;
    while(++turn){
        monster->displaySkills(enemySkill);
        hero->displaySkill(heroSkill);
        monster->displayStats(enemyStats);
        int key = wgetch(win);
        switch (key)
        {
        case 'q':
            hero->useSkill(0, monster);
            break;
        case 'w':
            hero->useSkill(1, monster);
            break;
        case 'e':
            hero->useSkill(2, monster);
            break;
        default:
            continue;
            break;
        }
        hero->decreaseCooldown();
        if(monster->getCurrHP() <= 0){
            log->displayMsg("Hero killed " + monster->getName());
            hero->gainExp(monster->getExp());
            auto found = std::find_if(m_Monsters.begin(), m_Monsters.end(), [this](Monster* monster){
                return monster->getPos() == m_Hero->getPos();
            });
            if(found == m_Monsters.end())
                throw "Cannot find dead monster";
            delete *found;
            m_Monsters.erase(found);
            break;
        }
        if(monster->useSkill(hero, outMsg)){
            log->displayMsg(outMsg);
            m_Hero->displayStats();
        }
        monster->decreaseCooldown();
        if(hero->getCurrHP() <= 0){
            log->displayMsg("Hero was killed by " + monster->getName());
            playerWin = false;
            break;
            napms(1000);
        }
        if(turn > 50){
            throw "Max turn exceeded";
            break;
        }
    }
    werase(enemyStats);
    wrefresh(enemyStats);
    delwin(enemyStats);
    werase(enemySkill);
    wrefresh(enemySkill);
    delwin(enemySkill);
    werase(heroSkill);
    wrefresh(heroSkill);
    delwin(heroSkill);
    return playerWin;
}
void Map::display(WINDOW* win){
    int yMax, xMax;
    getmaxyx(win, yMax, xMax);
    if((int)m_Map.size() + m_Margin >= yMax)
        throw "Invalid map size";
    
    // display map
    for(size_t i = 0; i < m_Map.size(); i++){
        if((int)m_Map.at(i).size() + m_Margin >= xMax)
            throw "Invalid map size";
        mvwprintw(win, i + m_Margin, m_Margin, "%s", m_Map.at(i).c_str());
    }
    //display gates
    for(size_t i = 0; i < m_Gates.size(); i++)
        m_Gates.at(i)->displayEntity(win,m_Margin);
    // display items
    for(size_t i = 0; i < m_Items.size(); i++)
        m_Items.at(i)->displayEntity(win,m_Margin);
    // display monsters
    for(size_t i = 0; i< m_Monsters.size(); i++)
        m_Monsters.at(i)->displayEntity(win,m_Margin);
    // display hero
    m_Hero->displayEntity(win, m_Margin);
    wrefresh(win);
}
