cmake_minimum_required(VERSION 3.17)

project(Frontend)

set(CMAKE_CXX_STANDARD 20)

add_executable(Frontend)

target_sources (Frontend PRIVATE 
	src/Frontend/Frontend.cpp
)

target_link_libraries(Frontend Engine)

# Generate Visual Studio project files
if(MSVC)
  set(CMAKE_GENERATOR "Visual Studio 17 2022") 
endif()