#pragma once
#include <string>

#include <filesystem>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace fs = std::filesystem;

void TestFunction();

#ifdef _WIN32
#    define MY_PLUGIN_API __declspec(dllexport)
#else
#    define MY_PLUGIN_API
#endif
