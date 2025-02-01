#include "Engine/EntryPoint.h"

#include "Engine/Application.h"

namespace RTSim {
    class Frontend : public Engine::Application {
    public:
        Frontend(const Engine::ApplicationSpecification& specs)
            : Application(specs) {
            //PushLayer(std::make_unique<RTSim::Layer>());
        }
    };


} // namespace RTSim






Engine::Application* Engine::Application::CreateApplication(Engine::ApplicationCommandLineArgs args)
{
    Engine::ApplicationSpecification spec;
    spec.Name = "RTSim Frontend";
    spec.CommandLineArgs = args;
    m_Instance  = std::make_unique<RTSim::Frontend>(spec);
    return m_Instance.get();


}

