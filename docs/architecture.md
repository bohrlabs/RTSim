# My C++23 Application: Architecture Overview

This README provides an overview of the architecture for my C++20 application.

## Architecture

The application is structured with a clear separation of concerns between a **Frontend** and a **Backend**.

### High-Level Architecture


```mermaid
classDiagram
    class IPlugin {
      + Initialize(services: IServices): bool
      + Shutdown(): void
      + Start(): void
      + Stop(): void
      + Process(deltaTime: float): void
      + GetName(): string
      + GetVersion(): string
    }

    class IServices {
      + CreateInputPort~T~(name: string, port: T**): void
      + CreateOutputPort~T~(name: string, port: T*): void
      + RegisterProperty~T~(name: string, value: T&): void
      + GetProperty(name: string): IProperty*
    }

    class IProperty {
      + GetData(): void*
      + GetSize(): size_t
      + GetTypeHash(): size_t
      + Serialize(): string
      + Deserialize(value: string): void
    }

    class FrameworkServices {
      - m_SharedMem: SharedMemoryManager&
      - m_PortMgr: PortManager&
      - m_InstanceId: string
      - m_Mutex: mutex
      + GetProperty(name: string): IProperty*
      # InternalCreateInputPort(...)
      # InternalCreateOutputPort(...)
      # InternalRegisterProperty(...)
    }

    class PropertyImpl {
      - m_pData: void*
      - m_Size: size_t
      - m_TypeHash: size_t
      + GetData(): void*
      + GetSize(): size_t
      + GetTypeHash(): size_t
      + Serialize(): string
      + Deserialize(value: string): void
    }

    class SharedMemoryManager {
      + Allocate(name: string, size: size_t): void*
      + Register(name: string, pData: void*, size: size_t): void
      + Get~T~(name: string): T*
    }

    class PortManager {
      + RegisterInputPort(name: string, pData: void*, size: size_t): void
      + RegisterOutputPort(name: string, pData: void*, size: size_t): void
      + Connect(outputName: string, inputName: string): void
    }

    class UUIDOwner {
      + GetUUID32(): uint32_t
      + GetUUID64(): uint64_t
      + GetUUIDString(): string
    }

    IServices <|-- FrameworkServices
    IProperty <|-- PropertyImpl
    IPlugin <|-- UUIDOwner

    FrameworkServices --> SharedMemoryManager
    FrameworkServices --> PortManager
    FrameworkServices --> PropertyImpl

    IServices --> IProperty : manages
    IPlugin --> IServices : uses


   ```


''' notes
    note right of IPlugin::Process
    Framework calls this
    with simulation deltaTime
    end note

    note bottom of IServices::CreateInputPort
    Template method forwards to
    InternalCreateInputPort with
    type-erased pointers
    end note

# Folder structure
```
Engine/
├── include/
│   └── Engine/ 
│       ├── Core.h
│       ├── Logger.h
│       ├── Threading.h
│       ├── Platform.h
│       ├── Configuration.h
│       └── IPlugin.h 
├── src/
│   └── Engine/
│       ├── Core.cpp
│       ├── Logger.cpp
│       ├── Threading.cpp
│       ├── Platform.cpp
│       ├── Configuration.cpp
│       ├── PluginManager.cpp
│       ├── PluginManager.h
├── CMakeLists.txt

Frontend/
├── src/
│   └── Frontend.cpp
├── CMakeLists.txt

Backend/
├── src/
│   └── Backend.cpp
├── CMakeLists.txt

tests/
    ├── CoreTests.cpp
    ├── FrontendTests.cpp 
    ├── BackendTests.cpp
    ├── ... (other test files) ...
├── CMakeLists.txt

Plugins/
    ├── MyFirstPlugin/
    │   ├── src/
    │   │   └── MyFirstPlugin.cpp
    │   ├── include/
    │   │   └── MyFirstPlugin.h
    │   ├── CMakeLists.txt
    ├── ... (other plugin directories) ...

CMakeLists.txt (in root directory)
.gitignore
CMakePresets.json

```