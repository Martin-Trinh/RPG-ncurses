#include "include/Game.h"

Game::Game(){
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    try{
        // load from config file
        m_GameConfig = new GameConfig(m_ConfigFile);
    }catch(const std::string& e){
        clear();
        mvprintw(0, 0, "%s",e.c_str());
        refresh();
        getch();
    }
}
Game::~Game(){
    delete m_GameConfig;
    endwin();
}
void Game::displayGame(){
    clear();
    refresh();
    // init main window
    int xSize = 62, ySize = 25;
    int startX = 1, startY = 1;
    WINDOW *win = newwin(ySize, xSize, startX, startY);
    keypad(win, true);
    box(win, 0, 0);
    mvwprintw(win, 0, 1, "Game screen");
    LogMsg * log = new LogMsg( xSize, 8, startX, ySize + 1, 6);
    WINDOW *heroStats = newwin(11, 20, startY, xSize + 1);
    WINDOW *control = newwin(9, 25, startY + 22, xSize + 1);
    int move;
    m_Map->getHero()->addLogWin(log);
    m_Map->getHero()->addStatsWin(heroStats);
    
    log->displayMsg("Welcome to the game!");
    m_Map->getHero()->displayStats();
    do{
        box(win, 0, 0);
        mvwprintw(win, 0, 1, "Game screen");
        m_Map->display(win);
        this->displayControl(control);
        move = m_Map->getKey(win, control);
        switch (move)
        {
        case KEY_BACKSPACE:
            if(this->warning()){
                clear();
                refresh();
                m_Exit = true;
            }
            break;
        case 's':
            clear();
            refresh();
            this->saveGame();
            m_Exit = true;
            break;
        case KEY_END:
            if(m_Map->heroWon()){
                clear();
                refresh();
                this->msgPopUp("You won!");
            }else{
                clear();
                refresh();
                this->msgPopUp("You lost!");
            }
            break;
        default:
            break;
        }
    }while(!m_Exit);
    delete log;
    delete m_Map;
    m_Map = nullptr;
    delwin(win);
    delwin(heroStats);
    delwin(control);
}
void Game::loadGame(){
    vecStr description = {"Load game", "Filename", "<Press enter to load>"};
    std::string filename;
    this->getInput(description, filename);
    try{
        m_Map = new Map(filename, m_GameConfig);
        m_Map->loadHeroFromFile(filename, m_GameConfig);
        m_Map->loadEntity(filename, false);
    }catch(const std::string& e){
        clear();
        mvprintw(1, 1, "%s", e.c_str());
        refresh();
        getch();
    }catch(const char* e){
        clear();
        mvprintw(1, 1, "%s", e);
        refresh();
        getch();
    }
}
void Game::saveGame(){
    vecStr description = {"Save game", "Filename", "<Press enter to save>"};
    std::string filename;
    this->getInput(description, filename);
    try{
        m_Map->save(filename);
        m_Map->getHero()->save(filename);
    }catch(const std::string& e){
        clear();
        mvprintw(1, 1, "%s", e.c_str());
        refresh();
        getch();
    }
}
void Game::getInput(const vecStr& description, std::string& input){
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    int xSize = 30, ySize = 8;
    WINDOW *win = newwin(ySize, xSize, yMax / 2 - ySize / 2, xMax / 2 - xSize / 2);
    keypad(win, true);
    box(win, 0, 0);
    mvwprintw(win, 0, 8, "%s", description.at(0).c_str());
    mvwprintw(win, 2, 1, "%s: %s",description.at(1).c_str() ,input.c_str());
    mvwprintw(win, 6, 5, "%s", description.at(2).c_str());
    while(1){
        int ch = wgetch(win);
        if((isdigit(ch) || isalpha(ch)) && input.size() < 18)
            input += ch;

        if(ch == KEY_BACKSPACE && input.size() > 0){
            input.pop_back();
            mvwprintw(win, 2, 1, "%s:                   ", description.at(1).c_str());
            mvwprintw(win, 2, 1, "%s: %s",description.at(1).c_str() ,input.c_str());
        }
        if(ch == 10){
            if(input == m_DefaultMap)
                mvwprintw(win, 4, 1, "Invalid filename!");
            if(input.empty())
                throw "Empty input!";
            break;
        }
        wattron(win, A_STANDOUT);
        mvwprintw(win, 2, 1, "%s: %s",description.at(1).c_str() ,input.c_str());
        wrefresh(win);
    }
    werase(win);
    wrefresh(win);
    delwin(win);
}
void Game::displayControl(WINDOW* win) const{
    werase(win);
    box(win, 0, 0);
    int line = 0;
    mvwprintw(win, line++, 1, "Control keys");
    line++;
    mvwprintw(win, line++, 1, "Movement:  <arrow keys>");
    mvwprintw(win, line++, 1, "Inventory: <i>");
    mvwprintw(win, line++, 1, "Save:      <s>");
    mvwprintw(win, line++, 1, "Quit:      <backspace>");
    wrefresh(win);
}
bool Game::warning()const{
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    int xSize = 30, ySize = 6;
    WINDOW *win = newwin(ySize, xSize, yMax / 2 - ySize / 2, xMax / 2 - xSize / 2);
    box(win, 0, 0);
    bool choice = false;
    keypad(win, true);
    std::string msg = "Do you want to quit?";
    std::string msg1 = "Yes, I want to quit";
    std::string msg2 = "No, I want to stay";

    while (1)
    {
        mvwprintw(win, 1, (xSize - msg.size()) / 2, "%s", msg.c_str());

        if (choice)
            wattron(win, A_STANDOUT);
        mvwprintw(win, 3, (xSize - msg1.size()) / 2, "%s", msg1.c_str());
        wattroff(win, A_STANDOUT);

        if (!choice)
            wattron(win, A_STANDOUT);
        mvwprintw(win, 4, (xSize - msg2.size()) / 2, "%s", msg2.c_str());
        wattroff(win, A_STANDOUT);

        int key = wgetch(win);
        if (key == KEY_UP || key == KEY_DOWN)
            choice ? choice = false : choice = true;

        if (key == 10)
        {
            wclear(win);
            wrefresh(win);
            delwin(win);
            return choice;
        }
    }
}
void Game::displayMenu(){
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    int ySize = 10, xSize = 20;
    WINDOW *win = newwin(10, 20, yMax / 2 - ySize / 2, xMax / 2 - xSize / 2);
    keypad(win, true);
    std::vector<std::string> Options = {"New Game", "Load Game", "Exit"};

    int selected = 0;
    while (!m_Exit)
    {
        box(win, 0, 0);
        int winXMax = getmaxx(win);
        int space = 1;
        for (int i = 0; i < (int)Options.size(); i++, space += 1)
        {
            if (i == selected)
                wattron(win, A_STANDOUT);
            mvwprintw(win, i + space, winXMax / 2 - Options.at(i).size() / 2, "%s", Options.at(i).c_str());
            wattroff(win, A_STANDOUT);
            wrefresh(win);
        }
        int key = wgetch(win);
        switch (key)
        {
        case KEY_UP:
            if (--selected < 0)
                selected = Options.size() - 1;
            break;
        case KEY_DOWN:
            if (++selected == (int)Options.size())
                selected = 0;
            break;
        case 10:
            if (Options.at(selected) == "New Game")
                this->createHero();
            if (Options.at(selected) == "Load Game"){
                this->loadGame();
                this->displayGame();
            }
            if (Options.at(selected) == "Exit")
                m_Exit = true;
            break;
        default:
            break;
        }
    }
    delwin(win);
}
void Game::createHero(){
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    int ySize = 13, xSize = 25;
    WINDOW *win = newwin(ySize, xSize, yMax / 2 - 5, xMax / 2 + 10);

    mapHero heroes = m_GameConfig->getHeroes();
    auto it = heroes.begin();
    bool create = true, selected = true;
    int line;
    while (create)
    {
        line = 1;
        werase(win);
        box(win, 0, 0);
        // hero type selection
        if (selected)
            wattron(win, A_STANDOUT);
        mvwprintw(win, line++, 1, "Hero type: < %s >", it->first.c_str());
        wattroff(win, A_STANDOUT);
        line++;
        // display stats each hero
        mvwprintw(win, line++, 1, "HP: %d", it->second->getStats().getHP());
        mvwprintw(win, line++, 1, "Mana: %d", it->second->getStats().getMana());
        mvwprintw(win, line++, 1, "Strength: %d", it->second->getStats().getStrength());
        mvwprintw(win, line++, 1, "Magic: %d", it->second->getStats().getMagic());
        mvwprintw(win, line++, 1, "Armor: %d", it->second->getStats().getArmor());
        mvwprintw(win, line++, 1, "Resistance: %d", it->second->getStats().getResistance());
        // draw a line
        wmove(win, line++ , 1);
        whline(win, ACS_HLINE, 23);
        // play button
        if (!selected)
            wattron(win, A_STANDOUT);
        mvwprintw(win, line++, getmaxx(win)/2 - 2, "Play");
        wattroff(win, A_STANDOUT);

        keypad(win, true);
        int key = wgetch(win);
        switch (key)
        {
        case KEY_UP:
        case KEY_DOWN:
            selected ? selected = false : selected = true;
            break;
        case KEY_RIGHT:
            if (selected && ++it == heroes.end())
                it = heroes.begin();
            break;
        case KEY_LEFT:
            if (selected && it-- == heroes.begin()){
                it = heroes.end();
                it--;
            }
            break;
        case KEY_BACKSPACE:
            create = false;
            break;
        case 10:
            if (!selected)
            {
                try{
                    m_Map = new Map {m_DefaultMap, m_GameConfig};
                    m_Map->loadEntity(it->first, true);
                    displayGame();
                    // back to menu
                    create = false;
                }catch(const std::string& e){
                    clear();
                    mvprintw(0, 0, "%s",e.c_str());
                    refresh();
                    getch();
                    endwin();
                }catch(const char* e){
                    clear();
                    mvprintw(0, 0, "Error: %s",e);
                    refresh();
                    getch();
                    endwin();
                }
            }
        default:
            break;
        }
    }
    wclear(win);
    wrefresh(win);
    delwin(win);
}
void Game::msgPopUp(const std::string& msg){
    m_Exit = true;
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    int ySize = 6, xSize = 30;
    WINDOW *win = newwin(ySize, xSize, yMax / 2 - ySize / 2, xMax / 2 - xSize / 2);
    box(win, 0, 0);
    mvwprintw(win, 2, (xSize - msg.size()) / 2, "%s", msg.c_str());
    mvwprintw(win, 4, 5, "Press any key to exit");
    wrefresh(win);
    getch();
    wclear(win);
    wrefresh(win);
    delwin(win);
}