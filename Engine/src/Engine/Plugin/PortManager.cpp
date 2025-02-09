#include "Engine/Plugin/PortManager.h"

namespace PluginSystem {
    void PortManager::RegisterOutput(
        const std::string &fullName,
        void              *pData,
        const std::string &type) {
        m_OutputPorts[fullName] = {pData, type};
    }

    void PortManager::RegisterInput(
        const std::string &fullName,
        void             **ppData,
        const std::string &type) {
        m_InputPorts[fullName] = {ppData, type};
    }

    void PortManager::Connect(
        const std::string &outputName,
        const std::string &inputName) {
        auto &output = m_OutputPorts.at(outputName);
        auto &input  = m_InputPorts.at(inputName);

        if (output.type != input.type) {
            throw std::runtime_error("Type mismatch between ports");
        }

        *input.ppData = output.pData;
    }
} // namespace PluginSystem