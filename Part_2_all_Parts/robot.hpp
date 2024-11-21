#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include "tool.hpp"

class Robot {
private:
    int number;

public:
    // Constructor
    Robot();

    // Destructor
    ~Robot();

    // Setter
    void setNum(const int& new_number);

    // Getter
    int getNum() const;

    // Task Function
    void Task(std::mutex& mutex1, std::mutex& mutex2, tool& tool1, tool& tool2);
};

#endif // ROBOT_H
