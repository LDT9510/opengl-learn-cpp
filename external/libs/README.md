# External libraries

## {fmt}

- Description: A modern formatting library.
- Upstream: https://github.com/fmtlib/fmt
- Version: Releases Page, file `fmt-11.1.4.zip`, version `11.1.4`.
- License: `MIT`
- Updated: `15/04/2025`
- Files extracted from upstream:
    - `include/**`
    - `src/**`
    - `support/**`
    - `ChangeLog.md`
    - `CMakeLists.txt`
    - `LICENSE`
    - `README.md`

## glad

- Description: Multi-Language Vulkan/GL/GLES/EGL/GLX/WGL Loader-Generator based on the official specs.
- Upstream: https://github.com/Dav1dde/glad
- Version: Generated with https://gen.glad.sh/#generator=c&api=gl%3D3.3&profile=gl%3Dcore%2Cgles1%3Dcommon
- License: `MIT`
- Updated: `15/04/2025`
- Files extracted from upstream:
    - Use the whole downloaded file.

## SDL3

- Description: Simple Direct-Media Layer.
- Upstream: https://github.com/libsdl-org/SDL
- Version: Releases Page, file `SDL3-3.2.10.zip`, version `3.2.10`.
- License: `Zlib`
- Updated: `15/04/2025`
- Files extracted from upstream:
    - `cmake/**`
    - `include/**`
    - `src/**`
    - `CMakeLists.txt`
    - `LICENSE.txt`
    - `README.md`
    - `REVISION.txt`

## spdlog

- Description: Fast C++ logging library.
- Upstream: https://github.com/gabime/spdlog
- Version: Releases Page, file `Source code.zip`, version `1.15.2`.
- License: `Zlib`
- Updated: `15/04/2025`
- Files extracted from upstream:
    - `cmake/**`
    - `include/**` (except `include/fmt/bundled/**` as it's using the external {fmt})
    - `src/**` (except `src/bundled_fmtlib_format.cpp`, same reason above)
    - `CMakeLists.txt`
    - `LICENSE`
    - `README.md`

## imgui

- Description: Dear ImGui: Bloat-free Graphical User interface for C++ with minimal dependencies
- Upstream: https://github.com/ocornut/imgui
- Version: `1.91.9b` (f5befd2d29e66809cd1110a152e375a7f1981f06)
- License: `MIT`
- Updated: `16/04/2025`
- Files extracted from upstream (custom organization):
  - `*.h`
  - `*.cpp`
  - `CMakeLists.txt`
  - `LICENSE.txt`

## glm

- Description: OpenGL Mathematics (light version)
- Upstream: https://github.com/g-truc/glm
- Version: `1.0.1` (0af55ccecd98d4e5a8d1fad7de25ba429d60e863)
- License: `MIT`
- Updated: `04/06/2025`
- Files extracted from upstream:
  - `cmake/**`
  - `glm/**`
  - `CMakeLists.txt`
  - `copying.txt`