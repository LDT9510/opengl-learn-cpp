#include "core/event_handler.h"

#include "core/timing.h"

#include <SDL3/SDL.h>
#include <dev_ui/dev_ui.h>

core::EventHandler::EventHandler(const Config& config) :
    m_windowResizingCallback{config.windowsResizingCallback},
    m_windowQuitCallback{config.windowsQuitCallback} {
}

void core::EventHandler::CollectInputAndProcessEvents() {
    // timing
    const float elapsedTime = timing::GetSdlElapsedSeconds();
    const float deltaTime   = elapsedTime - m_lastElapsedTime;
    m_lastElapsedTime       = elapsedTime;

    m_lastKeyPressed = SDL_SCANCODE_UNKNOWN; // reset the key, should have been handled already
    m_keyboardState  = SDL_GetKeyboardState(nullptr);

    // const auto io = im::GetIO();
    /*bool passAppMouseInput = !m_useImGui;*/

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        dev_ui::ProcessInput(e);

        const auto keyScanCode = e.key.scancode;
        switch (e.type) {
            case SDL_EVENT_QUIT: m_windowQuitCallback(); break;
            case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
                m_windowResizingCallback(e.window.data1, e.window.data2);
                break;
            case SDL_EVENT_MOUSE_WHEEL:
                if (/*passAppMouseInput && */ m_mouseWheelDirectionCallback)
                    (*m_mouseWheelDirectionCallback)(e.wheel.y);
                break;
            case SDL_EVENT_MOUSE_MOTION:
                if (/*passAppMouseInput && */ m_mouseOffsetCallBack) {
                    (*m_mouseOffsetCallBack)(e.motion.xrel, -e.motion.yrel);
                }

                break;
            case SDL_EVENT_KEY_DOWN:
                // if (io.WantTextInput) {
                //     m_disableKeyCheck = true;
                // } else {
                //     m_disableKeyCheck = false;
                //     m_lastKeyPressed  = keyScanCode;
                // }

                if (keyScanCode == SDL_SCANCODE_I) {
                    /*if (passAppMouseInput && m_useImGui)
                    {
                        passAppMouseInput = false;
                        ImGui::SetNextWindowFocus();
                    }
                    else
                    {
                        m_useImGui = !m_useImGui;
                    }*/
                }
                break;
            default: break;
        }
    }

    if (m_keyboardInputHandlerCallback) {
        (*m_keyboardInputHandlerCallback)(deltaTime);
    }
}

bool core::EventHandler::IsKeyPressed(const SDL_Scancode keyScanCode) const {
    if (m_disableKeyCheck) return false;

    return m_keyboardState ? m_keyboardState[keyScanCode] : false;
}

bool core::EventHandler::IsKeyReleased(const SDL_Scancode keyScanCode) const {
    if (m_disableKeyCheck) return false;

    return m_keyboardState ? m_keyboardState[keyScanCode] == 0 : false;
}

bool core::EventHandler::CheckKeyEvent(const SDL_Scancode keyScanCode) const {
    return m_lastKeyPressed == keyScanCode;
}

void core::EventHandler::ClearOptionalCallbacks() {
    m_mouseOffsetCallBack          = std::nullopt;
    m_mouseWheelDirectionCallback  = std::nullopt;
    m_keyboardInputHandlerCallback = std::nullopt;
}
