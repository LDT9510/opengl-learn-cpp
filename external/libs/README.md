# External libraries

## {fmt}

- Description: A modern formatting library.
- Upstream: https://github.com/fmtlib/fmt
- Version: Releases Page, file `fmt-11.1.4.zip`, version `11.1.4`.
- License: `MIT`
- Updated: `15/04/2025`
- Wrapped: no
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
- License: `Apache Version 2.0`
- Updated: `15/04/2025`
- Wrapped: yes
- Files extracted from upstream:
    - Use the whole downloaded file.

## SDL3

- Description: Simple Direct-Media Layer.
- Upstream: https://github.com/libsdl-org/SDL
- Version: Releases Page, file `SDL3-3.2.10.zip`, version `3.2.10`.
- License: `zlib`
- Updated: `15/04/2025`
- Wrapped: no
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
- License: `MIT`
- Updated: `15/04/2025`
- Wrapped: no
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
- Wrapped: yes
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
- Wrapped: no
- Files extracted from upstream:
  - `cmake/**`
  - `glm/**`
  - `CMakeLists.txt`
  - `copying.txt`

## physfs

- Description: Portable filesystem abstraction
- Upstream: https://github.com/icculus/physfs
- Version: `release-3.2.0` (eb3383b532c5f74bfeb42ec306ba2cf80eed988c)
- License: `zlib`
- Updated: `05/06/2025`
- Wrapped: no
- Files extracted from upstream:
  - `extras/*.c`
  - `extras/*.h`
  - `extras/casefolding.txt`
  - `src/**`
  - `CMakeLists.txt`
  - `LICENSE.txt`

## stb-image

- Description: Image loader
- Upstream: https://github.com/nothings/stb
- Version: `v2.30` (013ac3beddff3dbffafd5177e7972067cd2b5083)
- License: `MIT (alternative A)`
- Updated: `17/06/2025`
- Wrapped: yes
- Files extracted from upstream:
  - `stb_image.h` (in "stb-image/include/stb")


## tracy

- Description: Frame profiler
- Upstream: https://github.com/wolfpld/tracy
- Version: `0.12.2` (c556831ddc6fe26d2fce01c14c97205a9dad46d5)
- License: `3-clause BSD`
- Updated: `07/23/2025`
- Wrapped: no
- Files extracted from upstream:
    - `cmake`
    - `public`
    - `Config.cmake.in`
    - `CMakeLists.txt`
    - `LICENSE`