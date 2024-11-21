#include <iostream>
#include <thread>
#include <mutex>
#include "tool.hpp"
#include "robot.hpp"

int main() {
    std::mutex m0, m1, m2, m3, m4; // Creating mutexes for each tool

    tool tool0;
    tool0.setName("tool0");
    tool tool1;
    tool1.setName("tool1");
    tool tool2;
    tool2.setName("tool2");
    tool tool3;
    tool3.setName("tool3");
    tool tool4;
    tool4.setName("tool4");

    Robot R0;
    R0.setNum(0);

    Robot R1;
    R1.setNum(1);

    Robot R2;
    R2.setNum(2);

    Robot R3;
    R3.setNum(3);

    Robot R4;
    R4.setNum(4);

    std::thread t1(&Robot::Task, &R0, std::ref(m0), std::ref(m4), std::ref(tool0), std::ref(tool4));
    std::thread t2(&Robot::Task, &R1, std::ref(m0), std::ref(m1), std::ref(tool0), std::ref(tool1));
    std::thread t3(&Robot::Task, &R2, std::ref(m1), std::ref(m2), std::ref(tool1), std::ref(tool2));
    std::thread t4(&Robot::Task, &R3, std::ref(m2), std::ref(m3), std::ref(tool2), std::ref(tool3));
    std::thread t5(&Robot::Task, &R4, std::ref(m3), std::ref(m4), std::ref(tool3), std::ref(tool4));

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    std::cout << "All Robots have finished" << std::endl;
    return 0;
}
