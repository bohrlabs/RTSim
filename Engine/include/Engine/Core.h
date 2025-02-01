#pragma once
#include <string>


#include <vector>
#include <memory>
#include <string>
#include <map>
#include <filesystem>
#include <iostream>


namespace fs = std::filesystem;


void TestFunction();

#ifdef _WIN32
#define MY_PLUGIN_API __declspec(dllexport)
#else
#define MY_PLUGIN_API 
#endif

