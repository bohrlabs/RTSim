 #pragma once

#include "Engine/IPlugin.h"

class MyFirstPlugin : public Plugin::IPlugin
{
public:
    MyFirstPlugin();
    ~MyFirstPlugin() override;

    bool Initialize(Plugin::IServices& services) override;
    void Update(float deltaTime) override;
    void Shutdown() override;

    const std::string& GetName() const override;
    const std::string& GetVersion() const override;

    // Inherited via IPlugin
    void Start() override;
    void Stop() override;
    void Process(float deltaTime) override;
    /*
private:
    Plugin::IServices& m_services; 
    */
};

//// Declare the CreatePlugin function with extern "C" linkage
//extern "C" {
//    MY_PLUGIN_API Plugin::IPlugin* CreatePlugin();
//}