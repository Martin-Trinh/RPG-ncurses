#include "include/Game.h"
Game::Game(){
    initscr();
    noecho();
    cbreak();
    curs_set(0);
}
Game::~Game(){
    delete m_Map;
    delwin(m_Win);
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
    WINDOW *skill = newwin(8, 20, startY + 11, xSize + 1);
    WINDOW *control = newwin(10, 25, startY + 19, xSize + 1);
    int move;
    bool running = true;
    m_Hero->addLogWin(log);
    m_Hero->addStatsWin(heroStats);

    log->displayMsg("Welcome to the game!");
    m_Map->display(win);
    m_Hero->displaySkill(skill);
    m_Hero->displayStats();
    this->displayControl(control);
    while (running)
    {
        move = m_Map->getKey(win, control);
        switch (move)
        {
        case KEY_BACKSPACE:
            if(this->warning())
                running = false;
            break;
            // save game
            // display wiki
        default:
            break;
        }
        box(win, 0, 0);
        mvwprintw(win, 0, 1, "Game screen");
        m_Map->display(win);
        this->displayControl(control);
    };
    clear();
    refresh();
}
void Game::displayControl(WINDOW* win) const{
    werase(win);
    box(win, 0, 0);
    int line = 0;
    mvwprintw(win, line++, 1, "Control keys");
    line++;
    mvwprintw(win, line++, 1, "Movement:  <arrow keys>");
    mvwprintw(win, line++, 1, "Inventory: <i>");
    mvwprintw(win, line++, 1, "Skill 1:   <1>");
    mvwprintw(win, line++, 1, "Skill 2:   <2>");
    mvwprintw(win, line++, 1, "Skill 3:   <3>");
    mvwprintw(win, line++, 1, "Quit:      <backspace>");
    wrefresh(win);
}
bool Game::warning(){
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
    std::vector<std::string> Options = {"New Game", "Load Game", "Wiki", "Exit"};

    int selected = 0;
    bool exit = false;
    while (!exit)
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
            // if (Options.at(selected) == "Wiki")
            // if (Options.at(selected) == "Load Game")
            if (Options.at(selected) == "Exit")
                exit = true;
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
    
    std::string nameHero[3] = {"Warrior", "Wizard", "Archer"};
    // stats for hero
    std::vector<Stats> stats;
    std::vector<AttackSkill*> attackSkill;
    std::vector<HealSkill*> healSkill;

    stats.push_back(Stats{100, 100, 3, 10, 3, 5}),
    stats.push_back(Stats{100, 100, 7, 0, 11, 1}),
    stats.push_back(Stats{100, 100, 10, 5, 3, 2}),
    
    // add skills for hero
    attackSkill.push_back(new AttackSkill {"Primary attack", 1, 5, 10, true}),
    attackSkill.push_back(new AttackSkill {"Primary attack", 2, 5, 20, false}),
    attackSkill.push_back(new AttackSkill {"Primary attack", 3, 5, 10, false}),

    healSkill.push_back(new HealSkill{"Heal", 2, 5, 10});
    healSkill.push_back(new HealSkill{"Heal", 2, 5, 10});
    healSkill.push_back(new HealSkill{"Heal", 2, 5, 10});

    int type = 0;
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
        mvwprintw(win, line++, 1, "Hero type: < %s >", nameHero[type].c_str());
        wattroff(win, A_STANDOUT);
        line++;
        // display stats each hero
            mvwprintw(win, line++, 1, "HP: %d", stats[type].getHP());
            mvwprintw(win, line++, 1, "Mana: %d", stats[type].getMana());
            mvwprintw(win, line++, 1, "Strength: %d", stats[type].getStrength());
            mvwprintw(win, line++, 1, "Magic: %d", stats[type].getMagic());
            mvwprintw(win, line++, 1, "Armor: %d", stats[type].getArmor());
            mvwprintw(win, line++, 1, "Resistance: %d", stats[type].getResistance());
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
            if (selected && ++type > 2)
                type = 0;
            break;
        case KEY_LEFT:
            if (selected && --type < 0)
                type = 2;
            break;
        case KEY_BACKSPACE:
            create = false;
            break;
        case 10:
            if (!selected)
            {
                try{
                    m_Map = new Map {"map1.txt"};
                    m_Hero = new Hero{nameHero[type], 0, 0, stats[type]};
                    m_Hero->addSkill(attackSkill[type]);
                    m_Hero->addSkill(healSkill[type]);
                    m_Map->loadEntity(m_Hero);
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