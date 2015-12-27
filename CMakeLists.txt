
cmake_minimum_required(VERSION 2.8.9)

project(EventManager C CXX)

include_directories(include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

#set(SOURCES src/main.cpp)
file(GLOB SOURCES "src/*.cpp")
add_executable(EventManager ${SOURCES})

