#pragma once
#include "Engine/Core.h"

namespace PluginSystem {
    class PluginLoader {
      public:
        using PluginHandle = void *; // Public type alias for cross-class access

      private:
        std::unordered_map<std::string, PluginHandle> m_LoadedPlugins;

      public:
        PluginLoader();
        ~PluginLoader();

        PluginHandle Load(const std::filesystem::path &pluginPath);
        void         Unload(PluginHandle handle);

        template<typename T>
        T GetSymbol(PluginHandle handle, const std::string &symbolName);
    };

} // namespace PluginSystem