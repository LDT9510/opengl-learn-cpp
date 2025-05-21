#pragma once

#include <SDL3/SDL.h>
#include <array>
#include <functional>
#include <optional>

namespace core {

class EventHandler {
public:
    using MouseOffsetCallback          = std::function<void(float xOffset, float yOffset)>;
    using MouseWheelDirectionCallback  = std::function<void(float mouseWheelDirection)>;
    using WindowsResizingCallback      = std::function<void(int newSizeX, int mewSizeY)>;
    using WindowsQuitCallback          = std::function<void()>;
    using KeyboardInputHandlerCallback = std::function<void(const EventHandler& eventHandler)>;

    struct Config {
        WindowsResizingCallback windowsResizingCallback;
        WindowsQuitCallback     windowsQuitCallback;
    };

    explicit EventHandler(Config config);

    EventHandler(const EventHandler& other)                = delete;
    EventHandler(EventHandler&& other) noexcept            = default;
    EventHandler& operator=(const EventHandler& other)     = delete;
    EventHandler& operator=(EventHandler&& other) noexcept = default;

    void CollectAndProcessInput();
    bool IsKeyPressed(SDL_Scancode keyScanCode) const;
    bool IsKeyJustPressed(SDL_Scancode keyScanCode) const;

    void RegisterMouseOffsetCallback(MouseOffsetCallback callback) {
        m_mouseOffsetCallBack = std::move(callback);
    }

    void RegisterMouseWheelDirectionCallback(MouseWheelDirectionCallback callback) {
        m_mouseWheelDirectionCallback = std::move(callback);
    }

    void RegisterKeyboardInputHandler(KeyboardInputHandlerCallback callback) {
        m_keyboardInputHandlerCallback = std::move(callback);
    }

    void ClearOptionalCallbacks();

private:
    std::array<bool, SDL_SCANCODE_COUNT>        m_lastKeyboardState{};
    SDL_Scancode                                m_pressedKey = SDL_SCANCODE_UNKNOWN;
    WindowsResizingCallback                     m_windowResizingCallback;
    WindowsQuitCallback                         m_windowQuitCallback;
    std::optional<KeyboardInputHandlerCallback> m_keyboardInputHandlerCallback;
    std::optional<MouseOffsetCallback>          m_mouseOffsetCallBack;
    std::optional<MouseWheelDirectionCallback>  m_mouseWheelDirectionCallback;
};

} // namespace core
