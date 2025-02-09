#pragma once

#include "Engine/Core.h"

namespace Engine {
    /**
     * @class ILayer
     * @brief Interface class for layers in the engine.
     *
     * This class provides a common interface for all layers in the engine.
     * Layers are used to separate different parts of the application, such as
     * rendering, input handling, and game logic. Each layer can be attached,
     * detached, updated, and can handle events.
     */
    class ILayer {
      protected:
        std::string m_Name; ///< The name of the layer.
      public:
        ILayer()          = default;
        virtual ~ILayer() = default;

        /**
         * @brief Called when the layer is attached to the engine.
         *
         * This method is called when the layer is first attached to the engine.
         * It can be used to initialize resources or set up the layer.
         */
        virtual void OnAttach() = 0;

        /**
         * @brief Called when the layer is detached from the engine.
         *
         * This method is called when the layer is detached from the engine.
         * It can be used to clean up resources or perform any necessary teardown.
         */
        virtual void OnDetach() = 0;

        /**
         * @brief Called every frame to update the layer.
         *
         * This method is called every frame and is used to update the layer.
         * @param deltaTime The time elapsed since the last frame.
         */
        virtual void OnUpdate(float deltaTime) = 0;

        /**
         * @brief Called when an event occurs.
         *
         * This method is called when an event occurs. It can be used to handle
         * input events, such as keyboard or mouse events.
         */
        virtual void OnEvent() = 0;

        /**
         * @brief Gets the name of the layer.
         *
         * This method returns the name of the layer.
         * @return The name of the layer.
         */
        const std::string &GetName() const {
            return m_Name;
        }
    };
} // namespace Engine
