
#pragma once
#include "Plugin/IPlugin.h"
#include "SharedMemory.h" // Your shared memory manager

namespace PluginSystem {
    class FrameworkServices: public Plugin::IServices {
      private:
        SharedMemory &m_SharedMemory;

      protected:
        void InternalRegisterProperty(
            const std::string &name,
            void              *pData,
            size_t             dataSize,
            size_t             typeHash) override {
            // Allocate shared memory and copy initial value
            void *pSharedMem = m_SharedMemory.Allocate(name, dataSize);
            memcpy(pSharedMem, pData, dataSize);

            // Create a framework-managed property
            m_Properties[name] = std::make_unique<Plugin::Property<T>>(
                static_cast<T *>(pSharedMem));
        }

      public:
        FrameworkServices(SharedMemory &sharedMem)
            : m_SharedMemory(sharedMem) {
        }
    };
} // namespace PluginSystem