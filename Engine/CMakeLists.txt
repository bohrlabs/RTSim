cmake_minimum_required(VERSION 3.17)

project(Engine)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE ENGINE_SRC 
"src/*.cpp"
)
file(GLOB_RECURSE ENGINE_INC
"include/*.h"
)





# Add the Engine library
add_library(Engine STATIC 

	${ENGINE_SRC} 
	${ENGINE_INC} 
)

 target_include_directories(Engine PUBLIC include)

## Generate EngineConfig.cmake
#file(WRITE ${PROJECT_BINARY_DIR}/EngineConfig.cmake "
#  include(FindPackageHandleStandardArgs) 
#
#  find_package_handle_standard_args(Engine DEFAULT_MSG Engine_FOUND)
#
#  if(Engine_FOUND)
#      set(Engine_INCLUDE_DIRS ${PROJECT_BINARY_DIR}/include) 
#      set(Engine_LIBRARIES Engine) 
#  endif()
#")
#
## Install the Engine library and headers (optional)
#install(TARGETS Engine DESTINATION lib)
#install(FILES include/Engine/Engine.h 
#              #include/Engine/Logger.h 
#              #include/Engine/Threading.h 
#              #include/Engine/Platform.h 
#              #include/Engine/Configuration.h 
#              #include/Engine/IPlugin.h 
#        DESTINATION include)