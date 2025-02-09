
#pragma once

#include <cstdint>
#include <mutex>
#include <random>
#include <string>

namespace Utils {
    // Generate UUID as a hex string (e.g., "A1B2C3D4")
    std::string GenerateUUIDString();

    // Generate 32-bit UUID (from 8 hex characters)
    uint32_t GenerateUUID32();

    // Generate 64-bit UUID (from 16 hex characters)
    uint64_t GenerateUUID64();

    // Base class for automatic UUID generation
    class UUIDOwner {
      public:
        UUIDOwner();

        uint32_t GetUUID32() const {
            return m_UUID32;
        }
        uint64_t GetUUID64() const {
            return m_UUID64;
        }
        const std::string &GetUUIDString() const {
            return m_UUIDStr;
        }

      private:
        uint32_t    m_UUID32;
        uint64_t    m_UUID64;
        std::string m_UUIDStr;
    };
} // namespace Utils
