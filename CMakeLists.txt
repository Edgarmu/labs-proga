cmake_minimum_required(VERSION 3.28)
project(LabEdgar)

set(CMAKE_CXX_STANDARD 20)

include_directories(include test include/matrices include/trees)

add_executable(unitTests unitTests.cpp)
add_executable(ui ui.cpp)
add_executable(perfomance perfomance.cpp)