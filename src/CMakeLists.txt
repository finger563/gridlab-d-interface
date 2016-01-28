cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

SET(execName gridlabd_interface)

project(${execName})

set ( CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH};./cpp-netlib-build )
find_package ( cppnetlib 0.11.0 REQUIRED )

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

include_directories(${CPPNETLIB_INCLUDE_DIRS})

# add interface executable
add_executable (${execName} main.cpp)
target_link_libraries(${execName} ${CPPNETLIB_LIBRARIES})

# add market scheduler executable
add_executable (market market.cpp)

# add demand scheduler executable
add_executable (demand demand.cpp)
