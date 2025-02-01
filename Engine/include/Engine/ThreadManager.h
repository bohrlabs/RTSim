#pragma once

#include "ThreadMonitor.h"

#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <map>
#include <functional>
#include <atomic>
#include <string>

namespace Engine {

    class ThreadManager {
    private:
        // Thread Pool
        std::vector<std::jthread> m_ThreadPool;
        std::queue<std::function<void()>> m_TaskQueue;
        std::mutex m_QueueMutex;
        std::condition_variable m_TaskNotifier;
        std::atomic<bool> m_StopThreads = false;

        // Named Threads
        std::map<std::string, std::jthread> m_NamedThreads;
        std::mutex m_NamedThreadMutex;
        ThreadMonitor& m_Monitor;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_LastFrameTime;
        void WorkerThread();

    public:
        ThreadManager(size_t numThreads, ThreadMonitor& monitor);
        ~ThreadManager();

        void EnqueueTask(std::function<void()> func);
        void CreateThread(const std::string& name, std::function<void()> func);
        void Shutdown();
    };

} // namespace Engine
