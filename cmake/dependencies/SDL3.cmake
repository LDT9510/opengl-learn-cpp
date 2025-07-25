include("Utils")
include("ExternalsUtils")

block()
    set(lib_name "SDL3")
    Announce("Configuring \"${lib_name}\" external library.")

    # ====================== options ======================
    ForceBool(SDL_SHARED ON)  # Build a shared version of the library
    ForceBool(SDL_STATIC OFF)  # Build a static version of the library

    # for some platforms, always build static
    if(TARGET_PLATFORM_IS_WEB)
        ForceBool(SDL_SHARED OFF)
        ForceBool(SDL_STATIC ON)
    endif ()

    ForceBool(SDL_TESTS OFF)  # Build the test directory
    ForceBool(SDL_TEST_LIBRARY OFF)  # Build the SDL3_test library
    ForceBool(SDL_INSTALL OFF)  # Enable installation of SDL3
    ForceBool(SDL_UNINSTALL OFF)  # Enable uninstallation of SDL3
    ForceBool(SDL_EXAMPLES OFF)  # Build the examples directory
    ForceBool(SDL_INSTALL_TESTS OFF)  # Install tests target
    ForceBool(SDL_DISABLE_INSTALL_DOCS ON)  # Disable Install docs target

    # =================== subsystems ======================
    ForceBool(SDL_VIDEO ON)  # Enable the Video subsystem
    ForceBool(SDL_GPU OFF)  # Enable the GPU subsystem
    ForceBool(SDL_CAMERA OFF)  # Enable the Camera subsystem
    ForceBool(SDL_RENDER OFF)  # Enable the Render subsystem
    ForceBool(SDL_JOYSTICK ON)  # Enable the Joystick subsystem
    ForceBool(SDL_SENSOR OFF)  # Enable the Sensor subsystem
    ForceBool(SDL_HAPTIC OFF)  # Enable the Haptic subsystem
    ForceBool(SDL_HIDAPI ON)  # Enable the HIDAPI subsystem
    ForceBool(SDL_AUDIO OFF)  # Enable the Audio subsystem
    ForceBool(SDL_POWER OFF)  # Enable the Power subsystem
    
    # ==================== rendering and graphics APIs =======================
    ForceBool(SDL_DIRECTX OFF)  # Use DirectX for Windows audio/video
    ForceBool(SDL_OPENGL ON)  # Include OpenGL support
    ForceBool(SDL_OPENGLES OFF)  # Include OpenGL ES support
    ForceBool(SDL_VULKAN OFF)  # Enable Vulkan support
    ForceBool(SDL_OPENVR OFF)  # Use OpenVR video driver
    ForceBool(SDL_RENDER_D3D OFF)  # Enable the Direct3D 9 render driver
    ForceBool(SDL_RENDER_D3D11 OFF)  # Enable the Direct3D 11 render driver
    ForceBool(SDL_RENDER_D3D12 OFF)  # Enable the Direct3D 12 render driver
    ForceBool(SDL_RENDER_GPU OFF)  # Enable the SDL_GPU render driver
    ForceBool(SDL_RENDER_METAL OFF)  # Enable the Metal render driver
    ForceBool(SDL_RENDER_VULKAN OFF)  # Enable the Vulkan render driver

    #    # ======= advanced configurations (these should be left to auto-detection)  =======
    #    ForceBool(SDL_ALSA OFF)  # Support the ALSA audio API
    #    ForceBool(SDL_ASAN OFF)  # Use AddressSanitizer to detect memory errors
    #    ForceBool(SDL_ASSEMBLY ON)  # Enable assembly routines
    #    ForceString(SDL_ASSERTIONS "auto")  # Enable internal sanity checks (auto/disabled/release/enabled/paranoid)
    #    ForceBool(SDL_AVX ON)  # Use AVX assembly routines
    #    ForceBool(SDL_AVX2 ON)  # Use AVX2 assembly routines
    #    ForceBool(SDL_AVX512F ON)  # Use AVX512F assembly routines
    #    ForceString(SDL_BACKGROUNDING_SIGNAL OFF)  # number to use for magic backgrounding signal or 'OFF'
    #    ForceBool(SDL_CCACHE ON)  # Use Ccache to speed up build
    #    ForceBool(SDL_CLANG_TIDY OFF)  # Run clang-tidy static analysis
    #    ForceBool(SDL_CLOCK_GETTIME OFF)  # Use clock_gettime() instead of gettimeofday()
    #    ForceBool(SDL_DEPS_SHARED ON)  # Load dependencies dynamically
    #    ForceBool(SDL_DIALOG ON)  # Enable the Dialog subsystem
    #    ForceBool(SDL_DISKAUDIO ON)  # Support the disk writer audio driver
    #    ForceBool(SDL_DUMMYAUDIO OFF)  # Support the dummy audio driver
    #    ForceBool(SDL_DUMMYCAMERA OFF)  # Support the dummy camera driver
    #    ForceBool(SDL_DUMMYVIDEO OFF)  # Use dummy video driver
    #    ForceString(SDL_FOREGROUNDING_SIGNAL OFF)  # number to use for magic foregrounding signal or 'OFF'
    #    ForceBool(SDL_GCC_ATOMICS OFF)  # Use gcc builtin atomics
    #    ForceBool(SDL_GPU_DXVK OFF)  # Build SDL_GPU with DXVK support
    #    ForceBool(SDL_HIDAPI_JOYSTICK ON)  # Use HIDAPI for low level joystick drivers
    #    ForceBool(SDL_HIDAPI_LIBUSB ON)  # Use libusb for low level joystick drivers
    #    ForceBool(SDL_HIDAPI_LIBUSB_SHARED ON)  # Dynamically load libusb support
    #    ForceString(SDL_INSTALL_CMAKEDIR_ROOT cmake)  # Root folder where to install SDL3Config.cmake related files (SDL3 subfolder for MSVC projects)
    #    ForceBool(SDL_JACK OFF)  # Support the JACK audio API
    #    ForceBool(SDL_KMSDRM OFF)  # Use KMS DRM video driver
    #    ForceBool(SDL_LIBC ON)  # Use the system C library
    #    ForceBool(SDL_LIBICONV OFF)  # Prefer iconv() from libiconv, if available, over libc version
    #    ForceBool(SDL_LIBUDEV ON)  # Enable libudev support
    #    ForceBool(SDL_MMX ON)  # Use MMX assembly routines
    #    ForceBool(SDL_OFFSCREEN OFF)  # Use offscreen video driver
    #    ForceBool(SDL_PIPEWIRE OFF)  # Use Pipewire audio
    #    ForceBool(SDL_PRESEED ON)  # Preseed CMake cache to speed up configuration
    #    ForceBool(SDL_PTHREADS OFF)  # Use POSIX threads for multi-threading
    #    ForceBool(SDL_PULSEAUDIO OFF)  # Use PulseAudio
    #    ForceBool(SDL_RPATH OFF)  # Use an rpath when linking SDL
    #    ForceBool(SDL_SNDIO OFF)  # Support the sndio audio API
    #    ForceBool(SDL_SSE ON)  # Use SSE assembly routines
    #    ForceBool(SDL_SSE2 ON)  # Use SSE2 assembly routines
    #    ForceBool(SDL_SSE3 ON)  # Use SSE3 assembly routines
    #    ForceBool(SDL_SSE4_1 ON)  # Use SSE4.1 assembly routines
    #    ForceBool(SDL_SSE4_2 ON)  # Use SSE4.2 assembly routines
    #    ForceBool(SDL_SYSTEM_ICONV OFF)  # Use iconv() from system-installed libraries
    #    ForceBool(SDL_WASAPI ON)  # Use the Windows WASAPI audio driver
    #    ForceBool(SDL_WAYLAND OFF)  # Use Wayland video driver
    #    ForceBool(SDL_WERROR OFF)  # Enable -Werror
    #    # force_bool(SDL_X11 OFF)  # Use X11 video driver
    #    ForceBool(SDL_XINPUT ON)  # Use Xinput for Windows
    #    ForceBool(SDL_VIRTUAL_JOYSTICK ON)  # Enable the virtual-joystick driver
    #    ForceBool(SDL_XINPUT ON)  # Use Xinput for Windows

    AddExternalSubdirectory(${lib_name})
endblock()