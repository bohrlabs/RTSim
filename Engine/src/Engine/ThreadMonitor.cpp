// ThreadMonitor.cpp
#include "Engine/ThreadMonitor.h"

#include <chrono>
#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <thread>

namespace Engine {

    void ThreadMonitor::RenderGraph(const std::string &name, const std::vector<double> &data) {

        if (data.empty()) return;

        double maxTime = *max_element(data.begin(), data.end());
        double minTime = *min_element(data.begin(), data.end());
        std::cout << name << ": \n";
        double averageTime = 0;
        for (double t : data) {
            averageTime += t;
        }
        averageTime /= data.size();

        std::cout << "Average: " << Bar(averageTime, maxTime) << " " << averageTime << "ms" << std::string(m_GraphWidth, ' ') << "\n";
        std::cout << "Max    : " << Bar(maxTime, maxTime) << " " << maxTime << "ms" << std::string(m_GraphWidth, ' ') << "\n";
        std::cout << "Min    : " << Bar(minTime, maxTime) << " " << minTime << "ms" << std::string(m_GraphWidth, ' ') << "\n";

        std::cout << "-------------------------\n";
    }

    void ThreadMonitor::DisplayLoop() {
        while (m_Running) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));

            std::lock_guard<std::mutex> lock(m_DataMutex);
#ifdef WIN32
            //system("cls");  // Windows: use "cls" on Windows
            std::cout << "\033[H"; // ANSI escape code to reset cursor position
#else
            system("clear"); // Windows: use "clear" on Linux
#endif
            for (const auto &[name, stats] : m_ThreadData) {
                RenderGraph(name, stats.CycleTimes);
            }
        }
    }

    std::string ThreadMonitor::Bar(double averageTime, double maxTime) const {
        unsigned int barLength = static_cast<int>((averageTime / maxTime) * m_GraphWidth);
        if (barLength > m_GraphWidth) barLength = m_GraphWidth;
        return std::string(barLength, '#');
    }

    ThreadMonitor::ThreadMonitor() {
        std::thread(&ThreadMonitor::DisplayLoop, this).detach();
    }

    void ThreadMonitor::LogCycle(const std::string &thread_name, double cycle_time) {
        std::lock_guard<std::mutex> lock(m_DataMutex);
        ThreadStats                &stats = m_ThreadData[thread_name];

        if (stats.CycleTimes.size() >= m_MaxHistory) {
            stats.CycleTimes.erase(stats.CycleTimes.begin());
        }
        stats.CycleTimes.push_back(cycle_time);
    }
} // namespace Engine