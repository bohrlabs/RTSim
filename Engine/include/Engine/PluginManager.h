#pragma once
#include "Engine/Core.h"
#include "IPlugin.h"
#include "Services.h"



class PluginManager {
public:
    bool LoadPlugin(const fs::path& pluginPath);
    void UnloadPlugins();
    void UpdateAllPlugins(float deltaTime);

    // Getters for plugin information
    const std::vector<std::string>& GetProvidedPorts() const;
    const std::vector<std::string>& GetRequiredServices() const;

private:
    std::vector<std::unique_ptr<Plugin::IPlugin>> m_plugins;
    std::map<std::string, void*> m_ports; // Store registered ports
    std::map<std::string, std::unique_ptr<Plugin::IServices>> m_services; // Store registered services 
};

