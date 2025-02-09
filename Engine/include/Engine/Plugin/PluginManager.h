#pragma once
#include "Engine/Core.h"

#include "Engine/Services.h"
#include "Plugin/IPlugin.h"
#include "PluginLoader.h"

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

        fs::path CopyPluginToTemp(const fs::path &originalPath);

      public:
        PluginManager() = default;
        ~PluginManager();

        void LoadPlugin(const fs::path &pluginPath);
        void UnloadAllPlugins();
        void UpdatePlugins(float deltaTime);
    };

} // namespace PluginSystem
