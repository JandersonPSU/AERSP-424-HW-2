# AERSP-424-HW-2
Jack A, Peter B, and Sean's work for AERSP 424 HW 2

Question 6

One primary issue which can occur during the simulation is when the ATC is sleeping while an airplane is waiting to land on the runway. This is known as the race condition. An example of this is an airplane entering the airspace while the ATC is occupied, so the pilot must wait for directives. However, since it takes some intermediate time for the pilot to enter to the front of the queue, the current airplane which ATC is handling could have landed which would prompt the ATC to check for an airplane in the queue, but no airplane will be there as it has not entered yet. If this happens, the ATC will go to sleep. A solution to this problem is the mutex function, which can be implemented to make sure that only 1 action may occur at a time, preventing the race condition problem from occurring. 
