#pragma once

#include "Engine/ILayer.h"
namespace RTSim {

    class LayerBackend: public Engine::ILayer {
        // Inherited via ILayer
        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate(float deltaTime) override;
        void OnEvent() override;
    };

} // namespace RTSim
