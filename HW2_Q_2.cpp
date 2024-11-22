// This is the code for AERSP 424 HW 2 Question 2 for Jack A, Peter B, and Sean

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;




class tool{
private:
    string name;
public:


    //Constructor
    tool(){
        cout<<"Tool Created"<<endl;
    };
    //Destructor
    ~tool(){};
    //setter
    void setName(const string& new_name){
        name=new_name;
    };
    //getter
    string getName(){
        return name;
    };

};


class Robot
{
private:
    int number;
public:
    //Constructor   
    Robot(){
        cout<<"Robot Created"<<endl;
    };
    //Destructor
    ~Robot(){};

    //setter
    void setNum(const int& new_number){
        number=new_number;
    };
    //getter
    int getNum(){
        return number;
    };
    void Task(std::mutex& mutex1, std::mutex& mutex2, tool& tool1, tool& tool2){
        std::this_thread::sleep_for(std::chrono::seconds(5)); //Simulate the 1 second time to grab the tools
        lock(mutex1,mutex2);
        cout<<"Robot "<<this->getNum()<<" has "<<tool1.getName()<<" and "<<tool2.getName()<<", and is working"<<endl;
        std::this_thread::sleep_for(std::chrono::seconds(5)); //Simulate the Task going for 5 Seconds
        cout<<"Robot "<<this->getNum()<<" has finished working. "<<endl;
        mutex1.unlock();
        mutex2.unlock();
};
};






int main()
{
    std::mutex m0,m1,m2,m3,m4; //Creating mutexes for each tool

    tool tool0; //Creating Tool 1 for robots
    tool0.setName("tool0");
    tool tool1; //Creating Tool 2 for robots
    tool1.setName("tool1");
    tool tool2; //Creating Tool 3 for robots
    tool2.setName("tool2");
    tool tool3; //Creating Tool 4 for robots
    tool3.setName("tool3");
    tool tool4; //Creating Tool 5 for robots
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

    std::thread t1(&Robot::Task,&R0, ref(m0),ref(m4),ref(tool0),ref(tool4));// Starting Thread for Robot 1 to do Task 1
    std::thread t2(&Robot::Task,&R1, ref(m0),ref(m1),ref(tool0),ref(tool1));// Starting Thread for Robot 1 to do Task 1
    std::thread t3(&Robot::Task,&R2, ref(m1),ref(m2),ref(tool1),ref(tool2));// Starting Thread for Robot 1 to do Task 1
    std::thread t4(&Robot::Task,&R3, ref(m2),ref(m3),ref(tool2),ref(tool3));// Starting Thread for Robot 1 to do Task 1
    std::thread t5(&Robot::Task,&R4, ref(m3),ref(m4),ref(tool3),ref(tool4));// Starting Thread for Robot 1 to do Task 1


    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    cout<<"All Robots have finished";
};