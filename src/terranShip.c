#include <stdlib.h>
#include <stdio.h>

#include "terranShip.h"

static void printTerranShip(ship *myShip)
{
    printf("Last Terran AirShip with ID: %d has %d health left\n", myShip->index, myShip->health);
}

static bool terranUnderAttack(ship *attacker, ship *attacked)
{
    attacked->health -= attacker->attackStrength(attacker, attacked);
    return (attacked->health > 0);
}

static int vikingAttackStrength(ship *attacker, ship *attacked)
{
    (void)attacker;
    (void)attacked;
    if (attacked->type == PHOENIX)
    {
        return (VIKING_DAMAGE * VIKING_DAMAGE_MULTI);
    }
    return (VIKING_DAMAGE);
}

static char *vikingTypeToString(void)
{
    return ("Viking");
}

ship *createVikingShip(int index)
{
    terranShip *s = (terranShip *)malloc(sizeof(terranShip));

    s->item.type = VIKING;
    s->item.index = index;
    s->item.health = VIKING_HEALTH;
    s->item.showInfo = &printTerranShip;
    s->item.getShipTypeString = &vikingTypeToString;
    s->item.shipUnderAttack = &terranUnderAttack;
    s->item.attackStrength = &vikingAttackStrength;
    return (ship *)s;
}

static int battleShipAttackStrength(ship *attacker, ship *attacked)
{
    terranShip *myShip = (terranShip *)attacker;

    (void)attacked;
    if (myShip->attacks >= YAMATO_CANNON_LOADING_TURNS)
    {
        myShip->attacks = 0;
        return (BATTLE_CRUSER_DAMAGE * 5);
    }
    myShip->attacks++;
    return (BATTLE_CRUSER_DAMAGE);
}

static char *battleCruserTypeToString(void)
{
    return ("BattleCruser");
}

ship *createBattleShip(int index)
{
    terranShip *s = (terranShip *)malloc(sizeof(terranShip));

    s->item.type = BATTLE_CRUSER;
    s->item.index = index;
    s->item.health = BATTLE_CRUSER_HEALTH;
    s->item.showInfo = &printTerranShip;
    s->item.getShipTypeString = &battleCruserTypeToString;
    s->item.shipUnderAttack = &terranUnderAttack;
    s->item.attackStrength = &battleShipAttackStrength;
    s->attacks = 0;
    return (ship *)s;
}
