// This is the code for AERSP 424 HW 2 Question 1 for Jack A, Peter B, and Sean

#include <iostream>  // Include the input-output stream library
#include <iomanip>   // Include the library for input/output formatting
#include <vector>    // Include the vector container library
#include <string>    // Include the string library for string operations

using namespace std; // Use the standard namespace to avoid the need for std:: prefix

// 1. Implement an abstract base class “Sensor” 

// Define the Sensor class as an abstract base class
class Sensor
{

public:

    // Virtual destructor to ensure proper cleanup when deleting objects of derived classes
    virtual ~Sensor () {}

    // Pure virtual function to "gather data" from the sensor
    virtual void gatherData() const = 0;

    // Pure virtual function to "process" the "gathered data"
    virtual void processData() const = 0;
};

// Define a derived class for Air Speed Sensor
class Air_Speed_Sensor:public Sensor
{

public:

    // Overriding the gatherData function specific to Air_Speed_Sensor
    void gatherData() const 
    {
        cout << "Gathering data from <Air Speed> Sensor"<< endl;  // Print statement for gathering data
    }
    
    // Overriding the processData function specific to Air_Speed_Sensor
    void processData() const 
    {
        cout << "Processing data from <Air Speed> Sensor" << endl;  // Print statement for processing data
    }

};

// Define a derived class for Altitude Sensor
class Altitude_Sensor:public Sensor
{

public:

    // Overriding the gatherData function specific to Altitude_Sensor
    void gatherData() const  
    {
        cout << "Gathering data from <Altitude> Sensor" << endl;  // Print statement for gathering data
    }

    // Overriding the processData function specific to Altitude_Sensor
    void processData() const
    {
        cout << "Processing data from <Altitude Sensor>" << endl;  // Print statement for processing data
    }

};

// Define a derived class for Angle of Attack Sensor
class Ang_Of_Attck_Sensor:public Sensor
{

public:

    // Overriding the gatherData function specific to Ang_Of_Attck_Sensor
    void gatherData() const 
    {
        cout << "Gathering data from <Angle of Attack> Sensor" << endl;  // Print statement for gathering data
    }
    
    // Overriding the processData function specific to Ang_Of_Attck_Sensor
    void processData() const
    {
        cout << "Processing data from <Angle of Attack> Sensor" << endl;  // Print statement for processing data
    }

};

// Define a factory class to create Sensor objects
class SensorFactory 
{
public:

    // Static method to create the sensor based on the sensor type string
    static Sensor* createSensor(const string& sensorType) 
    {
        // If the sensorType is "Air_Speed_Sensor", create and return an Air_Speed_Sensor object
        if (sensorType == "Air_Speed_Sensor") 
        {
            return new Air_Speed_Sensor();  // Return a new Air_Speed_Sensor object
        } 
        
        // If the sensorType is "Altitude_Sensor", create and return an Altitude_Sensor object
        else if (sensorType == "Altitude_Sensor") 
        {
            return new Altitude_Sensor();  // Return a new Altitude_Sensor object
        } 
        
        // If the sensorType is "Ang_Of_Attck_Sensor", create and return an Ang_Of_Attck_Sensor object
        else if (sensorType == "Ang_Of_Attck_Sensor") 
        {
            return new Ang_Of_Attck_Sensor();  // Return a new Ang_Of_Attck_Sensor object
        } 
        
        // If the sensorType is unrecognized, return nullptr
        else 
        {
            return nullptr;  // Return null if no valid sensorType
        }
    }

};

// 4. Implement a control system class “AerospaceControlSystem”

// Define a class to simulate the aerospace control system
class AerospaceControlSystem
{

private:

    vector<Sensor*> sensors;  // Vector to hold Sensor pointers

public:
    
    // Method to add a sensor to the system
    void addSensor(Sensor* sensor) 
    {
        sensors.push_back(sensor);  // Add the sensor to the vector
    }

    // Method to monitor and adjust the system based on sensor data
    void monitorAndAdjust() 
    {
        // Iterate over each sensor in the vector
        for (Sensor* sensor : sensors) 
        {
            sensor->gatherData();  // Call the gatherData method on each sensor
            sensor->processData();  // Call the processData method on each sensor
            cout << "Adjusting controls based on sensor data." << endl;  // Print a statement for adjusting controls
        }
    }

};

// 5. The “main()” function, 

int main() 
{

    AerospaceControlSystem ctrlSys;  // Create an object of AerospaceControlSystem

    // Create and add a new Air_Speed_Sensor to the control system
    Sensor* Air_Speed_Sensor = SensorFactory::createSensor("Air_Speed_Sensor");
    ctrlSys.addSensor(Air_Speed_Sensor);  // Add the Air_Speed_Sensor to the control system

    // Create and add a new Altitude_Sensor to the control system
    Sensor* Altitude_Sensor = SensorFactory::createSensor("Altitude_Sensor");
    ctrlSys.addSensor(Altitude_Sensor);  // Add the Altitude_Sensor to the control system

    // Create and add a new Ang_Of_Attck_Sensor to the control system
    Sensor* Ang_Of_Attck_Sensor = SensorFactory::createSensor("Ang_Of_Attck_Sensor");
    ctrlSys.addSensor(Ang_Of_Attck_Sensor);  // Add the Ang_Of_Attck_Sensor to the control system

    // Monitor and adjust the system based on the sensors' data
    ctrlSys.monitorAndAdjust();  // Call the method to monitor and adjust

    return 0;  // Return 0 to indicate successful execution
}
