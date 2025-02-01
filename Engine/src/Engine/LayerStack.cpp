#include "Engine/LayerStack.h"

Engine::LayerStack::~LayerStack() {
}

void Engine::LayerStack::PushLayer(std::unique_ptr<ILayer> layer) {

    m_Layers.emplace(m_Layers.begin(), std::move(layer));
}

void Engine::LayerStack::PopLayer(std::unique_ptr<ILayer> layer) {
    auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
    if (it != m_Layers.end()) {
        m_Layers.erase(it);
    }
}
