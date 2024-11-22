// AERSP 424 HW 2 - Question 3 - Jack, Peter, Sean
// Some print statements commented out to match the output given but they are still relevant 
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>
#include <queue>

using namespace std;
using namespace chrono;


/* First Version of the HW
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

*/

// Debuged Version of the HW

// Code for the insomniac ATC controler

const int airMax = 3;

mutex mut;

class Air_Traffic_Controller
 {
private: // Setting up required checks
    bool Caffeine; // Check for if ATC is sleeping
    bool Landing; // Check to see if runway is clear for landing

    int TrafficPatternQueue; // Check used to see if to many planes are trying to land
    queue<int> LandingQueue; // Check to see where a plane is in the landing queue

public:

    Air_Traffic_Controller() : Caffeine(true), Landing(true), TrafficPatternQueue(0) {}

    void RedBull() 
    {
        Caffeine = false;
        
        cout << "BOO! The ATC is woken up."<<endl;
    }

    void NoCaffeine() 
    {
        
        if (TrafficPatternQueue == 0) 

        {  
            Caffeine = true;
            
            cout << "The ATC falls asleep. ZZZzzz..."<<endl;
        }
    }

    void RemoveFromTrafficPatternQueue() 
    {
        TrafficPatternQueue--;

        cout << "Runway is now free."<<endl;
        
        Landing = true; 

    
        if (!LandingQueue.empty()) 
        {

            int LandingAircraft = LandingQueue.front();

            LandingQueue.pop(); 

            cout << "Aircraft # " << LandingAircraft << " is cleared to land."<<endl;
            
            Landing = false; 

        }

    }
    
    void AddToTrafficPatternQueue(int PlaneNum) 
    {
        TrafficPatternQueue++;
        
        cout << "Aircraft # " << PlaneNum << " requesting landing."<<endl;
        
        if (TrafficPatternQueue == 1 && Landing) 
        { 
            cout << "Aircraft # " << PlaneNum << " is cleared to land."<<endl;
            
            Landing = false; 
        }

        else
        {
            cout << "Aircraft # " << PlaneNum << " is waiting for runway clearance."<<endl;

            LandingQueue.push(PlaneNum); 
        }

    }

    bool CheckCaffeine() const 
    {
        return Caffeine;
    }

    bool TrafficPatternCheck() const 
    {

        return TrafficPatternQueue >= airMax;

    }

};

// Debugging 140 ms is need to get to 5 seconds like shown in the example

void LandingFunc(Air_Traffic_Controller& ATC, double& LandingTime, int PlaneNum) 
{
    auto StartTime = high_resolution_clock::now(); 

    this_thread::sleep_for(milliseconds(140)); 

    {
        lock_guard<mutex> guard(mut); 
        if (ATC.CheckCaffeine()) 

        {
            ATC.RedBull();
        }

        if (!ATC.TrafficPatternCheck()) 

        {
            ATC.AddToTrafficPatternQueue(PlaneNum);
        }

        else 
        {
            cout << "Aircraft # " << PlaneNum << " requesting landing."<<endl;

            cout << "Approach pattern full. Aircraft #" << PlaneNum << " redirected to the Newark Airport."<<endl;

            cout << "Aircraft # " << PlaneNum <<" flying to the Newark Airport."<<endl;
            
        }

        return;

    }
    
    this_thread::sleep_for(seconds(1));
    {
        lock_guard<mutex> guard(mut);

        ATC.RemoveFromTrafficPatternQueue();

        ATC.NoCaffeine();  
    }

    auto EndTime = high_resolution_clock::now(); 

    auto LandingDuration = duration_cast<milliseconds>(EndTime - StartTime); 

    LandingTime = LandingTime + LandingDuration.count(); 

}

int main() 
{

    Air_Traffic_Controller ATC;

    vector<thread> MainThread;

    double LandingTime = 0; 

    for (int i = 0; i <= 9; i++) 

    {
        MainThread.emplace_back(LandingFunc, ref(ATC), ref(LandingTime), i);

        this_thread::sleep_for(milliseconds(140)); 
    }

    for (auto& thread : MainThread) 

    {
        thread.join();
    }

    int LandingTimeInSecs = (LandingTime / 1000); 

    cout << "duration : " << LandingTimeInSecs << " seconds."<<endl; 

    return 0;

}


