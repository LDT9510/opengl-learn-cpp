#include "core/renderer.h"

#include <dev_ui/dev_ui.h>
#include <glad/gl.h>

using namespace dev_ui;

void core::Renderer::Render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void core::Renderer::RenderDevUi() {
    im::ShowDemoWindow(nullptr);
}
