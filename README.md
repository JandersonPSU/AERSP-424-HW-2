# AERSP-424-HW-2
Jack A, Peter B, and Sean's work for AERSP 424 HW 2
We used ChatGPT for some debugging and help in writing some comments


Question 5

If the robot finishes the task and is immediately assigned a new task, it is possible that it takes the tools again and completes the task, which could repeat. If this happened it would be possible for the same robot to monopolize the tools and lock out the other adjacent robots from completing their tasks, as it would be locking up the tools. A solution to this would be to create a queue along with the mutex such that there is an order to the robots doing their tasks. A semaphore could also be used to similar effect.
