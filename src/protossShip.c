#include <stdlib.h>
#include <stdio.h>

#include "protossShip.h"

int MAX_FLEET_SIZE = 100;

static void printProtossShip(ship *myShip)
{
    if (NULL == myShip)
    {
        perror("Function printProtossShip pointer is null\n");
        exit(-1);
    }
    protossShip *pShip = (protossShip *)myShip;

    if (!pShip)
    {
        perror("Failed to cast !\n");
        exit(-1);
        ;
    }

    printf("Last Protoss AirShip with ID: %d has %d health and %d shield left\n", pShip->item.index, pShip->item.health, pShip->shield);
}

static bool protossUnderAttack(ship *attacker, ship *attacked)
{
    if (NULL == attacker || NULL == attacked)
    {
        perror("Function protossUnderAttack pointer is null\n");
        exit(-1);
    }
    int attack_strenght = attacker->attackStrength(attacker, attacked);
    protossShip *myShip = (protossShip *)attacked;

    if (!myShip)
    {
        perror("Failed to cast !\n");
        exit(-1);
    }

    if (attack_strenght <= myShip->shield)
    {
        myShip->shield -= attack_strenght;
    }
    else
    {
        attack_strenght -= myShip->shield;
        myShip->shield = 0;
        myShip->item.health -= attack_strenght;
    }
    return (attacked->health > 0);
}

static void recoverPhoenixShield(protossShip *myShip)
{
    if (NULL == myShip)
    {
        perror("Function printProtossShip pointer is null\n");
        exit(-1);
    }

    myShip->shield += PHOENIX_SHIELD_REGENERATE_RATE;
    if (myShip->shield > PHOENIX_SHIELD)
    {
        myShip->shield = PHOENIX_SHIELD;
    }
}

static int phoenixAttacksCount(protossShip *myShip)
{
    if (NULL == myShip)
    {
        perror("Function printProtossShip pointer is null\n");
        exit(-1);
    }
    (void)myShip;
    return (1);
}

static int phoenixAttackStrength(ship *attacker, ship *attacked)
{
    if (NULL == attacker || NULL == attacked)
    {
        perror("Function protossUnderAttack pointer is null\n");
        exit(-1);
    }

    (void)attacker;
    (void)attacked;
    return (PHOENIX_DAMAGE);
}

static char *phoenixTypeToString(void)
{
    return ("Phoenix");
}

ship *createPhoenixShip(int index)
{
    if (!((index > 0) && (index < MAX_FLEET_SIZE)))
    {
        perror("Index is out of bounds!\n");
        exit(-1);
    }
    protossShip *s = (protossShip *)malloc(sizeof(protossShip));

    if (!s)
    {
        perror("Unsuccessful memory allocation for protossShip\n");
        exit(-1);
    }

    s->item.type = PHOENIX;
    s->item.index = index;
    s->item.health = PHOENIX_HEALTH;
    s->item.showInfo = &printProtossShip;
    s->item.getShipTypeString = &phoenixTypeToString;
    s->item.shipUnderAttack = &protossUnderAttack;
    s->item.attackStrength = &phoenixAttackStrength;
    s->recover = &recoverPhoenixShield;
    s->shield = PHOENIX_SHIELD;
    s->attacksCount = &phoenixAttacksCount;
    return ((ship *)s);
}

static void recoverCarrierShield(protossShip *myShip)
{
    if (NULL == myShip)
    {
        perror("Function recoverCarrierShield pointer is null\n");
        exit(-1);
    }
    myShip->shield += CARRIER_SHIELD_REGENERATE_RATE;
    if (myShip->shield > CARRIER_SHIELD)
    {
        myShip->shield = CARRIER_SHIELD;
    }
}

static int carrierAttacksCount(protossShip *myShip)
{
    if (NULL == myShip)
    {
        perror("Function carrierAttacksCount pointer is null\n");
        exit(-1);
    }
    if (myShip->item.health < CARRIER_HEALTH)
    {
        return (DAMAGED_STATUS_INTERCEPTORS);
    }
    return (MAX_INTERCEPTORS);
}

static int carrierAttackStrength(ship *attacker, ship *attacked)
{
    if (NULL == attacker || NULL == attacked)
    {
        perror("Function carrierAttackStrength pointer is null\n");
        exit(-1);
    }
    (void)attacker;
    (void)attacked;
    return (CARRIER_DAMAGE);
}

static char *carrierTypeToString(void)
{
    return ("Carrier");
}

ship *createCarrierShip(int index)
{
    if (!((index >= 0) && (index < MAX_FLEET_SIZE)))
    {
        perror("Index is out of bounds!");
        exit(-1);
    }

    protossShip *s = (protossShip *)malloc(sizeof(protossShip));

    if (!s)
    {
        perror("Unsuccessful memory allocation for protossShip\n");
        exit(-1);
    }

    s->item.type = CARRIER;
    s->item.index = index;
    s->item.health = CARRIER_HEALTH;
    s->item.showInfo = &printProtossShip;
    s->item.getShipTypeString = &carrierTypeToString;
    s->item.shipUnderAttack = &protossUnderAttack;
    s->item.attackStrength = &carrierAttackStrength;
    s->recover = &recoverCarrierShield;
    s->shield = CARRIER_SHIELD;
    s->attacksCount = &carrierAttacksCount;
    return ((ship *)s);
}
