#pragma once
#include <string>
#include <map>
#include <mutex>
#include <vector>
namespace Engine {



    class ThreadMonitor {
    private:
        struct ThreadStats {
            std::vector<double> CycleTimes;
        };

        std::map<std::string, ThreadStats> m_ThreadData;
        std::mutex m_DataMutex;
        bool m_Running = true;
        const int m_MaxHistory = 10;
        const int m_GraphWidth = 40;

        void RenderGraph(const std::string& name, const std::vector<double>& data);

        void DisplayLoop();

        std::string Bar(double averageTime, double maxTime) const;

    public:

        ThreadMonitor();

        ~ThreadMonitor() {
            m_Running = false;
        }

        void LogCycle(const std::string& threadName, double cycleTime);
    };
} // namespace Engine