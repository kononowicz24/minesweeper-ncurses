#include "plansza.h"
#include "pole.h"
#include <cstdlib>
//#include <conio2.h>//wywalić conio2 na rzecz crossplatformowej biblioteki
//#include "tinythread.h"
//#include <thread>
#include <ctime>
#include <curses.h>
#include "ui.h"

using namespace std;
//using namespace tthread;

void CzasThread(void * arg)
{
#ifdef ___WINDA
    clock_t czas_pocz;
    clock_t czas_akt;
    czas_pocz=clock();
#else
    int czas=0;
#endif
    while (1)
    {
        int currx, curry;
        getsyx(curry,currx);
        move(2,30);
     #ifdef ___WINDA
        czas_akt=clock();
        int czas=(int)((czas_akt-czas_pocz)/(CLOCKS_PER_SEC));
     #else
        czas++;
     #endif
        printw("Czas: %d", czas);
        move(curry,currx);
        refresh();
        //this_thread::sleep_for(chrono::milliseconds(1000));// pauza wątku na 1000 ms aby dalo się wpisywać komendy
    }
}

Plansza::Plansza(int _x, int _y, int _max_bomb)
{
//plansza jest tablicą jednowymiarową
//o wymiarach X x Y
//element  ma i*x+j
    pierwszy_ruch=true;
    x=_x;
    y=_y;
    max_bomb=_max_bomb;
    tablica.reserve(x*y);
    for (int i=0; i<(x*y); i++) tablica[i].bomba=false; //zerowanie tabllicy
    for (int i=0; i<max_bomb; i++)
    {
        tablica[rand()%(x*y)].bomba=true;
        //cout<<bomby[i];
        //cout<<".";//
        //tablica[i].stan=1;
    }
    for (int i=0; i<(x*y); i++)
        tablica[i].stan=1;
    odkryte=0;
    oflagowane=0;
    /*/cout<<endl;//
    for (int i=0; i<y; i++)//
    {
    for (int j=0; j<x; j++)//
        cout<<tablica[i*x+j].bomba;//
    cout<<endl;//
    }
    cout<<endl;//
    stan=0;//*/
    //printw("zakonczono towrzenie tablicy");
    //clear();
}

Plansza::~Plansza()
{
    Plansza::narysuj();
    //cout<<"usuwanie tablic";//
}

void Plansza::kolejkujwyspy(int _j, int _i)
{
    tablica[_i*x+_j].ile=0;
    if (tablica[_i*x+_j].bomba==0)
    {
        if (_i-1>=0&&_j-1>=0) tablica[_i*x+_j].ile+=tablica[(_i-1)*x+_j-1].bomba;
        if (_i-1>=0         ) tablica[_i*x+_j].ile+=tablica[(_i-1)*x+_j].bomba;
        if (_i-1>=0&&_j+1<x ) tablica[_i*x+_j].ile+=tablica[(_i-1)*x+_j+1].bomba;
        if (         _j-1>=0) tablica[_i*x+_j].ile+=tablica[_i*x+_j-1].bomba;
        if (         _j+1<x ) tablica[_i*x+_j].ile+=tablica[_i*x+_j+1].bomba;
        if (_i+1<y&&_j-1>=0 ) tablica[_i*x+_j].ile+=tablica[(_i+1)*x+_j-1].bomba;
        if (_i+1<y          ) tablica[_i*x+_j].ile+=tablica[(_i+1)*x+_j].bomba;
        if (_i+1<y&&_j+1<x  ) tablica[_i*x+_j].ile+=tablica[(_i+1)*x+_j+1].bomba;
        odkryte++;
        if (tablica[_i*x+_j].ile==0)
        {
            tablica[_i*x+_j].odkryj();
            if ((_i-1>=0&&_j-1>=0)&&tablica[(_i-1)*x+_j-1].stan==1)
            {
                tablica[(_i-1)*x+_j-1].odkryj();
                kolejkujwyspy(_j-1,_i-1);

            }
            if ((_i-1>=0        )&&tablica[(_i-1)*x+_j].stan==1)
            {
                tablica[(_i-1)*x+_j].odkryj();
                kolejkujwyspy(_j,  _i-1);

            }
            if ((_i-1>=0&&_j+1<x)&&tablica[(_i-1)*x+_j+1].stan==1)
            {
                tablica[(_i-1)*x+_j+1].odkryj();
                kolejkujwyspy(_j+1,_i-1);

            }
            if ((        _j-1>=0)&&tablica[(_i)*x+_j-1].stan==1)
            {
                tablica[(_i)*x+_j-1].odkryj();
                kolejkujwyspy(_j-1,_i);

            }
            if ((        _j+1<x)&&tablica[(_i)*x+_j+1].stan==1)
            {
                tablica[(_i)*x+_j+1].odkryj();
                kolejkujwyspy(_j+1,_i);

            }
            if ((_i+1<y&&_j-1>=0)&&tablica[(_i+1)*x+_j-1].stan==1)
            {
                tablica[(_i+1)*x+_j-1].odkryj();
                kolejkujwyspy(_j-1,_i+1);

            }
            if ((_i+1<y        )&&tablica[(_i+1)*x+_j].stan==1)
            {
                tablica[(_i+1)*x+_j].odkryj();
                kolejkujwyspy(_j,  _i+1);

            }
            if ((_i+1<y&&_j+1<x)&&tablica[(_i+1)*x+_j+1].stan==1)
            {
                tablica[(_i+1)*x+_j+1].odkryj();
                kolejkujwyspy(_j+1,_i+1);

            }
        }
    }
}

