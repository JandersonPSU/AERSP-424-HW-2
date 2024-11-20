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