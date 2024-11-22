#ifndef HW2_Q_1_HPP
#define HW2_Q_1_HPP

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Abstract base class "Sensor"
class Sensor
{
public:
    virtual ~Sensor() {}                       // Virtual destructor
    virtual void gatherData() const = 0;       // Pure virtual function for gathering data
    virtual void processData() const = 0;      // Pure virtual function for processing data
};

// Derived class for Air Speed Sensor
class Air_Speed_Sensor : public Sensor
{
public:
    void gatherData() const override;          // Override gatherData for Air Speed Sensor
    void processData() const override;         // Override processData for Air Speed Sensor
};

// Derived class for Altitude Sensor
class Altitude_Sensor : public Sensor
{
public:
    void gatherData() const override;          // Override gatherData for Altitude Sensor
    void processData() const override;         // Override processData for Altitude Sensor
};

// Derived class for Angle of Attack Sensor
class Ang_Of_Attck_Sensor : public Sensor
{
public:
    void gatherData() const override;          // Override gatherData for Angle of Attack Sensor
    void processData() const override;         // Override processData for Angle of Attack Sensor
};

// Factory class for creating Sensor objects
class SensorFactory
{
public:
    static Sensor* createSensor(const string& sensorType); // Factory method to create sensors
};

// Class for Aerospace Control System
class AerospaceControlSystem
{
private:
    vector<Sensor*> sensors;                   // Vector to store Sensor pointers

public:
    void addSensor(Sensor* sensor);            // Add a sensor to the system
    void monitorAndAdjust();                   // Monitor and adjust based on sensor data
};

#endif // HW2_Q_1_HPP
