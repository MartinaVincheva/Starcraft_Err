#ifndef SHIP_H_
#define SHIP_H_

#include <stdbool.h>

#include "Defines.h"

typedef struct ship ship;

typedef void (*tShowInfo)(ship *myShip);
typedef void (*tShowKilled)(ship *ownShip, ship *enemyShip);
typedef char(*(*tShipTypeToString)(void));
typedef bool (*tShipUnderAttack)(ship *attacker, ship *attacked);
typedef int (*tAttackStrength)(ship *attacker, ship *attacked);

typedef struct ship
{
    AirShipType type;
    int index;
    int health;
    tShowInfo showInfo;
    tShipTypeToString getShipTypeString;
    tShipUnderAttack shipUnderAttack;
    tAttackStrength attackStrength;
} ship;

#endif /* SHIP_H_ */