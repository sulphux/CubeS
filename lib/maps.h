#ifndef MAPS_H_INCLUDED
#define MAPS_H_INCLUDED


#include <time.h>
#include "konsola.h"
#include "defines.h"

char mapa[ROZ_Y][ROZ_X];

void zaladuj_mape()
{
    srand(time(NULL));
    size_t x;
    size_t y;
    for(y=0; y<ROZ_Y; y++)
    {
        for(x=0; x<ROZ_X; x++)
        {
            mapa[y][x] = P00;
        }
    }

    for (x=0; x<50; x++)
    {
        mapa[abs(rand()%ROZ_Y)/1][abs(rand()%ROZ_X)/1]++;
    }
}

void rysuj_mape()
{
    clearScreen();
    size_t x,y;
    for(y=0; y<ROZ_Y; y++)
    {
        for(x=0; x<ROZ_X; x++)
        {
            putchar(mapa[y][x]);
        }
        putchar('\n');
    }
}


#endif // MAPS_H_INCLUDED
