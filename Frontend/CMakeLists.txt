cmake_minimum_required(VERSION 3.17)
include(../cmake/folder_structure.cmake)
project(Frontend)

set(CMAKE_CXX_STANDARD 20)

file (GLOB_RECURSE src_files
"src/Frontend/*.cpp"
"src/Frontend/*.h"
)

add_executable(Frontend)
target_sources (Frontend PRIVATE ${src_files})

target_link_libraries(Frontend Engine)

# target_include_directories(Frontend
#   PRIVATE
#   "src"
# )

# Generate Visual Studio project files
if(MSVC)
  set(CMAKE_GENERATOR "Visual Studio 17 2022") 
endif()

organize_sources(Frontend)