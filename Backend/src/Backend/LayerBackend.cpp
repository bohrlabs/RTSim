#include "LayerBackend.h"

namespace RTSim {

    void LayerBackend::OnAttach() {
    }

    void LayerBackend::OnDetach() {
    }

    void LayerBackend::OnUpdate(float deltaTimeMilli) {
        _sleep(10);
    }

    void LayerBackend::OnEvent() {
    }

} // namespace RTSim
