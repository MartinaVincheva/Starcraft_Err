#ifndef PROTOSSSHIP_H_
#define PROTOSSSHIP_H_

#include "ship.h"

typedef struct protossShip protossShip;
typedef int (*tAttacksCount)(protossShip *myShip);
typedef void (*tRecoverShield)(protossShip *myShip);

typedef struct protossShip
{
    ship item;
    int shield;
    tAttacksCount attacksCount;
    tRecoverShield recover;
} protossShip;

ship *createPhoenixShip(int index);
ship *createCarrierShip(int index);

#endif /* PROTOSSSHIP_H_ */