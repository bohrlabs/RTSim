#pragma once


#include <memory>
#include <string>



#ifdef _WIN32
#    define MY_PLUGIN_API __declspec(dllexport)
#else
#    define MY_PLUGIN_API
#endif


