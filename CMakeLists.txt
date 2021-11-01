cmake_minimum_required(VERSION 3.5)
set(PROJECT_NAME cpp_snake_example)
project(${PROJECT_NAME})

# C++ standard
set(CMAKE_CXX_STANDARD 14)


#using submodules
find_package(OpenCV 4 REQUIRED)  

include_directories(
    include/
    ${OpenCV_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_main src/main.cpp)
target_link_libraries(${PROJECT_NAME}_main ${OpenCV_LIBS})

