#include <string.h>
#include <stdlib.h>

#include "BattleField.h"
#include "terranShip.h"
#include "protossShip.h"

void generateTerranFleet(BattleField *battleField, const char *terranFleetStr)
{
    int fleetSize = strlen(terranFleetStr);
    Vector *terranFleet = &battleField->terranFleet;

    vectorInit(terranFleet, sizeof(terranFleetStr));
    for (int idx = 0; idx < fleetSize; idx++)
    {
        ship *myShip;

        switch (terranFleetStr[idx])
        {
        case 'v':
        case 'V':
        {
            myShip = createVikingShip(idx);
            break;
        }
        case 'b':
        case 'B':
        {
            myShip = createBattleShip(idx);
            break;
        }
        }
        vectorPush(terranFleet, myShip);
    }
}

void generateProtossFleet(BattleField *battleField, const char *protossFleetStr)
{
    int protosFleetSize = strlen(protossFleetStr);
    Vector *protossFleet = &battleField->protossFleet;

    vectorInit(protossFleet, sizeof(protossFleetStr));
    for (int idx = 0; idx < protosFleetSize; idx++)
    {
        ship *myShip;

        switch (protossFleetStr[idx])
        {
        case 'p':
        case 'P':
        {
            myShip = createPhoenixShip(idx);
            break;
        }
        case 'c':
        case 'C':
        {
            myShip = createCarrierShip(idx);
            break;
        }
        }
        vectorPush(protossFleet, myShip);
    }
}

static void showKilled(ship *ownShip, ship *enemyShip)
{
    printf("%s with ID: %d killed enemy airship with ID: %d\n", ownShip->getShipTypeString(), ownShip->index, enemyShip->index);
}

void startBattle(BattleField *battleField)
{
    while (true)
    {
        if (processTerranTurn(battleField))
        {
            printf("TERRAN has won!\n");
            break;
        }

        if (processProtossTurn(battleField))
        {
            printf("PROTOSS has won!\n");
            break;
        }
    }
}

void deinit(BattleField *battleField)
{
    for (size_t idx = 0; idx < vectorGetSize(&battleField->terranFleet); idx++)
    {
        free(vectorGet(&battleField->terranFleet, idx));
    }
    vectorFree(&battleField->terranFleet);
    for (size_t idx = 0; idx < vectorGetSize(&battleField->protossFleet); idx++)
    {
        free(vectorGet(&battleField->protossFleet, idx));
    }
    vectorFree(&battleField->protossFleet);
}

bool processTerranTurn(BattleField *battleField)
{
    ship *attacked = vectorBack(&battleField->protossFleet);

    for (size_t idx = 0; (attacked != NULL) && (idx < vectorGetSize(&battleField->terranFleet)); idx++)
    {
        ship *attacker = vectorGet(&battleField->terranFleet, idx);

        if (false == attacked->shipUnderAttack(attacker, attacked))
        {
            showKilled(attacker, attacked);
            free(attacked);
            vectorPop(&battleField->protossFleet);
            attacked = vectorBack(&battleField->protossFleet);
        }
    }
    if (!vectorIsEmpty(&battleField->protossFleet))
    {
        attacked->showInfo(attacked);
        return (false);
    }
    return (true);
}

bool processProtossTurn(BattleField *battleField)
{
    ship *attacked = vectorBack(&battleField->terranFleet);

    for (size_t idx = 0; (attacked != NULL) && (idx < vectorGetSize(&battleField->protossFleet)); idx++)
    {
        protossShip *attacker = vectorGet(&battleField->protossFleet, idx);

        for (int attacks = attacker->attacksCount(attacker); (attacked != NULL) && (attacks > 0); attacks--)
        {
            if (false == attacked->shipUnderAttack((ship *)attacker, attacked))
            {
                showKilled((ship *)attacker, attacked);
                free(attacked);
                vectorPop(&battleField->terranFleet);
                attacked = vectorBack(&battleField->terranFleet);
            }
        }
        attacker->recover(attacker);
    }
    if (!vectorIsEmpty(&battleField->terranFleet))
    {
        attacked->showInfo(attacked);
        return (false);
    }
    return (true);
}
