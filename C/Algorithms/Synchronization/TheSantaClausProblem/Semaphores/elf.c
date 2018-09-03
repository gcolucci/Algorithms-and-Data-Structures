/*****************************************************************
 *  Libraries import.                                            *
 ****************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#include "elf.h"
#include "draw.h"

/*****************************************************************
 *  Global variables initialization.                             *
 ****************************************************************/
/* Counters. */
extern int elves; /* Counter of elves with problems. */

/* States used for writing the output. */
extern ElfState *elvesStates;
extern Action action;
extern int elfThatGotHelp;
extern int elfThatArrivedAtTheDoor;
extern int elfThatHadProblems;
extern int elvesWantToBeAttented;

/* Semaphores. */
extern sem_t semSanta;
extern sem_t semElf;
extern sem_t semDoor;
extern sem_t lockCounters;
extern sem_t lockWaitForWork;
extern sem_t lockWaitForLastReindeer;
extern sem_t lockWrite;

/* Constants. */
const int N_ELVES = 15; /* Amount of elves in the simulation. */
const int ELVES_GROUP_SIZE = 3; /* Minimum amount of elves with problem so that Santa wakes up. */

/*****************************************************************
 *  Actions simulation.                                          *
 ****************************************************************/
/* Function triggered by each elf when they will get help from Santa. */
void getHelp(int id){
    sem_wait(&lockCounters); /* Acquire counters lock. */

    sem_wait(&lockWrite); /* Acquire lock for printing output. */

    elvesStates[id] = WORKING; /* Elf starts to work again. */

    action = ELF_GOT_HELP;
    elfThatGotHelp = id;
    writeOutput();

    elves--; /* After getting help, decreases elves counter. */

    if (elves == 0) { /* When the last elf gets help. */
        sem_post(&lockWaitForWork); /* Allows Santa to sleep. */
        sem_post(&semDoor); /* Releases door lock. */
    }

    sem_post(&lockCounters); /* Releases counters lock. */

    sleep(random() % 30);
}

/*****************************************************************
 *  Thread body. Randomly makes an elf have problems.            *
 ****************************************************************/
void* felf(void *v) {
	int id = * (int*) v;

	sleep(random() % 10);

	while (1) {
        /* Write state. */
        sem_wait(&lockWrite); /* Acquire lock for printing output. */

        elvesStates[id] = WITH_PROBLEM; /* Elf has a problem. */

        action = ELF_HAS_PROBLEM;
        elfThatHadProblems = id;
        writeOutput();

        sem_wait(&semDoor); /* Elf gets in and shuts the door to ask Santa help. */

        /* Write state. */
        sem_wait(&lockWrite);

        elvesStates[id] = ELF_WAITING_SANTA; /* Elf waits for Santa to wake up. */

        action = ELF_ARRIVED_DOOR;
        elfThatArrivedAtTheDoor = id;
        writeOutput();

		sem_wait(&lockCounters); /* Acquire counters lock. */

		elves++; /* Increases the number of elves at the door. */

		if (elves == ELVES_GROUP_SIZE)	{ /* If the number of elves at the door reaches the minimum.*/
            /* Write state. */
            sem_wait(&lockWrite);
            action = ELF_COMPLETE;
            elvesWantToBeAttented = 1;
            writeOutput();

			sem_post(&semSanta); /* Signals to wake Santa up. */
		}
		else { /* Otherwise */
            sem_post(&semDoor); /* Opens the door. */
		}

		sem_post(&lockCounters); /* Release counters lock. */

        sem_wait(&semElf); /* Elves sleep at the door until Santa wakes up. */

		getHelp(id); /* When wakes up, the elf ask for help. */
	}

	return NULL;
}
