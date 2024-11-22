#ifndef HW2_Q_1_HPP
#define HW2_Q_1_HPP

#include <iostream>
#include <vector>
#include <string>

class Sensor {
public:
    virtual ~Sensor() {}
    virtual void gatherData() const = 0;
    virtual void processData() const = 0;
};

class Air_Speed_Sensor : public Sensor {
public:
    void gatherData() const override;
    void processData() const override;
};

class Altitude_Sensor : public Sensor {
public:
    void gatherData() const override;
    void processData() const override;
};

class Ang_Of_Attck_Sensor : public Sensor {
public:
    void gatherData() const override;
    void processData() const override;
};

class SensorFactory {
public:
    static Sensor* createSensor(const std::string& sensorType);
};

class AerospaceControlSystem {
private:
    std::vector<Sensor*> sensors;
public:
    void addSensor(Sensor* sensor);
    void monitorAndAdjust();
};

#endif // HW2_Q_1_HPP
