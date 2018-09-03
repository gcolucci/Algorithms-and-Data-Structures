/*****************************************************************
 *  Libraries import.                                            *
 ****************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#include "reindeer.h"
#include "draw.h"

/*****************************************************************
 *  Global variables initialization.                             *
 ****************************************************************/
/* Counters. */
extern int reindeer; /* Counter of reindeer that are back from vacations. */

/* States used for writing the output. */
extern ReindeerState *reindeerStates;
extern Action action;
extern int reindeerThatArrived;
extern int reindeerThatWasAttached;
extern int reindeerWantToBeAttended;

/* Semaphores. */
extern sem_t semSanta;
extern sem_t semReindeer;
extern sem_t semDoor;
extern sem_t lockCounters;
extern sem_t lockWaitForWork;
extern sem_t lockWaitForLastReindeer;
extern sem_t lockWrite;

/* Constants. */
const int N_REINDEER = 8; /* Amount of reindeer in the sleigh. */

/*****************************************************************
 *  Actions simulation.                                          *
 ****************************************************************/
/* Function triggered by each reindeer to get attached after the sleigh gets fixed. */
void getHitched(int id) {
    int i;

    sem_wait(&lockCounters); /* Acquire counters lock. */

    reindeer--; /* After getting help, decreases reindeer counter. */

    /* Print that a reindeer got attached. */
    sem_wait(&lockWrite);

    action = REINDEER_ATTACHED;

    reindeerThatWasAttached = id;
    reindeerStates[id] = ATTACHED;
    writeOutput();

    if (reindeer == 0) { /* When the last reindeer attaches. */
        sem_post(&lockWaitForWork); /* Allows Santa to get back to sleep. */

        for (i = 1; i < N_REINDEER; i++) {
            sem_post(&lockWaitForLastReindeer); /* Allows the sleigh to leave. */
        }

        /* Write output. */
        sem_wait(&lockWrite);
        for (i = 0; i < N_REINDEER; i++) {
            reindeerStates[i] = VACATIONS; /* All reindeer will leave on vacations thereafter. */
        }
        action = REINDEER_LEFT;
        writeOutput();

        sem_post(&lockCounters); /* Release counters lock. */

        sleep(random() % 50);
    }
    else { /* If there are more reindeer to return. */
        sem_post(&lockCounters); /* Release counters lock. */
        sem_wait(&lockWaitForLastReindeer); /* Wait for the remaining reindeer. */

        sleep(random() % 50);
    }
}

/*****************************************************************
 *  Thread body. Randomly makes a reindeer get back.             *
 ****************************************************************/
void* freindeer(void *v) {
	int id = * (int*) v;

	sleep(random() % 15);

	while (1) {
		sem_wait(&lockCounters); /* Acquire counters lock. */

        reindeer++; /* A new reindeer has returned. */

        /* Write state. */
        sem_wait(&lockWrite);

        reindeerThatArrived = id;
        action = REINDEER_ARRIVED;
        reindeerStates[id] = REINDEER_WAITING_SANTA;
        writeOutput();

        if (reindeer == N_REINDEER) { /* Last reindeer to return. */
            /* Write state. */
            sem_wait(&lockWrite);

            action = REINDEER_COMPLETE;
            reindeerWantToBeAttended = 1;
            writeOutput();

            sem_post(&semSanta); /* Signals to wake Santa up. */
        }

		sem_post(&lockCounters); /* Release counters lock. */
		sem_wait(&semReindeer); /* Reindeer sleep until Santa wakes them up. */

		getHitched(id); /* When they wake up, they get attached to the sleigh. */

        /* Write state. */
        sem_wait(&lockWrite);
        writeOutput();
	}

	return NULL;
}
