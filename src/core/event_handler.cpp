#include "core/event_handler.h"

#include <SDL3/SDL.h>
#include <dev_ui/dev_ui.h>

core::EventHandler::EventHandler(Config config) :
    m_windowResizingCallback{std::move(config.windowsResizingCallback)},
    m_windowQuitCallback{std::move(config.windowsQuitCallback)} {
}

void core::EventHandler::CollectAndProcessInput() {
    // assume handled
    m_pressedKey = SDL_SCANCODE_UNKNOWN;

    int         numKeys;
    const bool* keyboardState = SDL_GetKeyboardState(&numKeys);
    std::copy_n(keyboardState, numKeys, &m_lastKeyboardState[0]); // store the previous state

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        dev_ui::ProcessInput(e);

        switch (e.type) {
            case SDL_EVENT_QUIT: m_windowQuitCallback(); break;
            case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
                m_windowResizingCallback(e.window.data1, e.window.data2);
                break;
            case SDL_EVENT_MOUSE_WHEEL:
                if (m_mouseWheelDirectionCallback) (*m_mouseWheelDirectionCallback)(e.wheel.y);
                break;
            case SDL_EVENT_MOUSE_MOTION:
                if (m_mouseOffsetCallBack) {
                    (*m_mouseOffsetCallBack)(e.motion.xrel, -e.motion.yrel);
                }
                break;
            case SDL_EVENT_KEY_DOWN: {
                m_pressedKey = e.key.scancode;

                if (m_keyboardInputHandlerCallback) {
                    (*m_keyboardInputHandlerCallback)(*this);
                }
            } break;
            default: break;
        }
    }
}

bool core::EventHandler::IsKeyPressed(const SDL_Scancode keyScanCode) const {
    return m_pressedKey == keyScanCode;
}

bool core::EventHandler::IsKeyJustPressed(SDL_Scancode keyScanCode) const {
    return m_pressedKey == keyScanCode && !m_lastKeyboardState[keyScanCode];
}

void core::EventHandler::ClearOptionalCallbacks() {
    m_mouseOffsetCallBack          = std::nullopt;
    m_mouseWheelDirectionCallback  = std::nullopt;
    m_keyboardInputHandlerCallback = std::nullopt;
}
