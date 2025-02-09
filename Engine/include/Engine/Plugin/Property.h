#pragma once
#include "Plugin/IPlugin.h"
#include <sstream>

namespace Plugin {
    template<typename T>
    class Property: public IProperty {
      public:
        Property(T &value)
            : m_Value(value), m_TypeHash(typeid(T).hash_code()) {
        }

        void *GetData() override {
            return &m_Value;
        }
        size_t GetSize() const override {
            return sizeof(T);
        }
        size_t GetTypeHash() const override {
            return m_TypeHash;
        }

        std::string Serialize() const override {
            if constexpr (std::is_arithmetic_v<T>) {
                return std::to_string(m_Value);
            }
            // Add custom serialization for complex types
            return "";
        }

        void Deserialize(const std::string &value) override {
            if constexpr (std::is_arithmetic_v<T>) {
                if constexpr (std::is_integral_v<T>) {
                    m_Value = static_cast<T>(std::stoll(value));
                } else {
                    m_Value = static_cast<T>(std::stod(value));
                }
            }
        }

      private:
        T     &m_Value;
        size_t m_TypeHash;
    };
} // namespace Plugin