void Plansza::narysuj()
{
    start_color();
    move(3,45);
    //cout<<"Do odkrycia: "<<((x*y)-odkryte-max_bomb)<<" pol   ";
    printw("Do odkrycia: %d pol   ",((x*y)-odkryte-max_bomb));
    move(2,45);
    printw("Pozostalo %d bomb do oflagowania", max_bomb-oflagowane);
    move(5,1);
    for (int i=0; i<y; i++)
    {
        if (i==0)
        {
            for (int j=0; j<x; j++)
            {
                if (j%10==0) printw("%c",186);
                if (j%5==0&&j%10!=0) printw("|");
                if (j%5!=0) printw(".");
            }
            printw("\n");
        } // ^ramka góra

        if (i%10==0) printw("%c",205);
        if (i%10!=0&&i%5==0) printw("%c",196);
        if (i%5!=0) printw("%c",250);
        //ramka dół*/
        for (int j=0; j<x; j++)
        {
            switch (tablica[i*x+j].stan)
            {
            case 0:
            {
                init_pair(1,COLOR_BLUE, COLOR_BLACK);
                init_pair(2,COLOR_GREEN, COLOR_BLACK);
                init_pair(3,COLOR_RED, COLOR_BLACK);
                init_pair(4,COLOR_BLUE, COLOR_BLACK);
                init_pair(5,COLOR_RED, COLOR_BLACK);
                init_pair(6,COLOR_CYAN, COLOR_BLACK);
                init_pair(7,COLOR_WHITE, COLOR_BLACK);
                //cout<<(char)(tablica[i*x+j].ile?tablica[i*x+j].ile+48:' ');
                if (tablica[i*x+j].ile==1) attron(COLOR_PAIR(1)|A_BOLD); ////WIN32/DOS ONLY
                if (tablica[i*x+j].ile==2) attron(COLOR_PAIR(2)|A_BOLD);
                if (tablica[i*x+j].ile==3) attron(COLOR_PAIR(3)|A_BOLD);
                if (tablica[i*x+j].ile==4) attron(COLOR_PAIR(4));
                if (tablica[i*x+j].ile==5) attron(COLOR_PAIR(5));
                if (tablica[i*x+j].ile==6) attron(COLOR_PAIR(6));
                if (tablica[i*x+j].ile==7) attron(COLOR_PAIR(7));
                if (tablica[i*x+j].ile==8) attron(COLOR_PAIR(7)|A_BOLD);
                //cout<<((char)(tablica[i*x+j].ile?(!tablica[i*x+j].bomba?tablica[i*x+j].ile+48:'*'):(!tablica[i*x+j].bomba?' ':'*')));
                if (tablica[i*x+j].ile)
                {
                    if (tablica[i*x+j].bomba)
                    {
                        attron(A_BOLD);
                        printw("*");
                    }
                    else
                    {
                        printw("%d",tablica[i*x+j].ile);
                    }
                }
                else
                {
                    if (tablica[i*x+j].bomba)
                    {
                        attron(A_BOLD);
                        printw("*");
                    }
                    else
                    {
                        printw(" ");
                    }
                }
                //wyswietlane jako czar sprawdza czy jest liczba, póżniej sprawdza czy są bomby
                attroff(A_BOLD);
                attroff(COLOR_PAIR(1));
                attroff(COLOR_PAIR(2));
                attroff(COLOR_PAIR(3));
                attroff(COLOR_PAIR(4));
                attroff(COLOR_PAIR(5));
                attroff(COLOR_PAIR(6));
                attroff(COLOR_PAIR(7));
                break;
            }
            case 1:
            {
                printw("#");
                break;
            }
            case 2:
            {
                printw("F");
                break;
            }
            case 3:
            {
                printw("?");
                break;
            }
            }
        }
        printw("\n");
    }
}

void Plansza::czytaj()
{
    int dx, dy;
    char mode;
    //cin>>dx>>dy>>mode;
    scanw("%d %d %c", &dx, &dy, &mode);
    if (pierwszy_ruch)
    {
        //std::thread t(CzasThread, 0); //rozpoczecie nowego watku (void CzasThread) który liczy czas
        pierwszy_ruch=false;
        //t.detach(); //odłączenie wątku, ponieważ czas jest niezależny od planszy
    }
    switch (mode)
    {
    case 'b':
    case 'B':
    {
        if ((dx<x)&&(dy<y))
        {
            if (tablica[dy*x+dx].stan==1) kolejkujwyspy(dx,dy);
            if (tablica[dy*x+dx].odkryj()==127) stan=1;
            if ((x*y)-odkryte-max_bomb==0) stan=2;
        }
        break;
    }
    case 'f':
    case 'F':
    {
        if (tablica[dy*x+dx].stan==2)
        {
            tablica[dy*x+dx].stan=1;
            oflagowane--;
            break;
        }
        if (tablica[dy*x+dx].stan==1||tablica[dy*x+dx].stan==3)
        {
            tablica[dy*x+dx].stan=2;
            oflagowane++;
        }
        break;
    }
    case 'q':
    case 'Q':
    {
        ;
    }
    default:
        break;
    }
}
