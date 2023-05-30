#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
void displayGame(){
    refresh();
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    WINDOW * win = newwin(30, 50, yMax/2 - 15, xMax/2 - 25);
    // wborder(win, '#','#', '#', '#', '#', '#', '#', '#');
    box(win, 0, 0);
    Player p {win, 1, 1, '@'};

    do {
        p.display();
        wrefresh(win);
    }while(p.getMove() != KEY_BACKSPACE);

    wclear(win);
    wrefresh(win);
}
void createHero()
{
    int selected = 0, type = 0;
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    WINDOW *win = newwin(13, 25, yMax / 2 - 5, xMax / 2 + 10);
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
    WINDOW *win = newwin(10, 20, yMax / 2 - 5, xMax / 2 - 10);

    std::vector<std::string> Options = {"New Game", "Load Game", "Tutorial", "Exit"};
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