#include "Engine/Application.h"
#include <chrono>

namespace Engine {
    Application::Application(const ApplicationSpecification &specs)
        : m_ThreadManager(std::thread::hardware_concurrency(), m_ThreadMonitor) {
        m_LayerStack = std::make_unique<LayerStack>();
    }

    Application::~Application() {
        Shutdown();
    }

    void Application::Run() {

        m_Running = true;
        while (m_Running) {
            auto now = std::chrono::high_resolution_clock::now();

            float frameTimeMilli = std::chrono::duration<float, std::milli>(now - m_LastFrameTime).count();
            m_LastFrameTime      = now;
            m_ThreadMonitor.LogCycle("Main Thread", frameTimeMilli);
            for (auto &layer : *m_LayerStack) {
                layer->OnUpdate(frameTimeMilli);
            }
        }
    }

    void Application::Shutdown() {
        m_Running = false;
        m_ThreadManager.Shutdown();
    }

    void Application::PushLayer(std::unique_ptr<ILayer> layer) {
        m_LayerStack->PushLayer(std::move(layer));
    }

    std::unique_ptr<Application> Application::m_Instance = nullptr; // Define it

} // namespace Engine
