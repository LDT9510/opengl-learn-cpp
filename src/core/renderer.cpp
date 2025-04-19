#include "core/renderer.h"

#include <dev_ui/dev_ui.h>
#include <glad/gl.h>

void core::Renderer::Render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void core::Renderer::RenderDevUi() {
    using namespace dev_ui;
    
    im::Begin("Learning OpenGL");

    if (ImGui::CollapsingHeader("Global Shortcuts"))
    {
        static constexpr ImGuiTableFlags tableFlags =
            ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders;
        static constexpr auto yellow = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
        if (im::BeginTable("shortcuts", 2, tableFlags))
        {
            im::TableSetupColumn("Shortcut", ImGuiTableColumnFlags_WidthFixed);
            im::TableSetupColumn("Description", ImGuiTableColumnFlags_WidthFixed);
            im::TableHeadersRow();
            im::TableNextRow();
            im::TableNextColumn();
            im::Indent();
            im::TextColored(yellow, "U");
            im::TableNextColumn();
            im::Text("Enables wireframe mode");
            im::EndTable();
        }
    }

    im::End();
}
