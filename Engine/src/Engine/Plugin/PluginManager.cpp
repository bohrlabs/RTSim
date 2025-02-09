
#include "Engine/Plugin/PluginManager.h"
#include "Engine/PlatformAbstraction.h"
#include "Engine/Utils/Utils.h"


namespace PluginSystem {


    fs::path PluginManager::CopyPluginToTemp(const fs::path &originalPath) {
        const std::string uuid    = Utils::GenerateUUIDString();
        const fs::path    tempDir = fs::temp_directory_path() / "RTsim_plugins";
        fs::create_directories(tempDir);

        const std::string newName =
            originalPath.stem().string() + "_" + uuid + originalPath.extension().string();
        const auto targetPath = tempDir / newName;

        try {
            fs::copy(originalPath, targetPath);
        } catch (const std::exception &e) {
            throw std::runtime_error("Failed to copy plugin: " + std::string(e.what()));
        }

        return targetPath;
    }

    PluginManager::~PluginManager() {
        UnloadAllPlugins();
    }

    void PluginManager::LoadPlugin(const fs::path &pluginPath) {
        std::lock_guard<std::mutex> lock(m_InstanceMutex);

        PluginInstance instance;
        instance.CopiedDllPath = CopyPluginToTemp(pluginPath);
        instance.Handle        = m_Loader.Load(instance.CopiedDllPath);

        auto createFunc = m_Loader.GetSymbol<CreatePluginFunction>(instance.Handle, "CreatePlugin");
        if (!createFunc) {
            throw std::runtime_error("Plugin is missing CreatePlugin symbol: " + pluginPath.string());
        }

        instance.Plugin.reset(createFunc());
        m_Instances.push_back(std::move(instance));
    }

    void PluginManager::UnloadAllPlugins() {
        std::lock_guard<std::mutex> lock(m_InstanceMutex);
        for (auto &instance : m_Instances) {
            if (instance.Plugin) {
                instance.Plugin->Shutdown();
                instance.Plugin.reset();
            }
            m_Loader.Unload(instance.Handle);
            fs::remove(instance.CopiedDllPath);
        }
        m_Instances.clear();
    }

    void PluginManager::UpdatePlugins(float deltaTime) {
        std::lock_guard<std::mutex> lock(m_InstanceMutex);
        for (auto &instance : m_Instances) {
            if (instance.Plugin) {
                instance.Plugin->Process(deltaTime);
            }
        }
    }

    //const std::vector<std::string> &PluginManager::GetProvidedPorts() const {
    //    // This method needs to be implemented to retrieve the list of provided ports from all loaded plugins
    //    // (This might require modifications to the plugin interface and loading logic)
    //    static std::vector<std::string> emptyVector;
    //    return emptyVector;
    //}

    //const std::vector<std::string> &PluginManager::GetRequiredServices() const {
    //    // This method needs to be implemented to retrieve the list of required services from all loaded plugins
    //    static std::vector<std::string> emptyVector;
    //    return emptyVector;
    //}

} // namespace PluginSystem
