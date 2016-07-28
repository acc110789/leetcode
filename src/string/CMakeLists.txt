project(teststring)

cmake_minimum_required(VERSION 2.8.12)

set(CMAKE_AUTOMOC ON)
include(FeatureSummary)

add_definitions(-std=c++14)
option(ENABLE_DEBUG "Enable debug" OFF)
if(ENABLE_DEBUG)
    add_definitions(-g -DDEBUG)
endif()

find_package(Qt5 REQUIRED COMPONENTS Core)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

add_executable(teststring 
    teststring.cpp
)
target_link_libraries(teststring
    Qt5::Core
)

