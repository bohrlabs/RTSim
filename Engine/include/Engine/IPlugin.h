#pragma once

#include "Core.h" 


namespace Plugin
{
    class IServices
    {
    public:
        IServices() = default;
        virtual ~IServices() = 0;
        virtual void RegisterService(const std::string& name, void* service) = 0;
        virtual void* GetService(const std::string& name) = 0;
        virtual void CreatePort(const std::string& name, void* port) = 0;
        virtual void* GetPort(const std::string& name) = 0;
        virtual void CreateConfigProperty(const std::string& name, void* configProperty) = 0;
    };


    class IPlugin
    {
    public:
        IPlugin() = default;
        virtual ~IPlugin() {};
        virtual bool Initialize(IServices& services) = 0;
        virtual void Update(float deltaTime) = 0;
        virtual void Shutdown() = 0;
    public:

        // Algorithm part
        virtual void Start() = 0;
        virtual void Stop() = 0;
        virtual void Process(float deltaTime) = 0;


    public:

        // Getters for plugin information
        virtual const std::string& GetName() const = 0;
        virtual const std::string& GetVersion() const = 0;
    };
} // namespace Plugin


// Function pointer for CreatePlugin function (used for dynamic loading)
typedef Plugin::IPlugin* (*CreatePluginFunction)();
