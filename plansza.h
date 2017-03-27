#ifndef PLANSZA_H_INCLUDED
#define PLANSZA_H_INCLUDED
#include "pole.h"
#include <vector>
class Plansza
{

    //std::string uniqueid;
    int x, y, max_bomb;

    std::vector < Pole > tablica;
    bool pierwszy_ruch;

    int odkryte;
    int oflagowane;

public:
    int stan;// flase gdy jeszcze gra
    //0 - w trakcie gry 1- przegrana 2 -wygrana

    Plansza(int x, int y, int _max_bomb);

    ~Plansza();

    void kolejkujwyspy(int _x, int _y);

    void narysuj();

    void czytaj();

};

#endif // PLANSZA_H_INCLUDED
