cmake_minimum_required(VERSION 3.17)

project(Backend)

set(CMAKE_CXX_STANDARD 20)

file (GLOB_RECURSE src_files
"src/Backend/*.cpp"
"src/Backend/*.h"
)

add_executable(Backend)
target_sources(Backend PRIVATE ${src_files})

target_link_libraries(Backend Engine)

# Generate Visual Studio project files
if(MSVC)
  set(CMAKE_GENERATOR "Visual Studio 17 2022")
endif()