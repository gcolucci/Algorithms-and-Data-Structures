/*****************************************************************
 *  Definition of states and actions.                            *
 ****************************************************************/
/* Santa's possible states. */
typedef enum {
    SLEEPING,
    AWAKE
} SantaState;

/* Reindeer's possible states. */
typedef enum {
    VACATIONS,
    REINDEER_WAITING_SANTA,
    ATTACHED,
} ReindeerState;

/* Elves' possible states. */
typedef enum {
    WORKING,
    WITH_PROBLEM,
    ELF_WAITING_SANTA,
} ElfState;

/* Possible actions. */
typedef enum {
    SANTA_SLEPT,
    SANTA_WOKE_UP,
    SANTA_PREPARED_SLEIGH,
    SANTA_HELPED_ELVES,
    SANTA_ATTENDS_REINDEERS,
    SANTA_ATTENDS_ELVES,
    REINDEER_ARRIVED,
    REINDEER_ATTACHED,
    REINDEER_LEFT,
    REINDEER_COMPLETE,
    ELF_HAS_PROBLEM,
    ELF_ARRIVED_DOOR,
    ELF_GOT_HELP,
    ELF_COMPLETE
} Action;

/*****************************************************************
 *  Functions.                                                   *
 ****************************************************************/
void writeOutput();
