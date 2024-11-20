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

class SensorFactory 
{
public:

    static Sensor* createSensor(const string& sensorType) 
    
    {
        if (sensorType == "Air_Speed_Sensor") 
        {
            return new Air_Speed_Sensor();
        } 
        
        else if (sensorType == "Altitude_Sensor") 
        {
            return new Altitude_Sensor();
        } 
        
        else if (sensorType == "Ang_Of_Attck_Sensor") 
        {
            return new Ang_Of_Attck_Sensor();
        } 
        
        else 
        {
            return nullptr; 
        }

    }

};

// 4. Implement a control system class “AerospaceControlSystem”

class AerospaceControlSystem
{

private:

    vector<Sensor*> sensors;  

public:
    
    void addSensor(Sensor* sensor) 
    {
        sensors.push_back(sensor);
    }

    
    void monitorAndAdjust() 
    {
        for (Sensor* sensor : sensors) 
        {
            sensor->gatherData();  
            sensor->processData();  
            cout << "Adjusting controls based on sensor data." << endl;
        }
    }

};