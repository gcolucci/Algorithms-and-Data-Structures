/*****************************************************************
 *  Libraries import.                                            *
 ****************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#include "santa.h"
#include "reindeer.h"
#include "elf.h"
#include "draw.h"

/*****************************************************************
 *  Global variables initialization.                             *
 ****************************************************************/
/* Counters. */
extern int elves; /* Counter of elves with problems. */
extern int reindeer; /* Counter of reindeer that returned from vacations. */

/* States used for writing the output. */
extern SantaState santaState;
extern Action action;
extern int reindeerWantToBeAttended;
extern int elvesWantToBeAttented;

/* Semaphores. */
extern sem_t semSanta;
extern sem_t semReindeer;
extern sem_t semElf;
extern sem_t semDoor;
extern sem_t lockCounters;
extern sem_t lockWaitForWork;
extern sem_t lockWaitForLastReindeer;
extern sem_t lockWrite;

/*****************************************************************
 *  Actions simulation.                                          *
 ****************************************************************/
/* Function triggered for Santa to prepare the sleigh. */
void prepareSleigh(){
    /* Write output. */
    sem_wait(&lockWrite);
    action = SANTA_PREPARED_SLEIGH;
    writeOutput();
}

/* Function triggered for Santa to help the elves. */
void helpElves(){
    /* Write output. */
    sem_wait(&lockWrite);
    action = SANTA_HELPED_ELVES;
    writeOutput();
}

/*****************************************************************
 *  Thread body. Randomly makes a reindeer get back.             *
 ****************************************************************/
void* fsanta(void *v) {
	int i;

	while (1) {
        /* Write output. */
        sem_wait(&lockWrite);
        santaState = SLEEPING;
        action = SANTA_SLEPT;
        writeOutput();

        sem_wait(&semSanta); /* Santa is initially sleeping. */

        /* Write state. */
        sem_wait(&lockWrite);
        santaState = AWAKE;
        action = SANTA_WOKE_UP;
        writeOutput();

		sem_wait(&lockCounters); /* Acquire counters lock. */

        /* Reindeer has priority over elves. */
		if (reindeer == N_REINDEER) { /* If all reindeer returned from vacations. */

            /* Write output. */
            sem_wait(&lockWrite);

            action = SANTA_ATTENDS_REINDEERS;
            reindeerWantToBeAttended = 0;
            writeOutput();

            /* Prepares the sleigh. */
            prepareSleigh();

			for (i = 0; i < N_REINDEER ; i++) {
				sem_post(&semReindeer); /* Wakes all reindeer up. */
			}
        }
		else if (elves == ELVES_GROUP_SIZE) { /* If there are the minimum number of elves waiting. */

            /* Write output. */
            sem_wait(&lockWrite);
            action = SANTA_ATTENDS_ELVES;
            elvesWantToBeAttented = 0;
            writeOutput();

            for (i = 0; i < ELVES_GROUP_SIZE ; i++) {
                sem_post(&semElf); /* Wakes all elves up. */
            }

            helpElves(); /* Helps the elves. */
        }

        sem_post(&lockCounters); /* Release counters lock. */
        sem_wait(&lockWaitForWork); /* Wait all reindeer to attach or all elves get help so that he can sleep again. */
	}

	return NULL;
}
