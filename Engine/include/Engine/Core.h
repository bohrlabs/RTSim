#pragma once
#include <string>

#include <filesystem>
#include <iostream>
#include <map>
#include <unordered_map>
#include <memory>
#include <string>
#include <vector>
#include <mutex>



namespace fs = std::filesystem;



#ifdef _WIN32
#    define MY_PLUGIN_API __declspec(dllexport)
#else
#    define MY_PLUGIN_API
#endif
