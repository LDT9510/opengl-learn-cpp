#include "core/renderer.h"

#include "core/event_handler.h"
#include "core/timing.h"

#include <dev_ui/dev_ui.h>
#include <glad/gl.h>

core::Renderer::Renderer() { // NOLINT(*-pro-type-member-init)
    // generate the buffers and get back a handle to them
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);
}

core::Renderer::~Renderer() {
    // cleanup
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
}

void core::Renderer::SetupRendering() const {
    // clang-format off
    constexpr float vertices[] = {
        -0.5f,  -0.5f,  0.0f, // bottom left
         0.0f,   0.5f,  0.0f, // top
         0.5f,  -0.5f,  0.0f, // bottom right
    };
    constexpr unsigned int indices[] = {
        0, 1, 2
    };
    // clang-format on

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure
    // vertex attributes(s).
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex
    // attribute's bound vertex buffer object so afterward we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS
    // stored in the VAO; keep the EBO bound.
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterward so other VAO calls won't accidentally modify this VAO, but
    // this rarely happens. Modifying other VAOs requires a call to glBindVertexArray anyway so we
    // generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void core::Renderer::Render() const {
    glPolygonMode(GL_FRONT_AND_BACK, m_wireframeActive ? GL_LINE : GL_FILL);

    // clear the background
    glClear(GL_COLOR_BUFFER_BIT);

    // bind the shader program
    m_shader.Use();

    // calculate the color based on time
    float timeValue           = timing::GetSdlElapsedSeconds();
    float greenValue          = (sin(timeValue) / 2.0f) + 0.5f;
    int   vertexColorLocation = glGetUniformLocation(m_shader.GetProgram(), "ourColor");

    // update the uniform
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    // bind the array to be drawn and issue the draw call
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
}

void core::Renderer::RenderDevUi() {
    using namespace dev_ui;

    im::Begin("Learning OpenGL");

    if (im::CollapsingHeader("Global Shortcuts")) {
        static constexpr ImGuiTableFlags tableFlags =
            ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders;
        static constexpr auto yellow = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
        if (im::BeginTable("shortcuts", 2, tableFlags)) {
            im::TableSetupColumn("Shortcut", ImGuiTableColumnFlags_WidthFixed);
            im::TableSetupColumn("Description", ImGuiTableColumnFlags_WidthFixed);
            im::TableHeadersRow();
            im::TableNextRow();
            im::TableNextColumn();
            im::Indent();
            {
                im::TextColored(yellow, "U");
                im::TableNextColumn();
                im::Text("Enables wireframe mode");
            }
            im::EndTable();
        }
    }

    im::End();
}

void core::Renderer::HandleInput(const EventHandler& eventHandler) {
    if (eventHandler.IsKeyJustPressed(SDL_SCANCODE_U)) {
        m_wireframeActive = !m_wireframeActive;
    }
}
