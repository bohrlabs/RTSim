#include "Engine/Services.h"
namespace PluginSystem {

    Plugin::IProperty *Services::GetProperty(const std::string &name) {
        return nullptr;
    }

    void Services::InternalCreateInputPort(const std::string &name, void **ppData, size_t dataSize) {
    }

    void Services::InternalCreateOutputPort(const std::string &name, void *pData, size_t dataSize) {
    }

    void Services::InternalRegisterProperty(const std::string &name, void *pData, size_t dataSize, size_t typeHash) {
    }

} // namespace PluginSystem