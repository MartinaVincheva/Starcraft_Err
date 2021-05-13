#include <stdlib.h>
#include <stdio.h>

#include "terranShip.h"

static void printTerranShip(ship *myShip)
{
    if (NULL == myShip)
    {
        perror("Function printTerranShip pointer is null\n");
        return NULL;
    }

    printf("Last Terran AirShip with ID: %d has %d health left\n", myShip->index, myShip->health);
}

static bool terranUnderAttack(ship *attacker, ship *attacked)
{
    if (NULL == attacker || NULL == attacked)
    {
        perror("Function terranUnderAttack pointers null\n");
        return NULL;
    }

    attacked->health -= attacker->attackStrength(attacker, attacked);
    return (attacked->health > 0);
}

static int vikingAttackStrength(ship *attacker, ship *attacked)
{
    if (NULL == attacker || NULL == attacked)
    {
        perror("Function vikingAttackStrenght pointers null\n");
        return NULL;
    }

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
    if (!((index > 0) && (index < MAX_FLEET_SIZE))) 
    {
        perror("createVikingShip index is out of bounds!\n");
        return NULL;
    }

    terranShip *s = (terranShip *)malloc(sizeof(terranShip));

    if (!s)
    {
        perror("Unsuccessful memory allocation for createVikingShip\n");
        return NULL;
    }

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
    if (NULL == attacker || NULL == attacked)
    {
        perror("Function battleShipAttackStrength pointers null\n");
        return NULL;
    }

    terranShip *myShip = (terranShip *)attacker;
    
    if (NULL == myShip)
    {
        perror("check battleShipAttackStrength *myShip\n");
        return NULL;
    }

    (void)attacked;
    if (myShip->attacks >= YAMATO_CANNON_LOADING_TURNS)
    {
        myShip->attacks = 0;
        return (BATTLE_CRUSER_DAMAGE * BATTLE_CRUSER_DAMAGE_MULTI);
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
    if (!((index > 0) && (index < MAX_FLEET_SIZE)))
    {
        perror("createBattleShip index is out of bounds!");
        return NULL;
    }

    terranShip *s = (terranShip *)malloc(sizeof(terranShip));

    if (!s)
    {
        perror("Unsuccessful memory allocation for createBattleShip\n");
        return NULL;
    }

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
