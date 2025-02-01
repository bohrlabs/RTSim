cmake_minimum_required(VERSION 3.17)
project(MyFirstPlugin)

set(CMAKE_CXX_STANDARD 20) 

include_directories(../../include) 

add_library(MyFirstPlugin SHARED 
src/MyFirstPlugin.cpp
src/MyFirstPlugin.h)

target_link_libraries(MyFirstPlugin Engine)