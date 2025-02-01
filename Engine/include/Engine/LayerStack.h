#pragma once

#include "Engine/Core.h"
#include "ILayer.h"

namespace Engine {
    class LayerStack {
    private:
        std::vector<std::unique_ptr<ILayer>> m_Layers;
        uint32_t m_LayerInsertIndex = 0;
    public:
        LayerStack() = default;
        ~LayerStack();

        /**
         * @brief Adds a layer to the stack.
         *
         * This method takes ownership of the provided layer and adds it to the stack.
         * The layer will be managed by the LayerStack and will be updated and rendered
         * in the order it was added.
         *
         * @param layer A unique pointer to the layer to be added.
         */
        void PushLayer(std::unique_ptr<ILayer> layer);

        /**
         * @brief Removes a layer from the stack.
         *
         * This method removes the specified layer from the stack. The layer will no longer
         * be managed by the LayerStack and will not be updated or rendered.
         *
         * @param layer A unique pointer to the layer to be removed.
         */
        void PopLayer(std::unique_ptr<ILayer> layer);

        /**
         * @brief Adds an overlay to the stack.
         *
         * This method takes ownership of the provided overlay and adds it to the stack.
         * Overlays are rendered on top of all other layers and are typically used for
         * UI elements or other elements that should always be visible.
         *
         * @param overlay A unique pointer to the overlay to be added.
         */
        //void PushOverlay(std::unique_ptr<ILayer> overlay);

        /**
         * @brief Removes an overlay from the stack.
         *
         * This method removes the specified overlay from the stack. The overlay will no longer
         * be managed by the LayerStack and will not be updated or rendered.
         *
         * @param overlay A unique pointer to the overlay to be removed.
         */
        //void PopOverlay(std::unique_ptr<ILayer> overlay);

        /**
         * @brief Returns an iterator to the beginning of the layer stack.
         *
         * This method returns an iterator to the first element in the layer stack.
         * It can be used to iterate over all layers in the stack.
         *
         * @return An iterator to the beginning of the layer stack.
         */
        std::vector<std::unique_ptr<ILayer>>::iterator begin() { return m_Layers.begin(); }

        /**
         * @brief Returns an iterator to the end of the layer stack.
         *
         * This method returns an iterator to the element following the last element
         * in the layer stack. It can be used to iterate over all layers in the stack.
         *
         * @return An iterator to the end of the layer stack.
         */
        std::vector<std::unique_ptr<ILayer>>::iterator end() { return m_Layers.end(); }
    };
} // namespace Engine
