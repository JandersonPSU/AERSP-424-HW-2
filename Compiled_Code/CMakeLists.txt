cmake_minimum_required(VERSION 3.10)
project(HW2)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)

# Add executables
add_executable(HW2_Q_1 HW2_Q_1.cpp)
add_executable(HW2_Q_2 HW2_Q_2.cpp)
add_executable(HW2_Q_3 HW2_Q_3.cpp)
add_executable(HW2_Q_4 HW2_Q_4.cpp)

# Link OpenCV for HW2_Q_4
set(OpenCV_DIR C:/Users/pbach/Downloads/opencv/build)
find_package(OpenCV REQUIRED)
target_link_libraries(HW2_Q_4 ${OpenCV_LIBS})
