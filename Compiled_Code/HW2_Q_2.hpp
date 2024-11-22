#ifndef HW2_Q_2_HPP
#define HW2_Q_2_HPP

#include <iostream>
#include <string>
#include <mutex>

class tool {
private:
    std::string name;
public:
    tool();
    ~tool();
    void setName(const std::string& new_name);
    std::string getName();
};

class Robot {
private:
    int number;
public:
    Robot();
    ~Robot();
    void setNum(const int& new_number);
    int getNum();
    void Task(std::mutex& mutex1, std::mutex& mutex2, tool& tool1, tool& tool2);
};

#endif // HW2_Q_2_HPP
