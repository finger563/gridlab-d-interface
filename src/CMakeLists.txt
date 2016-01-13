cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

SET(execName gridlabd_interface)

project(${execName})

## Check C++11 / C++0x
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "-std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "-std=c++0x")
else()
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

add_subdirectory(cpr)

include_directories(${CPR_INCLUDE_DIRS})

# add interface executable
add_executable (${execName} main.cpp)
target_link_libraries(${execName} ${CPR_LIBRARIES})

# add market scheduler executable
add_executable (market market.cpp)
#target_link_libraries(market ${CPR_LIBRARIES})

# add demand scheduler executable
add_executable (demand demand.cpp)
#target_link_libraries(demand ${CPR_LIBRARIES})
