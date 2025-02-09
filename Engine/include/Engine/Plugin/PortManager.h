
#pragma once
#include "Engine/Core.h"

namespace PluginSystem {
    struct OutputPort {
        void       *pData;
        std::string type;
    };

    struct InputPort {
        void      **ppData; // Pointer to the user's data pointer
        std::string type;
    };

    class PortManager {
      private:
        std::unordered_map<std::string, OutputPort> m_OutputPorts;
        std::unordered_map<std::string, InputPort>  m_InputPorts;

      public:
        void RegisterOutput(const std::string &fullName, void *pData, const std::string &type);
        void RegisterInput(const std::string &fullName, void **ppData, const std::string &type);
        void Connect(const std::string &outputName, const std::string &inputName);
    };
} // namespace PluginSystem