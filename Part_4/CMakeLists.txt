cmake_minimum_required(VERSION 3.10)

project(ObjectDetection)

set(OpenCV_DIR C:/Users/pbach/Downloads/opencv/build)
find_package(OpenCV REQUIRED)

add_executable(${PROJECT_NAME} src/Main.cpp)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

