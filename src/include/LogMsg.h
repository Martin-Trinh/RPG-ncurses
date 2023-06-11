#pragma once
/**
 * Project Graphic RPG Engine
 * @author trinhdin
 */
#include <ncurses.h>
#include <string>
#include <vector>

typedef std::vector<std::string> vecStr;
/**
 * @brief class for displaying messages on game log
 * 
 */
class LogMsg{
private:
    /// @brief window for displaying messages
    WINDOW * m_Win;
    /// @brief vector of messages
    vecStr m_Messages;
    /// @brief max number of messages
    size_t m_MaxMsg;
public:
    /// @brief Construct a new LogMsg object
    LogMsg(int xSize, int ySize, int xStart, int yStart, size_t maxMsg);
    /// @brief ncurse window
    ~LogMsg();
    /**
     * @brief add new message to vector of messages and then display it to the console
     * 
     * @param newMsg -> new message to display
     */
    void displayMsg(const std::string& newMsg);
};