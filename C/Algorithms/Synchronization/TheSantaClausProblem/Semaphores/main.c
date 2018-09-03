/*****************************************************************
 *  Libraries import.                                            *
 ****************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#include "reindeer.h"
#include "santa.h"
#include "draw.h"
#include "elf.h"

/*****************************************************************
 *  Global variables initialization.                             *
 ****************************************************************/
/* Counters. */
int elves = 0; /* Counter of elves with problems. */
int reindeer = 0; /* Counter of reindeer back from vacations. */

/* States used for writing the output. */
SantaState santaState;
ElfState *elvesStates;
ReindeerState *reindeerStates;
Action action;
int reindeerThatArrived;
int reindeerThatWasAttached;
int reindeerWantToBeAttended = 0;
int elfThatGotHelp;
int elfThatArrivedAtTheDoor;
int elfThatHadProblems;
int elvesWantToBeAttented = 0;

/* Semaphores. */
sem_t semSanta;
sem_t semReindeer;
sem_t semElf;
sem_t semDoor;
sem_t lockCounters;
sem_t lockWaitForWork;
sem_t lockWaitForLastReindeer;
sem_t lockWrite;

/* Constants. */
extern const int N_REINDEER; /* Amount of reindeer in the sleigh. */
extern const int N_ELVES; /* Amount of reindeer in the sleigh. */

/*****************************************************************
 *  Main.                                                        *
 ****************************************************************/
int main (int argc, char *argv[]) {
    /* Santa thread. */
    pthread_t santa;

	/* Reindeer threads and their IDs arrays. */
	pthread_t *reindeer = (pthread_t *) malloc(sizeof(pthread_t) * N_REINDEER);
	int *reindeerIds = (int *) malloc(sizeof(int) * N_REINDEER);

	/* Elves threads and their IDs arrays. */
	pthread_t *elves = (pthread_t *) malloc(sizeof(pthread_t) * N_ELVES);
    int *elvesIds = (int *) malloc(sizeof(int) * N_ELVES);

    int i;

    /* Semaphore initialization. */
    sem_init (&semSanta, 0, 0);
    sem_init (&semReindeer, 0, 0);
    sem_init (&semElf, 0, 0);
    sem_init (&semDoor, 0, 1);
    sem_init (&lockCounters, 0, 1);
    sem_init (&lockWaitForWork, 0, 0);
    sem_init (&lockWaitForLastReindeer, 0, 0);
    sem_init (&lockWrite, 0, 1);

    /* Santa's state initialization. */
    santaState = SLEEPING;

    /* Reindeer's state initialization. */
    reindeerStates = (ReindeerState *) malloc(sizeof(ReindeerState) * N_REINDEER);
    for (i = 0; i < N_REINDEER; i++) {
        reindeerStates[i] = VACATIONS;
    }

    /* Elves' state initialization. */
    elvesStates = (ElfState *) malloc(sizeof(ElfState) * N_ELVES);
    for (i = 0; i < N_ELVES; i++) {
        elvesStates[i] = WORKING;
    }

    /* Seed for generation of random numbers. */
    srand(time(NULL));

	/* Creation of Santa's thread. */
	pthread_create(&santa, NULL, fsanta, NULL);

	/* Creation of reindeer's threads. */
	for (i = 0; i < N_REINDEER; i++) {
		reindeerIds[i] = i;
		pthread_create(&reindeer[i], NULL, freindeer, (void*) &reindeerIds[i]);
	}

	/* Creation of elves' threads. */
	for (i = 0; i < N_ELVES; i++) {
		elvesIds[i] = i;
		pthread_create(&elves[i], NULL, felf, (void*) &elvesIds[i]);
	}

    /* Santa's thread execution. */
    pthread_join(santa, NULL);

    /* Releases memory. */
    free(reindeer);
    free(reindeerIds);
    free(elves);
    free(elvesIds);
    free(reindeerStates);
    free(elvesStates);

	return 0;
}
