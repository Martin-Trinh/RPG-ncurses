#include "include/LogMsg.h"

LogMsg::LogMsg(int xSize, int ySize, int xStart, int yStart, size_t maxMsg){
    m_Win = newwin(ySize, xSize, yStart, xStart);
    // scrollok(m_Win, true);
    m_MaxMsg = maxMsg;
}
LogMsg::~LogMsg(){
    delwin(m_Win);
}
void LogMsg::displayMsg(const std::string& newMsg){
    werase(m_Win);
    box(m_Win, 0, 0);
    mvwprintw(m_Win, 0, 1, "Game messages");
    int width = getmaxx(m_Win);
    if(m_Messages.size() == m_MaxMsg){
        std::swap(m_Messages.at(1), m_Messages.at(2));
        std::swap(m_Messages.at(0), m_Messages.at(2));
        m_Messages.at(2) = newMsg;
    }else{
        m_Messages.push_back(newMsg);
    }
    int row = 1;
    for(const auto& msg : m_Messages){
        int col = 1; 
        for(char i: msg){
            if(col >= width){
                col = 1;
                row++;
            }
            mvwaddch(m_Win, row, col, i);
            col++;
        }
        row++;
    }
    wrefresh(m_Win);
}