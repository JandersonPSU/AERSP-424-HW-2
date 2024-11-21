#include "robot.hpp"

// Constructor
Robot::Robot() {
    std::cout << "Robot Created" << std::endl;
}

// Destructor
Robot::~Robot() {}

// Setter
void Robot::setNum(const int& new_number) {
    number = new_number;
}

// Getter
int Robot::getNum() const {
    return number;
}

// Task Function
void Robot::Task(std::mutex& mutex1, std::mutex& mutex2, tool& tool1, tool& tool2) {
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate the time to grab the tools
    std::unique_lock<std::mutex> lock1(mutex1, std::defer_lock);
    std::unique_lock<std::mutex> lock2(mutex2, std::defer_lock);
    std::lock(lock1, lock2);

    std::cout << "Robot " << this->getNum() << " has " 
              << tool1.getName() << " and " << tool2.getName() 
              << ", and is working" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(5)); // Simulate the task duration
    std::cout << "Robot " << this->getNum() << " has finished working." << std::endl;
}
