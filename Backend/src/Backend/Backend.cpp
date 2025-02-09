
#include "Engine/Application.h"
#include "Engine/EntryPoint.h"

namespace RTSim {
    class Backend: public Engine::Application {
      public:
        Backend(const Engine::ApplicationSpecification &specs)
            : Application(specs) {
            //PushLayer(std::make_unique<RTSim::Layer>());
        }

        virtual void PostStart() override {

            Application::Get().CreateThread("backend user thread", []() {
                std::this_thread::sleep_for(std::chrono::milliseconds(10 + rand() % 20));
            });
        }
    };

} // namespace RTSim

Engine::Application *Engine::Application::CreateApplication(Engine::ApplicationCommandLineArgs args) {
    Engine::ApplicationSpecification spec;
    spec.Name            = "RTSim Backend";
    spec.CommandLineArgs = args;
    m_Instance           = std::make_unique<RTSim::Backend>(spec);
    return m_Instance.get();
}
