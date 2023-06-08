#pragma once

#include <ncurses.h>
#include <string>
#include <vector>

typedef std::vector<std::string> vecStr;

class LogMsg{
private:
    WINDOW * m_Win;
    vecStr m_Messages;
    size_t m_MaxMsg;
public:
    LogMsg(int xSize, int ySize, int xStart, int yStart, size_t maxMsg);
    ~LogMsg();
    void displayMsg(const std::string& newMsg);
};