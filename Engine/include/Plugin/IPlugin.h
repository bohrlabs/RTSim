#pragma once

#include "PluginCommon.h" // Ensure this includes necessary headers (e.g., <string>, <unordered_map>)

namespace Plugin {
    //====================================================
    // Forward Declarations
    //====================================================
    class IProperty;

    //====================================================
    // Interfaces
    //====================================================
    class IServices {
      public:
        virtual ~IServices() = 0;

        //------------------------------------------------
        // Port Management (User-friendly APIs)
        //------------------------------------------------
        template<typename T>
        void CreateInputPort(const std::string &name, T **ppPort) {
            InternalCreateInputPort(name, reinterpret_cast<void **>(ppPort), sizeof(T));
        }

        template<typename T>
        void CreateOutputPort(const std::string &name, T *pPort) {
            InternalCreateOutputPort(name, reinterpret_cast<void *>(pPort), sizeof(T));
        }

        //------------------------------------------------
        // Property Management
        //------------------------------------------------
        template<typename T>
        void RegisterProperty(const std::string &name, T &value) {
            static_assert(std::is_trivially_copyable_v<T>, "Port type must be trivially copyable");
            InternalRegisterProperty(name, &value, sizeof(T), typeid(T).hash_code());
        }

        virtual IProperty *GetProperty(const std::string &name) = 0;

      protected:
        // Framework implementations (pure virtual)
        virtual void InternalCreateInputPort(
            const std::string &name,
            void             **ppData,
            size_t             dataSize) = 0;

        virtual void InternalCreateOutputPort(
            const std::string &name,
            void              *pData,
            size_t             dataSize) = 0;

        virtual void InternalRegisterProperty(
            const std::string &name,
            void              *pData,
            size_t             dataSize,
            size_t             typeHash) = 0;

        // Member variables (m_ prefix, camelCase)
        std::unordered_map<std::string, std::unique_ptr<IProperty>> m_Properties;
    };

    //====================================================
    // Property Interface
    //====================================================
    class IProperty {
      public:
        virtual ~IProperty() = default;

        // Core methods
        virtual void  *GetData()           = 0;
        virtual size_t GetSize() const     = 0;
        virtual size_t GetTypeHash() const = 0;

        // Serialization
        virtual std::string Serialize() const                     = 0;
        virtual void        Deserialize(const std::string &value) = 0;
    };

    //====================================================
    // Plugin Interface
    //====================================================
    class IPlugin {
      public:
        virtual ~IPlugin() = default;

        // Lifecycle
        virtual bool Initialize(IServices &services) = 0;
        virtual void Shutdown()                      = 0;

        // Execution Control
        virtual void Start()                  = 0;
        virtual void Stop()                   = 0;
        virtual void Process(float deltaTime) = 0;

        // Metadata
        virtual const std::string &GetName() const    = 0;
        virtual const std::string &GetVersion() const = 0;
    };

    // Factory function alias
    using CreatePluginFunction = IPlugin *(*)();
} // namespace Plugin
