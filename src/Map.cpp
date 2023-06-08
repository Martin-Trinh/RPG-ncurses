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
    int hero = 0;
    for(size_t i = 0; i < m_Map.size(); i++){
        for(size_t j = 0; j < m_Map.at(i).size(); j++){
            char tile = m_Map.at(i).at(j);
            if(tile == '@'){
                hero++;
                m_Hero = new Hero{name, (int)(j + m_Margin), (int)(i + m_Margin), stats};
                m_Map.at(i).at(j) = '.';
            }else if(tile == '-' || tile == '+'){
                m_Gates.push_back(new Gate{tile, (int)(j + m_Margin), (int)(i + m_Margin), false});
                m_Map.at(i).at(j) = '.';
            }else if(m_CharItems.find(tile) != m_CharItems.end()){
                addItem(tile, j + m_Margin, i + m_Margin);
                m_Map.at(i).at(j) = '.';
            }else if(m_CharMonster.find(tile) != m_CharMonster.end()){
                addMonster(tile, j + m_Margin, i + m_Margin);
                m_Map.at(i).at(j) = '.';
            }else if (tile != '#' && tile != '.' && tile != ' '){
                throw std::string {"Uknown character on map: "} + tile; 
            }
        }
    }
    if(hero == 0){
        throw "Hero not found";
    }else if(hero > 2){
        throw "More than 1 hero ono map";
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
        //key
        case '?':
            m_Items.push_back(new Key{"key", tile, x, y, &m_Gates});
            break;
    default:
        break;
    }
}

int Map::getKey(WINDOW* win, WINDOW* control){
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
        m_Hero->openInventory(win, control);
        break;
    default:
        break;
    }
    if(m_CharItems.find(target) != m_CharItems.end()){
        size_t index = this->findItem(m_Hero->getPos());
        if(index != m_Items.size() && m_Hero->addItem(m_Items.at(index))){
            m_Items.erase(m_Items.begin() + index);
        }
    }else if(m_CharMonster.find(target) != m_CharMonster.end()){
        size_t index = this->findMonster(m_Hero->getPos());
       if(index != m_Monsters.size()){

       }
            // enter combat
    }
    return move;
}
size_t Map::findItem(Position pos) const{
    for(size_t i = 0; i < m_Items.size(); i++){
        if(m_Items.at(i)->getPos() == pos)
            return i;
    }
    return m_Items.size();
}
size_t Map::findMonster(Position pos)const{
    for(size_t i = 0; i < m_Monsters.size(); i++){
        if(m_Monsters.at(i)->getPos() == pos)
            return i;
    }
    return m_Monsters.size();
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
    //display gates
    for(size_t i = 0; i < m_Gates.size(); i++)
        m_Gates.at(i)->displayGate(win);
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
