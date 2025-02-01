#include "Engine/PlatformAbstraction.h"

#ifdef _WIN32
#include <windows.h>

class WindowsLibrary : public PlatformLibrary {
private:
    HMODULE m_libraryHandle = nullptr;

public:
    bool Load(const std::string& path) override {
        m_libraryHandle = LoadLibraryA(path.c_str());
        if (!m_libraryHandle) {
            std::cerr << "Failed to load library: " << path << std::endl;
            return false;
        }
        return true;
    }

    void* GetFunction(const std::string& functionName) override {
        if (!m_libraryHandle) return nullptr;
        return reinterpret_cast<void*>(GetProcAddress(m_libraryHandle, functionName.c_str()));
    }

    void Unload() override {
        if (m_libraryHandle) {
            FreeLibrary(m_libraryHandle);
            m_libraryHandle = nullptr;
        }
    }

    ~WindowsLibrary() override {
        Unload();
    }
};

#else
#include <dlfcn.h>

class LinuxLibrary : public PlatformLibrary {
private:
    void* m_libraryHandle = nullptr;

public:
    bool Load(const std::string& path) override {
        m_libraryHandle = dlopen(path.c_str(), RTLD_LAZY);
        if (!m_libraryHandle) {
            std::cerr << "Failed to load library: " << path << "\n" << dlerror() << std::endl;
            return false;
        }
        return true;
    }

    void* GetFunction(const std::string& functionName) override {
        if (!m_libraryHandle) return nullptr;
        return dlsym(m_libraryHandle, functionName.c_str());
    }

    void Unload() override {
        if (m_libraryHandle) {
            dlclose(m_libraryHandle);
            m_libraryHandle = nullptr;
        }
    }

    ~LinuxLibrary() override {
        Unload();
    }
};

#endif

std::unique_ptr<PlatformLibrary> PlatformLibrary::Create() {
#ifdef _WIN32
    return std::make_unique<WindowsLibrary>();
#else
    return std::make_unique<LinuxLibrary>();
#endif
}