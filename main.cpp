//#include <iostream>
#include "plansza.h"
#include "pole.h"
#include "ui.h"
#include <ctime>
#include <cstdlib>
//#include <conio2.h>//
#include <curses.h>

#if defined(_WIN32) || defined(__WIN32__) || defined(__WINDOWS__)
#define ___WINDA
#endif
using namespace std;

int main()
{
    initscr();
    keypad(stdscr, TRUE);


    srand(time(NULL)+clock());
    Ui interfejs;
    getch();
    endwin();
    return 0;
}
