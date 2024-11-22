// AERSP 424 HW 2 - Question 3 - Jack, Peter, Sean
// Some print statements commented out to match the output given but they are still relevant 
#include <iostream>
#include <thread>
#include <mutex>
#include <random>
#include <condition_variable>
#include <queue>
#include <atomic>
#include <chrono>

using namespace std;

// Defining constants and variables 

const int airMax = 3; // Maximum number of airplanes in the airspace
const int aircraftTot = 10; // Total number of airplanes for this simulation
queue<int> airspaceQue; // Queue for airplanes currently in the airspace  
mutex mute;
condition_variable condition;
atomic<bool> RunwayClear(true); // Runway is initially clear

// Aircraft function which will be used in the main function    

void aircraft(int id) // id is the number assigned to a specific aircraft (0-10)
{
    {
        unique_lock<mutex> lock(mute); // Makes sure only 1 aircraft enters the queue (airspace) at a time 
        fprintf(stdout, "Aircraft #%d requesting landing.\n", id);

        while (airspaceQue.size() >= airMax) // Check if the airspace is at capacity
         
        {
            condition.wait(lock); // Airplane must wait if the airspace is at capacity 
        }

        airspaceQue.push(id); // If the airspace is open, an aircraft may enter
        condition.notify_all(); // Notify ATC that a new aircraft has entered the airspace
    }

    {
        unique_lock<mutex> lock(mute); // Makes sure one airplane can check for landing status at a time 
        condition.wait(lock, [&] { return RunwayClear.load() && airspaceQue.front() == id; }); // Makes sure the airplane is at the front of the queue and the runway is clear
        fprintf(stdout, "Aircraft #%d is cleared to land.\n", id);
        airspaceQue.pop(); // Remove the airplane from the queue because it landed already
        RunwayClear = false; // The runway is not clear 
        condition.notify_all(); // Notify ATC that the aircraft is landing
    }

    // Simulate landing duration
    this_thread::sleep_for(chrono::seconds(1));

    {
        unique_lock<mutex> lock(mute);
        RunwayClear = true; // Set runway to clear after the previous airplane has landed
        fprintf(stdout, "Runway is now free.\n");
        condition.notify_all(); // Notify the next airplane in the queue that they can request landing
    }
}

// ATC function which will be used in main function

void ATC()
{
    while (true) // Loop will keep running 

    {
        unique_lock<mutex> lock(mute); // Allows ATC to take control 
        if (airspaceQue.empty()) // See if airplanes are in the queue so ATC can sleep or wake up 

        {
            // fprintf(stdout, "ATC falls asleep\n");   // commenting out to match output
            condition.wait(lock, [] { return !airspaceQue.empty(); }); // Condition for ATC waking up 
            // fprintf(stdout, "ATC wakes up\n");   // commenting out to match output
        }
        condition.notify_all(); // Notifies airplanes that ATC is processing the queue
    }
}

// Main function 

int main()
{
    thread atcThread(ATC); // Create ATC thread    
    thread aircraftThreads[aircraftTot]; // Create airplane thread/Initialize the amount of threads to the total amount of airplanes
    // Note: Random delay between aircraft arrivals so it can make the output
    // look like the provided output in the homework otherwise it will just be one airplane after another
    srand(time(0)); // Initialize the random number generator 

    for (int i = 0; i < aircraftTot; ++i) // Launch the airplanes  i.e. threads of which there are 10 total (not all at once though)

    {
        aircraftThreads[i] = thread(aircraft, i);
        this_thread::sleep_for(chrono::milliseconds(rand() % 1000)); // Random delay from 0 to 1 seconds with increments of 1 millisecond 
    }

    for (auto& t : aircraftThreads) // Joining the threads to make sure every airplane will get a chance to land 

    {
        t.join();
    }

    atcThread.detach(); // Allowing the ATC thread to continue running

    return 0;
}
