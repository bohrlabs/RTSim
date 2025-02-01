#include "MyFirstPlugin.h"
#include <iostream>


MyFirstPlugin::MyFirstPlugin() {
}

MyFirstPlugin::~MyFirstPlugin() {
}

bool MyFirstPlugin::Initialize(Plugin::IServices& services) {
    std::cout << "MyFirstPlugin: Initialized" << std::endl;

    // Example: Create a port 
    void* myPort = this; // Example: Pass 'this' as the port 
    services.CreatePort("MyFirstPluginPort", myPort);

    return true;
}

void MyFirstPlugin::Update(float deltaTime) {
    // Perform plugin logic here
    // ...
}

void MyFirstPlugin::Shutdown() {
    std::cout << "MyFirstPlugin: Shutting down" << std::endl;
}

const std::string& MyFirstPlugin::GetName() const {
    static const std::string name = "MyFirstPlugin";
    return name;
}

const std::string& MyFirstPlugin::GetVersion() const {
    static const std::string version = "1.0.0";
    return version;
}

void MyFirstPlugin::Start() {
}

void MyFirstPlugin::Stop() {
}

void MyFirstPlugin::Process(float deltaTime) {
}

// Define the CreatePlugin function with extern "C" linkage
extern "C"
{
    MY_PLUGIN_API Plugin::IPlugin* CreatePlugin() {
        return std::make_unique<MyFirstPlugin>().release();
        //MyFirstPlugin* myFirstPlugin = new MyFirstPlugin();
        //return reinterpret_cast<Plugin::IPlugin*>(myFirstPlugin);
        
    }
}