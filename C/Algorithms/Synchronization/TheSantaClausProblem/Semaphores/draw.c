/*****************************************************************
 *  Libraries import.                                            *
 ****************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#include "draw.h"
#include "reindeer.h"
#include "elf.h"

/*****************************************************************
 *  Global variables initialization.                             *
 ****************************************************************/
/* States used for output. */
extern SantaState santaState;
extern ElfState *elvesStates;
extern ReindeerState *reindeerStates;
extern Action action;
extern int reindeerThatArrived;
extern int reindeerThatWasAttached;
extern int reindeerWantToBeAttended;
extern int elfThatGotHelp;
extern int elfThatArrivedAtTheDoor;
extern int elfThatHadProblems;
extern int elvesWantToBeAttented;

/* Semaphores. */
extern sem_t lockWrite;

/*****************************************************************
 *  Write of program actions and states                          *
 ****************************************************************/
void writeOutput() {
    int i, j, idAux, actionHasNumber = 0;
    char *actionWrite;

    sleep(1);

    /* Elves. */
    printf("\nELVES: ");
    for (i = 0; i < N_ELVES; i++) {
        if (i % 7 == 0 && i > 0) {
            printf("\n%9c", ' ');
        }

        if (elvesStates[i] == WORKING) {
            printf("%10c", ' ');
        }
        else if (elvesStates[i] == WITH_PROBLEM) {
            printf("D%d%*c", i, i > 99? 6: i > 9? 7: 8, ' ');
        }
        else if (elvesStates[i] == ELF_WAITING_SANTA) {
            printf("%10c", ' ');
        }
    }
    printf("\n\n\n");

    /* Reindeer. */
    printf("REINDEER: %2c", ' ');
    for (i = 0; i < N_REINDEER; i++) {
        if (i % 7 == 0 && i > 0) {
            printf("\n%9c", ' ');
        }

        if (reindeerStates[i] == VACATIONS) {
            printf("%10c", ' ');
        }
        else if (reindeerStates[i] == REINDEER_WAITING_SANTA) {
            printf("R%d%*c", i, i > 99? 6: i > 9? 7: 8, ' ');
        }
        else if (reindeerStates[i] == ATTACHED) {
            printf("----%*c", 5, ' ');
        }
    }
    printf("\n\n\n");

    /* Chooses the action to be printed. */
    switch (action) {
        case SANTA_SLEPT:
            actionWrite = "SANTA HAS SLEPT";
            break;
        case SANTA_WOKE_UP:
            actionWrite = "SANTA HAS WOKEN UP";
            break;
        case SANTA_PREPARED_SLEIGH:
            actionWrite = "SANTA HAS PREPARED THE SLEIGH";
            break;
        case SANTA_HELPED_ELVES:
            actionWrite = "SANTA HAS GONE TO HELP THE ELVES";
            break;
        case SANTA_ATTENDS_REINDEERS:
            actionWrite = "SANTA IS ATTENDING THE REINDEERS";
            break;
        case SANTA_ATTENDS_ELVES:
            actionWrite = "SANTA IS ATTENDING THE ELVES";
            break;
        case REINDEER_ARRIVED:
            actionWrite = "HAS ARRIVED THE REINDEER";
            actionHasNumber = 1;
            idAux = reindeerThatArrived;
            break;
        case REINDEER_ATTACHED:
            actionWrite = "HAS ATTACHED ITSELF THE REINDEER";
            actionHasNumber = 1;
            idAux = reindeerThatWasAttached;
            break;
        case REINDEER_LEFT:
            actionWrite = "REINDEERS WENT TO WORK AND LEAVE ON VACATIONS";
            break;
        case REINDEER_COMPLETE:
            actionWrite = "ALL REINDEERS ARRIVED";
            break;
        case ELF_HAS_PROBLEM:
            actionWrite = "HAS PROBLEMS THE ELF";
            actionHasNumber = 1;
            idAux = elfThatHadProblems;
            break;
        case ELF_ARRIVED_DOOR:
            actionWrite = "HAS ARRIVED AT THE DOOR THE ELF";
            actionHasNumber = 1;
            idAux = elfThatArrivedAtTheDoor;
            break;
        case ELF_GOT_HELP:
            actionWrite = "GOT HELP THE ELF";
            actionHasNumber = 1;
            idAux = elfThatGotHelp;
            break;
        case ELF_COMPLETE:
            actionWrite = "ALL ELVES ARRIVED";
    }

    /* Santa. */
    printf("---------|        |-----------------------------------\n");
    printf("   / \\   |        |\n");
    printf("  /   \\  |        | %s\n", elvesWantToBeAttented ? "ELVES WANT HELP" : "");
    printf(" /-----\\ |        |\n");

    if (!actionHasNumber) {
        printf(" | %s | |        |  %s\n", santaState == AWAKE ? "O.O" : "U.U", actionWrite);
    }
    else {
        printf(" | %s | |        |  %s %d\n", santaState == AWAKE ? "O.O" : "U.U", actionWrite, idAux);
    }

    printf(" \\-----/ |        |\n");
    printf("  \\   /  |        | %s\n", reindeerWantToBeAttended ? "REINDEER WANT HELP" : "");
    printf("   \\ /   |        |___________________________________\n\n");

    for (i = 0, j = 0; i < N_ELVES; i++) {
        if (j % 5 == 0 && j > 0) {
            printf("\n");
        }

        if (elvesStates[i] == ELF_WAITING_SANTA) {
            printf("D%d%*c", i, i > 99? 6: i > 9? 7: 8, ' ');
            j++;
        }
    }

    printf("\n\n\n");
    sem_post(&lockWrite);
}
