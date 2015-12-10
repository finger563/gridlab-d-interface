cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

SET(execName gridlabd_interface)

project(${execName})

add_subdirectory(cpr)

include_directories(${CPR_INCLUDE_DIRS})

add_executable (${execName} main.cpp)

target_link_libraries(${execName} ${CPR_LIBRARIES})
