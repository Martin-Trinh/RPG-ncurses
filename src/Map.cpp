#include "include/Map.h"

Map::Map(const std::string& mapFile){
    std::ifstream inFile {"./map/" + mapFile};
    if(!inFile){
        throw "Cannot open file";
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
void Map::loadEntity(const std::string &name,const Stats& stats){
    bool heroFound = true;
    for(size_t i = 0; i < m_Map.size(); i++){
        for(size_t j = 0; j < m_Map.at(i).size(); j++){
            char tile = m_Map.at(i).at(j);
            if(tile == '@'){
                heroFound = true;
                m_Hero = new Hero{name,(int) (j + m_Margin), (int)(i + m_Margin), stats};
                m_Map.at(i).at(j) = '.';
            }else if(tile == '?' || tile == '+'){

            }else if(m_CharItems.find(tile) != m_CharItems.end()){
                addItem(tile,j + m_Margin, i + m_Margin);
                m_Map.at(i).at(j) = '.';
            }else if(m_CharMonster.find(tile) != m_CharMonster.end()){
                addMonster(tile,j + m_Margin, i + m_Margin);
                m_Map.at(i).at(j) = '.';
            }else if (tile != '#' && tile != '.' && tile != ' '){
                throw std::string {"Uknown character on map: "} + tile; 
            }
        }
    }
    if(!heroFound){
        throw "Hero not found";
    }
}
void Map::addMonster(char tile, int x, int y){
    static Stats monsterStat {20, 10, 10, 5, 3, 2};
    switch (tile)
    {
    case 'S':
        m_Monsters.push_back(new Monster{"Slime", x, y, monsterStat, nullptr, 5, tile});
        break;
    case 'X':
        m_Monsters.push_back(new Monster{"Spider", x, y, monsterStat, nullptr, 6, tile});
    default:
        break;
    }
}
void Map::addItem(char tile, int x, int y){
    static Stats helmetStat {100, 100, 10, 5, 3, 2};
    static Stats plateStat  {100, 100, 10, 5, 3, 2};
    static Stats axeStat    {100, 100, 10, 5, 3, 2};
    static Stats bootStat   {100, 100, 10, 5, 3, 2};
    static Stats ringStat   {100, 100, 10, 5, 3, 2};
    switch (tile)
    {
        case '^':
            m_Items.push_back(new Equipment{"helmet", tile, x, y, helmetStat});
            break;
        case 'a':
            m_Items.push_back(new Equipment{"axe", tile, x, y, axeStat});
            break;
        case 'b':
            m_Items.push_back(new Equipment{"boot", tile, x, y, bootStat});
            break;
        case 'p':
            m_Items.push_back(new Equipment{"plate", tile, x, y, plateStat});
            break;
        case 'o':
            m_Items.push_back(new Equipment{"ring", tile, x, y, ringStat});
            break;
        // potion
        case 'h':
            m_Items.push_back(new Potion{"health", tile, x, y, 10, 0, 0});
            break;
        case 'm':
            m_Items.push_back(new Potion{"mana", tile, x, y, 0, 10, 0});
            break;
        case 'e':
            m_Items.push_back(new Potion{"exp", tile, x, y, 0, 0, 10});
            break;
    default:
        break;
    }
}
void Map::removeItem(){
}
void Map::removeMonster(){
}

int Map::getKey(WINDOW* win, WINDOW* control, WINDOW* log){
    int move = wgetch(win);
    char target;
    switch (move)
    {
    case KEY_UP:
        target = m_Hero->move(win, m_Hero->getPos().m_X, m_Hero->getPos().m_Y - 1);
        break;
    case KEY_DOWN:
        target = m_Hero->move(win, m_Hero->getPos().m_X, m_Hero->getPos().m_Y + 1);
        break;
    case KEY_RIGHT:
        target = m_Hero->move(win, m_Hero->getPos().m_X + 1, m_Hero->getPos().m_Y);
        break;
    case KEY_LEFT:
        target = m_Hero->move(win, m_Hero->getPos().m_X - 1, m_Hero->getPos().m_Y);
        break;
    case 'i':
        m_Hero->openInventory(win, control, log);
        break;
    // case '1':
    // case '2':
    // case '3':
    //     this->useSkill(0, findMon)
    default:
        break;
    }
    if(m_CharItems.find(target) != m_CharItems.end()){
        Item* item = this->findItem(m_Hero->getPos());
        if(item){
            m_Hero->addItem(item);
            this->removeItem();
        }
    }else if(m_CharMonster.find(target) != m_CharMonster.end()){
        Monster * monster = this->findMonster(m_Hero->getPos());
       if(monster)
            this->removeMonster();
            // enter combat
    }
    return move;
}
Item* Map::findItem(Position pos)const{
    for(size_t i = 0; i < m_Items.size(); i++){
        if(m_Items.at(i)->getPos() == pos)
            return m_Items.at(i);
    }
    return NULL;
}
Monster* Map::findMonster(Position pos)const{
    for(size_t i = 0; i < m_Monsters.size(); i++){
        if(m_Monsters.at(i)->getPos() == pos)
            return m_Monsters.at(i);
    }
    return NULL;
}

Hero* Map::getHero()const { return m_Hero;}
void Map::display(WINDOW* win){
    int yMax, xMax;
    getmaxyx(win, yMax, xMax);
    if((int)m_Map.size() >= yMax)
        throw "Invalid map size";
    // display map
    for(size_t i = 0; i < m_Map.size(); i++){
        if((int)m_Map.at(i).size() >= xMax)
            throw "Invalid map size";
        mvwprintw(win, i + m_Margin, m_Margin, "%s", m_Map.at(i).c_str());
    }
    // display items
    for(size_t i = 0; i < m_Items.size(); i++)
        m_Items.at(i)->displayItem(win);
    // display monsters
    for(size_t i = 0; i< m_Monsters.size(); i++)
        m_Monsters.at(i)->displayMonster(win);
    // display hero
    m_Hero->displayHero(win);
    wrefresh(win);
}