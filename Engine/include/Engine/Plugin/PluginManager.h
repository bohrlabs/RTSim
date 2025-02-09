#pragma once
#include "Engine/Core.h"

#include "Engine/Services.h"
#include "Plugin/IPlugin.h"
#include "PluginLoader.h"
#include "PortManager.h"
#include "Config.h"

namespace PluginSystem {

    struct PluginInstance {
        std::unique_ptr<Plugin::IPlugin> Plugin;
        fs::path                         CopiedDllPath;
        PluginLoader::PluginHandle       Handle;
    };

    class PluginManager {
      private:
        PluginLoader                m_Loader;
        std::vector<PluginInstance> m_Instances;
        std::mutex                  m_InstanceMutex;

      private:
        PortManager   m_PortManager;
        ConfigManager m_ConfigManager;


        fs::path CopyPluginToTemp(const fs::path &originalPath);

      public:
        PluginManager() = default;
        ~PluginManager();

        void LoadPlugin(const fs::path &pluginPath);
        void UnloadAllPlugins();
        void UpdatePlugins(float deltaTime);

         void LoadConfig(const std::filesystem::path &configPath);
    };

} // namespace PluginSystem
