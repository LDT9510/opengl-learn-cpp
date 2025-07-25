

#include "core/event_handler.h"

#include "dev_ui/dev_ui.h"

#include <SDL3/SDL.h>

namespace core
{
    EventHandler::EventHandler(Config config) :
        m_WindowResizingCallback{std::move(config.WindowsResizingCallback)},
        m_WindowQuitCallback{std::move(config.WindowsQuitCallback)}
    {
    }

    // TODO either handle all events here or defer them
    void EventHandler::CollectInput()
    {
        m_LastKeyboardState      = m_CurrentKeyboardState;
        m_KeyboardInputAvailable = false;

        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            dev_ui::ProcessInput(e);

            switch (e.type)
            {
                case SDL_EVENT_QUIT:
                    m_WindowQuitCallback();
                    break;

                case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
                    m_WindowResizingCallback(e.window.data1, e.window.data2);
                    break;

                case SDL_EVENT_MOUSE_WHEEL:
                    if (m_MouseWheelDirectionCallback) (*m_MouseWheelDirectionCallback)(e.wheel.y);
                    break;

                case SDL_EVENT_MOUSE_MOTION:
                    if (m_MouseOffsetCallBack)
                    {
                        (*m_MouseOffsetCallBack)(e.motion.xrel, -e.motion.yrel);
                    }
                    break;

                case SDL_EVENT_KEY_DOWN:
                case SDL_EVENT_KEY_UP:
                    m_KeyboardInputAvailable = true;
                    break;

                default:
                    break;
            }
        }

        i32       numKeys;
        const b8* keyboardState = SDL_GetKeyboardState(&numKeys);
        std::copy_n(keyboardState, numKeys, m_CurrentKeyboardState.data()); // store the previous state
    }

    void EventHandler::ProcessInput() const
    {
        if (m_KeyboardInputAvailable && m_KeyboardInputHandlerCallback)
        {
            (*m_KeyboardInputHandlerCallback)(*this);
        }
    }

    b8 EventHandler::IsKeyPressed(SDL_Keycode keyCode) const
    {
        return m_CurrentKeyboardState[SDL_GetScancodeFromKey(keyCode, nullptr)];
    }

    b8 EventHandler::IsKeyReleased(SDL_Keycode keyCode) const
    {
        return !IsKeyPressed(SDL_GetScancodeFromKey(keyCode, nullptr));
    }

    b8 EventHandler::IsKeyJustPressed(SDL_Keycode keyCode) const
    {
        auto scancode = SDL_GetScancodeFromKey(keyCode, nullptr);
        return m_CurrentKeyboardState[scancode] && !m_LastKeyboardState[scancode];
    }

    void EventHandler::ClearOptionalCallbacks()
    {
        m_MouseOffsetCallBack          = std::nullopt;
        m_MouseWheelDirectionCallback  = std::nullopt;
        m_KeyboardInputHandlerCallback = std::nullopt;
    }
} // namespace core
