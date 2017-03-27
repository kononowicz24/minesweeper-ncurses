#ifndef POLE_H_INCLUDED
#define POLE_H_INCLUDED

class Pole
{
    bool bomba;
    int ile;
  friend class Plansza;
public:
    short stan; //0-odkryte 1-nieodkryte 2-flaga 3-znak zapytania

    Pole();
    int odkryj();
};

#endif // POLE_H_INCLUDED
