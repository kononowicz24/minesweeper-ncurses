#include "ui.h"
#include "plansza.h"
#include <curses.h>

using namespace std;

Ui::Ui()
{
    int x,y,bomb;
    printw("Witaj w grze saper\nPodaj rozmiar planszy\ni oddziel je spacja\nx, y, ilosc_bomb");
    printw("\n");
    scanw("%d %d %d",&x, &y, &bomb);

    if (bomb<=(x-1)*(y-1))
    {

        Plansza plansza(x,y,bomb);
        plansza.stan=false;
        while (plansza.stan==0)
        {
            plansza.narysuj();
            plansza.czytaj();
        }
        switch (plansza.stan)
        {
        case 1:
            {
                printw("przegrales");
                break;
            }
        case 2:
            {
                printw("wygrales");
                break;
            }
        }
    }
}
Ui::~Ui()
{
    ;
}

