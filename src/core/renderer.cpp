#include "core/renderer.h"

#include <thirdparty/glad/gl.h>

namespace core {
void Renderer::Render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
} // core