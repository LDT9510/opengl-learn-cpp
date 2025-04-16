#pragma once

#include <thirdparty/SDL3/SDL.h>

#include <functional>
#include <optional>

namespace core {

class EventHandler {
public:
    using MouseOffsetCallback          = std::function<void(float xOffset, float yOffset)>;
    using MouseWheelDirectionCallback  = std::function<void(float mouseWheelDirection)>;
    using WindowsResizingCallback      = std::function<void(int newSizeX, int mewSizeY)>;
    using WindowsQuitCallback          = std::function<void()>;
    using KeyboardInputHandlerCallback = std::function<void(float deltaTime)>;

    struct Config {
        WindowsResizingCallback windowsResizingCallback;
        WindowsQuitCallback     windowsQuitCallback;
    };

    explicit EventHandler(const Config& config);

    EventHandler(const EventHandler& other)                = delete;
    EventHandler(EventHandler&& other) noexcept            = default;
    EventHandler& operator=(const EventHandler& other)     = delete;
    EventHandler& operator=(EventHandler&& other) noexcept = default;

    void CollectInputAndProcessEvents();
    // bool ImGuiActive() const;
    bool IsKeyPressed(SDL_Scancode keyScanCode) const;
    bool IsKeyReleased(SDL_Scancode keyScanCode) const;
    bool CheckKeyEvent(SDL_Scancode keyScanCode) const;

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
    const bool*                                 m_keyboardState = nullptr;
    SDL_Scancode                                m_lastKeyPressed{};
    bool                                        m_disableKeyCheck = false;
    WindowsResizingCallback                     m_windowResizingCallback;
    WindowsQuitCallback                         m_windowQuitCallback;
    std::optional<KeyboardInputHandlerCallback> m_keyboardInputHandlerCallback;
    std::optional<MouseOffsetCallback>          m_mouseOffsetCallBack;
    std::optional<MouseWheelDirectionCallback>  m_mouseWheelDirectionCallback;
    float                                       m_lastElapsedTime = 0.0;
};

} // namespace core
