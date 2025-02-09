#include "Engine/Plugin/PluginLoader.h"
#include <stdexcept>

#ifdef _WIN32
#    include <windows.h>
#else
#    include <dlfcn.h>
#endif

namespace PluginSystem {
    PluginLoader::PluginLoader() = default;

    PluginLoader::~PluginLoader() {
        for (const auto &[path, handle] : m_LoadedPlugins) {
            Unload(handle);
        }
    }

    PluginLoader::PluginHandle PluginLoader::Load(const std::filesystem::path &pluginPath) {
#ifdef _WIN32
        PluginHandle handle = LoadLibraryW(pluginPath.c_str());
#else
        PluginHandle handle = dlopen(pluginPath.c_str(), RTLD_LAZY | RTLD_LOCAL);
#endif
        if (!handle) {
            throw std::runtime_error("Failed to load plugin: " + pluginPath.string());
        }
        m_LoadedPlugins[pluginPath.string()] = handle;
        return handle;
    }

    void PluginLoader::Unload(PluginHandle handle) {
        if (handle) {
#ifdef _WIN32
            FreeLibrary(static_cast<HMODULE>(handle));
#else
            dlclose(handle);
#endif
        }
    }

    template<typename T>
    T PluginLoader::GetSymbol(PluginHandle handle, const std::string &symbolName) {
#ifdef _WIN32
        return reinterpret_cast<T>(GetProcAddress(static_cast<HMODULE>(handle), symbolName.c_str()));
#else
        return reinterpret_cast<T>(dlsym(handle, symbolName.c_str()));
#endif
    }
} // namespace PluginSystem