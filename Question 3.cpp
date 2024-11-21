// NOT COMPLETE YET, NEEDS FIX

// AERSP 424 HW 2 - Question 3 - Jack, Peter, Sean

#include <iostream>
#include <thread>
#include <mutex>
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
atomic<bool> SleepATC(true); // ATC is initially asleep
atomic<bool> RunwayClear(true); // Runway is initially clear

// Aircraft function which will be used in the main function    

void aircraft(int id) // id is the number assigned to a specific aircraft (1-10)
{
    {
        unique_lock<mutex> lock(mute);
        cout << "Aircraft #" << id << " requesting landing." << endl;

        while (airspaceQue.size() >= airMax) // Check if the airspace is at capacity

        {
            condition.wait(lock); // If airspace is at capacity, incomiing aircraft must wait 
        }

        airspaceQue.push(id); // If the airspace is open, an aircraft may enter

        if (SleepATC) 

        {
            SleepATC = false; // Wake up the ATC if they are sleeping
            condition.notify_all(); // Notify all waiting threads i.e. the pilots
        }
    }

    {
        unique_lock<mutex> lock(mute);
        condition.wait(lock, [&] { return RunwayClear.load() && airspaceQue.front() == id; });

        RunwayClear = false; // Set runway as not clear when an aircraft is landing
        cout << "Aircraft #" << id << " is cleared to land." << endl;
        airspaceQue.pop();

        lock.unlock();

        this_thread::sleep_for(chrono::seconds(1)); // The landing will occur, only taking a second

        lock.lock();
        cout << "Runway is now free." << endl;
        RunwayClear = true; // Set runway as clear after the previous airplae has landed
        condition.notify_all();

        if (airspaceQue.empty())

        {
            SleepATC = true; // If the airspace is empty, the ATC can go to sleep 
        }
    }
}

// Main function 

int main()
{
    thread aircraftThreads[aircraftTot]; // Initialize the amound of threads to the total amound of airplanes

    for (int i = 0; i < aircraftTot; ++i) // Launcg the airplanes (threads) of which there are 10 total (not all at once though)

    {
        aircraftThreads[i] = thread(aircraft, i);
    }

    for (int i = 0; i < aircraftTot; ++i) // The threads will join 

    {
        aircraftThreads[i].join();
    }

    return 0;
}
