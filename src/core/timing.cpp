#include "timing.h"

#include <SDL3/SDL.h>

namespace core
{
    f32 timing::GetSdlElapsedSeconds()
    {
        return static_cast<f32>(SDL_GetTicks()) / 1000.f;
    }
} // namespace core
