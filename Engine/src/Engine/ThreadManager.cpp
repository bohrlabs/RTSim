#include "Engine/ThreadManager.h"
#include <iostream>

namespace Engine {
    ThreadManager::ThreadManager(size_t numThreads, ThreadMonitor &monitor)
        : m_Monitor(monitor) {
        for (size_t i = 0; i < numThreads; ++i) {
            m_ThreadPool.emplace_back(&ThreadManager::WorkerThread, this);
        }
    }

    ThreadManager::~ThreadManager() {
        Shutdown();
    }

    void ThreadManager::WorkerThread() {
        while (!m_StopThreads) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(m_QueueMutex);
                m_TaskNotifier.wait(lock, [this] { return !m_TaskQueue.empty() || m_StopThreads; });

                if (m_StopThreads && m_TaskQueue.empty()) return;

                task = std::move(m_TaskQueue.front());
                m_TaskQueue.pop();
            }
            task(); // Execute task
        }
    }

    void ThreadManager::EnqueueTask(std::function<void()> func) {
        {
            std::lock_guard<std::mutex> lock(m_QueueMutex);
            m_TaskQueue.push(std::move(func));
        }
        m_TaskNotifier.notify_one();
    }

    void ThreadManager::CreateThread(const std::string &name, std::function<void()> func) {
        std::lock_guard<std::mutex> lock(m_NamedThreadMutex);

        if (m_NamedThreads.contains(name)) {
            std::cerr << "Thread " << name << " already exists!\n";
            return;
        }

        m_NamedThreads[name] = std::jthread([this, name, func]() {
            while (not m_StopThreads) {
                auto start = std::chrono::high_resolution_clock::now();
                func();
                auto  end            = std::chrono::high_resolution_clock::now();
                float frameTimeMilli = std::chrono::duration<float, std::milli>(end - start).count();
                m_Monitor.LogCycle(name, frameTimeMilli);
            }
        });
    }

    void ThreadManager::Shutdown() {
        m_StopThreads = true;
        m_TaskNotifier.notify_all();

        for (auto &thread : m_ThreadPool) {
            if (thread.joinable()) thread.join();
        }

        std::lock_guard<std::mutex> lock(m_NamedThreadMutex);
        m_NamedThreads.clear();
    }
} // namespace Engine
