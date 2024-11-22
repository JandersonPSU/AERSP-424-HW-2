// AERSP 424 HW 2 - Question 3 - Jack, Peter, Sean

// NEED TO ADD A FUNCTION FOR ATC THREAD, BUT THE OUTPUT ON THE HW HAS NO COMMUNICATION FROM ATC//
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
    }

    {
        unique_lock<mutex> lock(mute); // Makes sure one airplane can check for landing status at a time 
        condition.wait(lock, [&] { return RunwayClear.load() && airspaceQue.front() == id; }); // Makes sure the airplane is at the front of the qeue and the runway is clear

        RunwayClear = false; // Set runway as not clear when an aircraft is landing
        fprintf(stdout, "Aircraft #%d is cleared to land.\n", id);
        airspaceQue.pop();

        lock.unlock(); // See if an airplane can enter the airspace while another airplane is landing 

        this_thread::sleep_for(chrono::seconds(1)); // The landing will occur, only taking a second

        lock.lock(); // Locks after the airplane has landed 
        fprintf(stdout, "Runway is now free.\n");
        RunwayClear = true; // Set runway as clear after the previous airplane has landed

        condition.notify_all(); // Notifies the next airplane that they can check if they are able to land     
    }
}

// Main function 

int main()
{
    thread aircraftThreads[aircraftTot]; // Initialize the amount of threads to the total amount of airplanes
    // Note: Random delay between aircraft arrivals so i can make the output
    //look like the provided output in the homework otherwise it will just be one airplane after another
    srand(time(0)); // Initialize the random number generator 

    for (int i = 0; i < aircraftTot; ++i) // Launch the airplanes  i.e. threads of which there are 10 total (not all at once though)

    {

        aircraftThreads[i] = thread(aircraft, i);
        this_thread::sleep_for(chrono::milliseconds(rand() % 1000)); // Random delay from 0 to 1 seconds with incriments of 1 millisecond 
    }

    for (auto& t : aircraftThreads) // Joining the threads to make sure every airplane will geta chance to land 

    {
        t.join();
    }

    return 0;
}
