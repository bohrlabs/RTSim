// Config.h
#pragma once
#include <string>
#include <unordered_map>
#include <vector>

namespace PluginSystem {
    struct PluginConfig {
        std::string                                  Name;
        std::string                                  Path;
        std::vector<std::string>                     InputPorts;
        std::vector<std::string>                     OutputPorts;
        std::unordered_map<std::string, std::string> Properties; // Serialized values
    };

    class ConfigManager {
      public:
        void LoadFromFile(const std::filesystem::path &configPath);

        const std::vector<PluginConfig> &GetPlugins() const {
            return m_Plugins;
        }

      private:
        std::vector<PluginConfig> m_Plugins;
    };
} // namespace PluginSystem