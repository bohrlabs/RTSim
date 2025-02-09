// Utils.cpp
#include "Engine/Utils/UUID.h"
#include <stdexcept>

namespace Utils {
    namespace {
        std::mutex                      g_RngMutex;
        std::random_device              g_Rd;
        std::mt19937                    g_Gen(g_Rd());
        std::uniform_int_distribution<> g_Dis(0, 15);
        const char                     *g_HexChars = "0123456789ABCDEF";
    } // namespace

    std::string GenerateUUIDString() {
        std::lock_guard<std::mutex> lock(g_RngMutex);
        std::string                 uuid;
        for (int i = 0; i < 8; ++i) {
            uuid += g_HexChars[g_Dis(g_Gen)];
        }
        return uuid;
    }

    uint32_t GenerateUUID32() {
        std::lock_guard<std::mutex> lock(g_RngMutex);
        uint32_t                    uuid = 0;
        for (int i = 0; i < 8; ++i) {
            uuid = (uuid << 4) | g_Dis(g_Gen);
        }
        return uuid;
    }

    uint64_t GenerateUUID64() {
        std::lock_guard<std::mutex> lock(g_RngMutex);
        uint64_t                    uuid = 0;
        for (int i = 0; i < 16; ++i) {
            uuid = (uuid << 4) | g_Dis(g_Gen);
        }
        return uuid;
    }

    UUIDOwner::UUIDOwner()
        : m_UUID32(GenerateUUID32()),
          m_UUID64(GenerateUUID64()),
          m_UUIDStr(GenerateUUIDString()) {
    }
} // namespace Utils

