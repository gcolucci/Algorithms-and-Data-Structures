### The Santa Claus Problem

## About the problem:

I first read about this problem in the "The Little Book of Semaphores", by Allen B. Downey. He states that the problem is from William Stalling's "Operating Systems," who, in turn, "attributes it to John Trono of St. Michael’s College in Vermont." Its formulation is this:  

> "Stand Claus sleeps in his shop at the North Pole and can only be awakened by either (1) some sleep, the elves can only wake him when three of them have problems. When three elves are having their problems solved, any other elves wishing to visit Santa must wait for those elves to return. If Santa wakes up to find three elves waiting at his shop’s door, along with the last reindeer having come back from the tropics, Santa has decided that the elves can wait until after Christmas, because it is more important to get his sleigh ready. (It is assumed that the reindeer do not want to leave the tropics, and therefore they stay there until the last possible moment.) The last reindeer to arrive must get Santa while the others wait in a warming hut before being harnessed to the sleigh."

Some additional constraints:                  
- After the ninth reindeer arrives, Santa must invoke prepareSleigh, and then all nine reindeer must invoke getHitched.                                               
- After the third elf arrives, Santa must invoke helpElves. Concurrently, all three elves should invoke getHelp.
- All three elves must invoke getHelp before any additional elves enter (increment the elf counter).
  
## About this solution:

This code was part of a project for a Operating Systems course I enrolled at the University of Campinas back in 2013. I thank my professor for the task. It uses only semaphores to synchronize the threads in C.  The number of reindeers and the minimum number of elves to wake Santa up are defined in constants. It prevents elves from getting help before Santa wakes up and does not allow Santa to sleep before finishing his worl. I believe these constraints are not explicit in the solution presented by Downey in the book.

The main.c file runs a simulation of this problem, randomly making reindeer arrive and elves have problems. The states and actions are printed with plain characters. At the top, there is a list of all elves, named from D1 to Dn, where n is the number of elves. It is followed by a list of reindeer, named from R1 to Rm, where m is the number of reindeer. Then, at the left, there is a ~~kind of weird~~ cubist depiction of Santa Claus, whose eyes change according to if he's awake or sleeping. Beside it, there is a box where all actions are printed. Below, there is a list of elves waiting for help.