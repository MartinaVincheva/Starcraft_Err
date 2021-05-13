#ifndef TERRANSHIP_H_
#define TERRANSHIP_H_

#include "ship.h"

typedef struct terranShip
{
    ship item;
    int attacks;
} terranShip;

ship *createVikingShip(int index);
ship *createBattleShip(int index);

#endif /* TERRANSHIP_H_ */