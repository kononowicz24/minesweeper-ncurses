#include <iostream>
#include "pole.h"

using namespace std;

Pole::Pole()
{
    ;
}

int Pole::odkryj()
{
    switch (stan)
    {
        case 0: break; // tutaj chordowanie
        case 1:
        {
            stan=0;
            if (bomba)
            {
                return 127;
            }
            else
            {
                break;
            }
            break;
        }
        case 2: break;
        case 3: break;
    }
    return 0;
}
