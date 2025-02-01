# My C++20 Application: Architecture Overview

This README provides an overview of the architecture for my C++20 application.

## Architecture

The application is structured with a clear separation of concerns between a **Frontend** and a **Backend**.

### High-Level Architecture


```mermaid
classDiagram
    class Engine {
        
        - Core
        - Utilities
        - Logging
        - SharedMemory
        - OpenGLContext
        - 3DGraphics
        - 2DGraphics
        - PluginInterface
    }
    class Frontend {
        <<Engine>>
        - UserInterface <<Dear ImGui>>
        - Configuration
        <<OpenGL>> Visualization3D 
        - Visualization2D <<OpenGL>>
    }
    class Backend {
        <<Engine>>
        - API
        - DataIngestion
        - DataProcessing
        - AlgorithmExecution
        - DataStorage
    }
    class Plugin  {
        <<PluginInterface>>
        + OnInitialize()
        + OnUpdate()
        + OnShutdown()
        + Process()
        
    }
    Engine ..> Plugin : uses
    Frontend ..> Engine
    Backend ..> Engine
   ```


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