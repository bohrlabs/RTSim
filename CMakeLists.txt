cmake_minimum_required(VERSION 3.17)

project(RTSim)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add subdirectories
add_subdirectory(Engine)   # Engine library
add_subdirectory(Frontend) # Frontend application
add_subdirectory(Backend)  # Backend application

# Uncomment this if you have tests
# add_subdirectory(tests)

add_subdirectory(Plugins)

