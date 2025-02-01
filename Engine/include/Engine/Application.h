#pragma once


#include "Engine/Core.h"
#include "Engine/LayerStack.h"
#include "ThreadMonitor.h"
#include "ThreadManager.h"

#include <queue>
#include <functional>
#include <mutex>

int main(int argc, char** argv);


namespace Engine {
    struct ApplicationCommandLineArgs
    {
        int Count = 0;
        char** Args = nullptr;

        const char* operator[](int index) const {
            return Args[index];
        }
    };

    struct ApplicationSpecification
    {
        std::string Name = "RTSim Application";
        std::string WorkingDirectory;
        ApplicationCommandLineArgs CommandLineArgs;
    };


    class Application {
    private:
        static std::unique_ptr<Application> m_Instance;
        friend int ::main(int argc, char** argv);

    private:
        bool m_Running = true;
        std::unique_ptr<LayerStack> m_LayerStack;
        ThreadMonitor m_ThreadMonitor;
        ThreadManager m_ThreadManager;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_LastFrameTime;

    public:

        Application(const ApplicationSpecification& specs);
        virtual ~Application();
        void Run();
        void Shutdown();
        void PushLayer(std::unique_ptr<ILayer> layer);


        // Delegating thread operations to ThreadManager
        void EnqueueTask(std::function<void()> func) { m_ThreadManager.EnqueueTask(std::move(func)); }
        void CreateThread(const std::string& name, std::function<void()> func) { m_ThreadManager.CreateThread(name, std::move(func)); }


        virtual void PostStart() = 0;
        

    public:

        static Application* CreateApplication(const ApplicationCommandLineArgs args);

        static Application& Get() { return *(m_Instance.get()); }


    };



    //static Application* CreateApplication(const ApplicationCommandLineArgs args);



} // namespace Engine