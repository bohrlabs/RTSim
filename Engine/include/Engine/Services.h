#pragma once
#include "Engine/Core.h"
#include "Plugin/IPlugin.h"

namespace PluginSystem {

    class Services: public Plugin::IServices {
      public:
        Services()          = default;
        virtual ~Services() = default;

      private:
        std::map<std::string, void *> m_Services;
        std::map<std::string, void *> m_Ports;

        // Inherited via IServices
        void InternalCreateInputPort(const std::string &name, void **ppData, size_t dataSize) override;
        void InternalCreateOutputPort(const std::string &name, void *pData, size_t dataSize) override;
        void InternalRegisterProperty(const std::string &name, void *pData, size_t dataSize, size_t typeHash) override;

        Plugin::IProperty *GetProperty(const std::string &name) override;
    };

} // namespace PluginSystem
