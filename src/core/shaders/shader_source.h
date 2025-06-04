#pragma once

namespace shaders {

namespace vertex {
    static constexpr auto source = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";
}

namespace fragment {
    static constexpr auto source = R"(
#version 330 core
out vec4 FragColor;
  
uniform vec4 ourColor; // we set this variable in the OpenGL code.

void main()
{
    FragColor = ourColor;
}   
)";
}

} // namespace shaders
