// This is the code for AERSP 424 HW 2 Question 2 for Jack A, Peter B, and Sean

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;



//class for the tool
class tool{
private:
    string name; //variable for tool name
public:


    //Constructor
    tool(){
        cout<<"Tool Created"<<endl; //Outputing Tool creation
    };
    //Destructor
    ~tool(){};
    //setter
    void setName(const string& new_name){
        name=new_name; //setting the name of the tool
    };
    //getter
    string getName(){
        return name; //returning the name to the call
    };

};

//Robot Class
class Robot
{
private:
    int number; //variable for robot number
public:
    //Constructor   
    Robot(){
        cout<<"Robot Created"<<endl; //outputting robot creation
    };
    //Destructor
    ~Robot(){}; 

    //setter
    void setNum(const int& new_number){
        number=new_number; //setting the robot number
    };
    //getter
    int getNum(){
        return number; //returning the robot number to the call
    };
    //function for the task that takes in 2 mutexes to lock resources and the two tools being used
    void Task(std::mutex& mutex1, std::mutex& mutex2, tool& tool1, tool& tool2){
        std::this_thread::sleep_for(std::chrono::seconds(5)); //Simulate the 1 second time to grab the tools
        lock(mutex1,mutex2); //locking resources (mutexes related to the tools)
        fprintf(stdout, "Robot %d has %s and %s, and is working\n", this->getNum(), tool1.getName().c_str(), tool2.getName().c_str()); //outputting that the robot is working with the given tools
        std::this_thread::sleep_for(std::chrono::seconds(5)); //Simulate the Task going for 5 Seconds
        fprintf(stdout, "Robot %d has finished working.\n", this->getNum()); //outputting that the task is ended
        mutex1.unlock(); //unlocking mutex 1
        mutex2.unlock(); //unlocking mutex 2
};
};






int main()
{
    std::mutex m0,m1,m2,m3,m4; //Creating mutexes for each tool

    tool tool0; //Creating Tool 1 for robots
    tool0.setName("tool0"); //setting name for tool0
    tool tool1; //Creating Tool 2 for robots
    tool1.setName("tool1");//setting name for tool1
    tool tool2; //Creating Tool 3 for robots
    tool2.setName("tool2");//setting name for tool2
    tool tool3; //Creating Tool 4 for robots
    tool3.setName("tool3");//setting name for tool3
    tool tool4; //Creating Tool 5 for robots
    tool4.setName("tool4");//setting name for tool4
    //creating and numbering robot 0
    Robot R0; 
    R0.setNum(0);
    //creating and numbering robot 1
    Robot R1;
    R1.setNum(1);
    //creating and numbering robot 2
    Robot R2;
    R2.setNum(2);
    //creating and numbering robot 3
    Robot R3;
    R3.setNum(3);
    //creating and numbering robot 4
    Robot R4;
    R4.setNum(4);

    //Threads
    std::thread t1(&Robot::Task,&R0, ref(m0),ref(m4),ref(tool0),ref(tool4));// Starting Thread for Robot 0 to do Task 
    std::thread t2(&Robot::Task,&R1, ref(m0),ref(m1),ref(tool0),ref(tool1));// Starting Thread for Robot 1 to do Task 
    std::thread t3(&Robot::Task,&R2, ref(m1),ref(m2),ref(tool1),ref(tool2));// Starting Thread for Robot 2 to do Task 
    std::thread t4(&Robot::Task,&R3, ref(m2),ref(m3),ref(tool2),ref(tool3));// Starting Thread for Robot 3 to do Task 
    std::thread t5(&Robot::Task,&R4, ref(m3),ref(m4),ref(tool3),ref(tool4));// Starting Thread for Robot 4 to do Task 

    //Joining Threads
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    //Final output stating finished condition
    cout<<"All Robots have finished";
};