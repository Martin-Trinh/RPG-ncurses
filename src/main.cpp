#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>
#include "include/Hero.h"
#include "include/Stats.h"
#include "include/Map.h"

void sideWindow (WINDOW* win, const std::string & title, const std::vector<std::string>& msg){
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 0, 1, "%s", title.c_str());
    for(size_t i = 0; i < msg.size(); i++){
        mvwprintw(win, i + 2, 1, "%s", msg.at(i).c_str());
    }
    wrefresh(win);
}
void Inventory(WINDOW * win, WINDOW * control, WINDOW * log){
    int key, selected = 0;
    std::vector<std::string> items = {
        "axe",
        "potion",
        "bread",
        "spear",
        "empty",
        "empty",
    };
    std::vector<std::string> equipments = {
        "Helmet",
        "Plate",
        "Weapon"
    };
    std::vector<std::string> controls = {
        "Select:   <arrow key>",
        "Use item: <e>",
        "Close:    <i>",
    };
    
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 0, 1, "Inventory");

    WINDOW * inven = newwin(items.size() + 2, 20, 4, 3);
    WINDOW * equip = newwin(8, 20, 4, 30);
    box(inven, 0, 0);
    box(equip, 0, 0);
    mvwprintw(inven, 0, 1, "Backpack");
    mvwprintw(equip, 0, 1, "Equipment");
    sideWindow(control, "Control key", controls);
    bool inventory = true;
    while(1){
        keypad(inven, true);
        keypad(equip, true);
        if(inventory){
            for(size_t i = 0; i < items.size(); i++){
                if((int)i == selected)
                    wattron(inven, A_STANDOUT);
                mvwprintw(inven, i + 1, 2, "%s", items.at(i).c_str());
                wattroff(inven, A_STANDOUT);
            }
            wrefresh(win);
            wrefresh(inven);

            key = wgetch(inven);
            switch (key)
            {
            case KEY_DOWN:
                if(++selected > (int)items.size() - 1)
                    selected = 0;
                break;
            case KEY_UP:
                if(--selected < 0)
                    selected = items.size() - 1;
                break;
            case 's':
                inventory = false;
                selected = 0;
                break;
            case 'e':
                wmove(log, 1, 1);
                wclrtoeol(log);
                wprintw(log, "You used %s", items.at(selected).c_str());
                wrefresh(log);
                break;    
            default:
                break;
            }
        }else{
            for(size_t i = 0; i < equipments.size(); i++){
                if((int)i == selected)
                    wattron(equip, A_STANDOUT);
                mvwprintw(equip, i + 1, 2, "%s", equipments.at(i).c_str());
                wattroff(equip, A_STANDOUT);
            }
            wrefresh(win);
            wrefresh(equip);

            key = wgetch(equip);
            switch (key)
            {
            case KEY_DOWN:
                if(++selected > (int)equipments.size() - 1)
                    selected = 0;
                break;
            case KEY_UP:
                if(--selected < 0)
                    selected = equipments.size() - 1;
                break;
            case 's':
                inventory = true;
                selected = 0;
                break;
            case 'e':
                wmove(log, 1, 1);
                wclrtoeol(log);
                wprintw(log, "You used %s", items.at(selected).c_str());
                wrefresh(log);
                break;    
            default:
                break;
            }
        }
        if(key == 'i')
            break;
        
    };
    werase(win);
}
bool Warning(){
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    int xSize = 30, ySize = 6;
    WINDOW * win = newwin(ySize, xSize, yMax/2 - ySize/2, xMax/2 - xSize/2);
    box(win, 0, 0);
    bool choice = false;
    keypad(win, true);
    std:: string msg = "Do you want to quit?";
    std:: string msg1 = "Yes, I want to quit";
    std:: string msg2 = "No, I want to stay";

    while(1){
        mvwprintw(win, 1, (xSize - msg.size())/2, "%s", msg.c_str());

        if(choice)
            wattron(win, A_STANDOUT);
        mvwprintw(win, 3, (xSize - msg1.size())/2, "%s", msg1.c_str());
        wattroff(win, A_STANDOUT);

        if(!choice)
            wattron(win, A_STANDOUT);
        mvwprintw(win, 4, (xSize - msg2.size())/2, "%s", msg2.c_str());
        wattroff(win, A_STANDOUT);

        int key = wgetch(win);
        if (key == KEY_UP || key == KEY_DOWN)
            choice ? choice = false : choice = true;

        if(key == 10){
            wclear(win);
            wrefresh(win);
            return choice;
        }
    }
    
}
void displayGame(){
    clear();
    refresh();
    // init main window
    int xSize = 62, ySize = 25;
    int startX = 1, startY = 1;
    WINDOW * win = newwin(ySize, xSize, startX, startY);
    keypad(win, true);
    // init log window
    WINDOW * log = newwin(6, xSize, ySize + 1, startX);
    box(log, 0, 0);
    mvwprintw(log, 0, 1, "Game message");
    // init side windows 
    WINDOW * heroStats = newwin(10, 20, startY, xSize + 1); 
    WINDOW * enemyStats = newwin(10, 20, startY, xSize + 1 + 20); 
    WINDOW * skill = newwin(8, 20, startY + 10 , xSize + 1);
    WINDOW * control = newwin(8, 25, startY + 18, xSize + 1);
    //create Hero
    Stats wizardStats {};
    Hero p {win, "wizard", '@', 1, 1, wizardStats};

    std::vector<std::string> guide = {
        "Movement:  <arrow keys>",
        "Inventory: <i>",
        "Skill:     <s>",
        "Quit:      <backspace>"
    };
    std::vector<std::string> skills = {
        "Primary:   <1>",
        "Magic:     <2>",
        "Ultimate:  <3>",
    };
    std::vector<std::string> statName = {
        "HP",
        "Mana",
        "Strength",
        "Magic",
        "Armor",
        "Magic res",
        "Point"
    };
    int statVal[7] = {200, 50, 20, 10, 10, 0, 0};
    for(size_t i = 0; i < statName.size(); i++){
        statName.at(i) += ": " ;
        statName.at(i).append(std::to_string(statVal[i]));
    }
    Map map {"map1.txt"};
    int move; 
    while(1){
        box(win, 0, 0);
        mvwprintw(win, 0, 1, "Game screen");
        map.displayMap(win);
        wrefresh(win);
        // print map and entity here
        p.displayCharacter();
        // messages
        wrefresh(log);
        // side windows
        sideWindow(heroStats, " Hero Stats", p.statsToVector());
        sideWindow(enemyStats, "Enemy Stats", p.statsToVector());
        sideWindow(skill, "Skill set",skills);
        sideWindow(control,"Control key",guide);
        move = p.getMove();
        if(move == KEY_BACKSPACE && Warning())
            break;
        if(move == 'i'){
            Inventory(win, control, log);
        }
        if(move > '0' && move < '4'){
            mvwprintw(log, 1,1, "You cast %s", skills.at(move-49).c_str());
        }
    };
    clear();
    refresh();
}
void createHero()
{
    int selected = 0, type = 0;
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    int ySize = 13, xSize = 25;
    WINDOW * win = newwin(ySize, xSize, yMax / 2 - 5, xMax / 2 + 10);
    int winXMax = getmaxx(win);
    std::string name;
    std::string arrHero[3] = {"Warrior", "Wizard", "Archer"};
    int statsWarrior[5] = {200, 50, 20, 10, 10};
    int statsWizard[5] = {100, 100, 5, 20, 8};
    int statsArcher[5] = {100, 20, 15, 10, 5};
    bool create = true;
    while (create)
    {
        int line = 1;
        werase(win);
        box(win, 0, 0);
        if (selected == 0)
            wattron(win, A_STANDOUT);
        mvwprintw(win, line++, 1, "Hero name: %s",  name.c_str());
        wattroff(win, A_STANDOUT);

        wmove(win, line++,1);
        whline(win, ACS_HLINE, 23);

        if (selected == 1)
            wattron(win, A_STANDOUT);
        mvwprintw(win, line++, 1, "Hero type: < %s >", arrHero[type].c_str());
        wattroff(win, A_STANDOUT);

        line++;

        switch (type)
        {
        case 0:
            mvwprintw(win, line++, 1, "HP: %d", statsWarrior[0]);
            mvwprintw(win, line++, 1, "Mana: %d", statsWarrior[1]);
            mvwprintw(win, line++, 1, "Strength: %d", statsWarrior[2]);
            mvwprintw(win, line++, 1, "Intel: %d", statsWarrior[3]);
            mvwprintw(win, line++, 1, "Armor: %d", statsWarrior[4]);
            break;
        case 1:
            mvwprintw(win, line++, 1, "HP: %d", statsWizard[0]);
            mvwprintw(win, line++, 1, "Mana: %d", statsWizard[1]);
            mvwprintw(win, line++, 1, "Strength: %d", statsWizard[2]);
            mvwprintw(win, line++, 1, "Intel: %d", statsWizard[3]);
            mvwprintw(win, line++, 1, "Armor: %d", statsWizard[4]);
            break;
        case 2:
            mvwprintw(win, line++, 1, "HP: %d", statsArcher[0]);
            mvwprintw(win, line++, 1, "Mana: %d", statsArcher[1]);
            mvwprintw(win, line++, 1, "Strength: %d", statsArcher[2]);
            mvwprintw(win, line++, 1, "Intel: %d", statsArcher[3]);
            mvwprintw(win, line++, 1, "Armor: %d", statsArcher[4]);
            break;
        default:
            break;
        }    
        wmove(win,10,1);
        whline(win, ACS_HLINE, 23);
        if (selected == 2)
            wattron(win, A_STANDOUT);
        mvwprintw(win, 11, winXMax/2 - 2, "Play");
        wattroff(win, A_STANDOUT);


        keypad(win, true);
        int key = wgetch(win);
        switch (key)
        {
        case KEY_UP:
            if (--selected < 0)
                selected = 2;
            break;
        case KEY_DOWN:
            if (++selected > 2)
                selected = 0;
            break;
        case KEY_RIGHT:
            if(selected == 1 && ++type > 2)
                type = 0;
            break;
        case KEY_LEFT:
            if (selected == 1 && --type < 0)
                type = 2;
            break;
        case KEY_BACKSPACE:
            create = false;
            break;
        case 10:
            if(selected == 2){
                displayGame();
                create = false;
            }
    
        default:
            if (isalpha(key) && selected == 0)
                name.push_back(key);
            break;
        }
    }
    wclear(win);
    wrefresh(win);
}

void displayMainMenu()
{
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    int ySize = 10, xSize = 20;
    WINDOW *win = newwin(10, 20, yMax/2 - ySize/2, xMax/2 - xSize/2);

    std::vector<std::string> Options = {"New Game", "Load Game", "Controls", "Exit"};
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
        keypad(win, true);
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
                createHero();
            if (Options.at(selected) == "Exit")
                exit = true;
            break;
        default:
            break;
        }
    }
    
}


int main()
{
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    displayMainMenu();

    endwin();
    return 0;
}