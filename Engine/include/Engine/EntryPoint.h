#pragma once

#include "Engine/Core.h"    
#include "Engine/Application.h"



//extern std::unique_ptr<Engine::Application> Engine::CreateApplication(Engine::ApplicationCommandLineArgs args);
//#include "Engine/ThreadMonitor.h"
//
//#include <thread>
//#include <chrono>
//#include <string>
//using namespace std;
//using namespace chrono;
//
//// Example worker function
//static void worker(ThreadMonitor& monitor, const std::string& name) {
//    while (true) {
//
//        auto start = high_resolution_clock::now();
//
//        std::this_thread::sleep_for(milliseconds(10 + rand() % 20));  // Simulate work
//
//        auto end = std::chrono::high_resolution_clock::now();
//        double cycle_time = duration<double, milli>(end - start).count();
//
//        monitor.LogCycle(name, cycle_time);
//    }
//}


//int main(int argc, char** argv) {
//    srand(time(nullptr));
//    ThreadMonitor monitor;
//
//    std::thread t1(worker, ref(monitor), "Thread 1");
//    std::thread t2(worker, ref(monitor), "Thread 2");
//
//    t1.join();
//    t2.join();
//}


#if 1
int main(int argc, char** argv) {
    //Engine::Log::Init();

    Engine::ApplicationCommandLineArgs specification = { argc, argv };

    Engine::Application;

    auto application = Engine::Application::CreateApplication(specification);
    application->PostStart();
    application->Run();

    delete application;

    return 0;
}

#endif
