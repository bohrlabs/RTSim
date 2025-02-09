
#include "Engine/Plugin/PluginManager.h"
#include "Engine/PlatformAbstraction.h"
namespace Engine {

    bool PluginManager::LoadPlugin(const fs::path &pluginPath) {
        auto library = PlatformLibrary::Create();

        if (!library->Load(pluginPath.string())) {
            return false;
        }

        // Get function pointer to CreatePlugin function
        CreatePluginFunction CreatePluginFunc =
            reinterpret_cast<CreatePluginFunction>(library->GetFunction("CreatePlugin"));

        if (!CreatePluginFunc) {
            std::cerr << "Failed to find CreatePlugin function in " << pluginPath << std::endl;
            return false;
        }

        // Create an instance of the plugin
        std::unique_ptr<Plugin::IPlugin> plugin(CreatePluginFunc());

        if (!plugin) {
            std::cerr << "Failed to create plugin instance" << std::endl;
            return false;
        }

        // Initialize the plugin
        std::unique_ptr<Plugin::IServices> service = std::make_unique<Services>();
        if (service.get() != nullptr) {
            m_Services[plugin->GetName()] = std::move(service);
            Plugin::IServices *servicePtr = m_Services[plugin->GetName()].get();
            if ((servicePtr) && (!plugin->Initialize(*servicePtr))) {
                std::cerr << "Plugin initialization failed" << std::endl;
                return false;
            }
        }
        // store the plugin in the map
        m_Plugins.push_back(std::move(plugin));
        return true;
    }

    void PluginManager::UnloadPlugins() {
        for (auto &plugin : m_Plugins) {
            plugin->Shutdown();
        }
        m_Plugins.clear();
    }

    void PluginManager::UpdateAllPlugins(float deltaTime) {
        for (const auto &plugin : m_Plugins) {
            plugin->Update(deltaTime);
        }
    }

    const std::vector<std::string> &PluginManager::GetProvidedPorts() const {
        // This method needs to be implemented to retrieve the list of provided ports from all loaded plugins
        // (This might require modifications to the plugin interface and loading logic)
        static std::vector<std::string> emptyVector;
        return emptyVector;
    }

    const std::vector<std::string> &PluginManager::GetRequiredServices() const {
        // This method needs to be implemented to retrieve the list of required services from all loaded plugins
        static std::vector<std::string> emptyVector;
        return emptyVector;
    }

} // namespace Engine
