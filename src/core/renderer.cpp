#include "core/renderer.h"

#include "core/event_handler.h"
#include "core/filesystem.h"

#include <glad/gl.h>
#include <imgui/imgui.h>
#include <spdlog/spdlog.h>
#include <stb/stb_image.h>

namespace core
{
    Renderer::Renderer() :
        m_Shader{CoreShaderFile("vertex_shader.vert"), CoreShaderFile("fragment_shader.frag")}
    {
        // generate the buffers and get back a handle to them
        glGenVertexArrays(1, &m_Vao);
        glGenBuffers(1, &m_Vbo);
        glGenBuffers(1, &m_Ebo);
        glGenTextures(1, &m_Texture);
    }

    Renderer::~Renderer()
    {
        // cleanup
        glDeleteVertexArrays(1, &m_Vao);
        glDeleteBuffers(1, &m_Vbo);
        glDeleteBuffers(1, &m_Ebo);
        glDeleteTextures(1, &m_Texture);
    }

    void Renderer::SetupRendering() const
    {
        // clang-format off
        static constexpr f32 vertices[] = {
            // positions         // colors        // texture coordinates
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,     // bottom right
           -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,     // bottom left
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.5f, 1.0f      // top
       };

        static constexpr u32 indices[] = {
            0, 1, 2
        };
        // clang-format on

        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then
        // configure vertex attributes(s).
        glBindVertexArray(m_Vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), nullptr);
        glEnableVertexAttribArray(0);

        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), reinterpret_cast<void*>(3 * sizeof(f32)));
        glEnableVertexAttribArray(1);

        // texture coordinates attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(f32), reinterpret_cast<void*>(6 * sizeof(f32)));
        glEnableVertexAttribArray(2);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex
        // attribute's bound vertex buffer object so afterward we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object
        // IS stored in the VAO; keep the EBO bound. glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterward so other VAO calls won't accidentally modify this VAO,
        // but this rarely happens. Modifying other VAOs requires a call to glBindVertexArray anyway
        // so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);

        // load texture from image
        // load and generate the texture
        int            width, height, nrChannels;
        auto           imageContents = fs::Instance().ReadFile<std::vector<u8>>(TextureFile("wall.jpg"));
        unsigned char* data          = stbi_load_from_memory(
            imageContents.data(), static_cast<i32>(imageContents.size()), &width, &height, &nrChannels, 0
        );
        if (data)
        {
            // load texture data and configure
            glBindTexture(GL_TEXTURE_2D, m_Texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            // set the texture wrapping/filtering options (on the currently bound texture object)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            static constexpr f32 borderColor[] = {1.0f, 1.0f, 0.0f, 1.0f};
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
            stbi_image_free(data);
        }
        else
        {
            SPDLOG_ERROR("Failed to load texture");
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    }

    void Renderer::Render() const
    {
        glPolygonMode(GL_FRONT_AND_BACK, m_IsWireframeActive ? GL_LINE : GL_FILL);

        // clear the background
        glClear(GL_COLOR_BUFFER_BIT);

        // bind the shader program
        m_Shader.Use();

        // bind the array to be drawn and issue the draw call
        glBindTexture(GL_TEXTURE_2D, m_Texture);
        glBindVertexArray(m_Vao);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::PrepareDevUi()
    {
        ImGui::Begin("Learning OpenGL");

        if (ImGui::CollapsingHeader("Global Shortcuts"))
        {
            static constexpr ImGuiTableFlags tableFlags = ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders;
            static constexpr auto            yellow     = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
            if (ImGui::BeginTable("shortcuts", 2, tableFlags))
            {
                ImGui::TableSetupColumn("Shortcut", ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableSetupColumn("Description", ImGuiTableColumnFlags_WidthFixed);
                ImGui::TableHeadersRow();
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Indent();
                {
                    ImGui::TextColored(yellow, "U");
                    ImGui::TableNextColumn();
                    ImGui::Text("Enables wireframe mode");
                }
                ImGui::EndTable();
            }
        }

        if (ImGui::Button("Reload shaders"))
        {
            if (!m_IsShaderReloading)
            {
                if (ReloadShaders())
                {
                    SPDLOG_INFO("All Shaders reloaded OK.");
                }
                else
                {
                    SPDLOG_ERROR("Error reloading shaders.");
                }
            }
            else
            {
                SPDLOG_INFO("Already compiling, please wait...");
            }
        }

        ImGui::End();
    }

    void Renderer::HandleInput(const EventHandler& eventHandler)
    {
        if (eventHandler.IsKeyJustPressed(SDLK_U))
        {
            m_IsWireframeActive = !m_IsWireframeActive;
        }
    }

    b8 Renderer::ReloadShaders()
    {
        m_IsShaderReloading = true;
        m_Shader            = {CoreShaderFile("vertex_shader.vert"), CoreShaderFile("fragment_shader.frag")};
        m_IsShaderReloading = false;

        return m_Shader.IsValid();
    }
} // namespace core
