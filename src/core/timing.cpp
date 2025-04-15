#include "core/timing.h"

#include <thirdparty/SDL3/SDL.h>

namespace core::timing {
float GetSdlElapsedSeconds() {
    return static_cast<float>(SDL_GetTicks()) / 1000.f;
}
} // namespace core::timing
