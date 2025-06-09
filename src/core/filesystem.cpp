#include "core/filesystem.h"

#include <SDL3/SDL_filesystem.h>
#include <physfs.h>
#include <spdlog/spdlog.h>

namespace core
{
    Filesystem::Filesystem(char** platformArgument)
    {
        if (PHYSFS_init(std::strlen(platformArgument[0]) > 0 ? platformArgument[0] : nullptr))
        {
            SPDLOG_INFO("Virtual filesystem initialized.");
        }
        else
        {
            CRASH("Virtual filesystem error: {}.\n", PHYSFS_getLastError());
        }

        fmt::format_to(std::back_inserter(m_ContentRoot), "{}/contents", SDL_GetBasePath());

        if (PHYSFS_mount(m_ContentRoot.c_str(), "/", false))
        {
            SPDLOG_DEBUG("Filesystem root '{}' mounted at '/' successfully.", m_ContentRoot);
        }
        else
        {
            CRASH("Cannot mount virtual filesystem from '{}': {}", m_ContentRoot, PHYSFS_getLastError());
        }
    }

    Filesystem::~Filesystem()
    {
        PHYSFS_unmount(m_ContentRoot.c_str());
        PHYSFS_deinit();
    }
} // namespace core
