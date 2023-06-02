#include "include/Map.h"

Map::Map(std::string mapFile){
    std::ifstream inFile {"./map/" + mapFile};
    if(!inFile){
        throw "Cannot open file";
    }
    std::string tmp;
    while(std::getline(inFile, tmp)){
        m_Map.push_back(tmp);
    }
    if(!inFile.eof()){
        throw "Read error";
    }
    inFile.close();
}

void Map::displayMap(WINDOW* win){
    int yMax, xMax;
    getmaxyx(win, yMax, xMax);
    if((int)m_Map.size() >= yMax)
        throw "Invalid map size";
    for(size_t i = 0; i < m_Map.size(); i++){
        if((int)m_Map.at(i).size() >= xMax)
            throw "Invalid map size";
        mvwprintw(win, i + 2, 2, "%s", m_Map.at(i).c_str());
    }
}