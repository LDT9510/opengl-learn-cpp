#pragma once

#include "../utils/types.h"

#include <SDL3/SDL.h>

#include <array>
#include <functional>
#include <optional>

namespace core
{
    class EventHandler
    {
        using MouseOffsetCallback          = std::function<void(f32 xOffset, f32 yOffset)>;
        using MouseWheelDirectionCallback  = std::function<void(f32 mouseWheelDirection)>;
        using WindowsResizingCallback      = std::function<void(i32 newSizeX, i32 mewSizeY)>;
        using WindowsQuitCallback          = std::function<void()>;
        using KeyboardInputHandlerCallback = std::function<void(const EventHandler& eventHandler)>;

    public:
        struct Config
        {
            WindowsResizingCallback WindowsResizingCallback;
            WindowsQuitCallback     WindowsQuitCallback;
        };

        explicit EventHandler(Config config);

        EventHandler(const EventHandler& other)                = delete;
        EventHandler& operator=(const EventHandler& other)     = delete;
        EventHandler(EventHandler&& other) noexcept            = default;
        EventHandler& operator=(EventHandler&& other) noexcept = default;

        void RegisterMouseOffsetCallback(const MouseOffsetCallback& callback)
        {
            m_MouseOffsetCallBack = callback;
        }

        void RegisterMouseWheelDirectionCallback(const MouseWheelDirectionCallback& callback)
        {
            m_MouseWheelDirectionCallback = callback;
        }

        void RegisterKeyboardInputHandler(const KeyboardInputHandlerCallback& callback)
        {
            m_KeyboardInputHandlerCallback = callback;
        }

        void ClearOptionalCallbacks();
        void CollectInput();
        void ProcessInput() const;
        b8   IsKeyPressed(SDL_Keycode keyCode) const;
        b8   IsKeyReleased(SDL_Keycode keyCode) const;
        b8   IsKeyJustPressed(SDL_Keycode keyCode) const;

    private:
        std::array<b8, SDL_SCANCODE_COUNT>          m_CurrentKeyboardState{};
        std::array<b8, SDL_SCANCODE_COUNT>          m_LastKeyboardState{};
        b8                                          m_KeyboardInputAvailable{};
        WindowsResizingCallback                     m_WindowResizingCallback;
        WindowsQuitCallback                         m_WindowQuitCallback;
        std::optional<KeyboardInputHandlerCallback> m_KeyboardInputHandlerCallback;
        std::optional<MouseOffsetCallback>          m_MouseOffsetCallBack;
        std::optional<MouseWheelDirectionCallback>  m_MouseWheelDirectionCallback;
    };
} // namespace core
