// This is the code for AERSP 424 HW 2 Question 1 for Jack A, Peter B, and Sean

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;


// 1. Implement an abstract base class “Sensor” 

// Define the Sensor class
class Sensor
{

public:

    // Virtual destructor to make sure no issue pop up with derived class objects
    virtual ~Sensor () {}

    // Pure virtual function to "gather data" from the sensor
    virtual void gatherData() const = 0;

    // Pure virtual function to "process" the "gathered data"
    virtual void processData() const = 0;
};

class Air_Speed_Sensor:public Sensor
{

public:

    void gatherData() const
    {
        cout << "Gathering data from <Air Speed> Sensor"<< endl;
    }
    void processData() const
    {
        cout << "Processing data from <Air Speed> Sensor" << endl;
    }

};

class Altitude_Sensor:public Sensor
{

public:

    void gatherData() const 
    {
        cout << "Gathering data from <Altitude> Sensor" << endl;
    }
    void processData() const
    {
        cout << "Processing data from <Altitude Sensor>" << endl;
    }

};

class Ang_Of_Attck_Sensor:public Sensor
{

public:

    void gatherData() const
    {
        cout << "Gathering data from <Angle of Attack> Sensor" << endl;
    }
    void processData() const
    {
        cout << "Processing data from <Angle of Attack> Sensor" << endl;
    }

};

