#include <stdio.h>
#include <stdlib.h>

/* Run "cmake -G "Unix Makefiles" CMakeLists.txt"
   and then "make" to build the executable */
#include "BattleField.h"

int main()
{
    const int buffSize = 50;
    char terranFleet[buffSize];
    char protossFleet[buffSize];
    scanf("%s %s", terranFleet, protossFleet);
    
    if (terranFleet==NULL){
        perror("invalid terranFleet entry");
        exit(1);
    }
    if (protossFleet==NULL){
        perror("invalid protossFleet entry");
        exit(1);
    }

    BattleField battleField;
    generateTerranFleet(&battleField, terranFleet);
    generateProtossFleet(&battleField, protossFleet);
    startBattle(&battleField);
    deinit(&battleField);

    return EXIT_SUCCESS;
}
