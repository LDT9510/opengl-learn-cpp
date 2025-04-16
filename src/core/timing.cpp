#include "core/timing.h"

#include <SDL3/SDL.h>

float core::timing::GetSdlElapsedSeconds() {
    return static_cast<float>(SDL_GetTicks()) / 1000.f;
}
