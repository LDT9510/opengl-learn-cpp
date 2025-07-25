#pragma once

#include "core/types.h"
#include "utils/singleton.h"

#include <fmt/format.h>
#include <physfs.h>

#include <filesystem>
#include <string>

namespace core
{
    template<const char* TBasePath>
    class FileType
    {
    public:
        explicit FileType(std::string_view path) :
            m_Path{fmt::format("/{}/{}", TBasePath, path)}
        {
        }

        std::string GetPath() const
        {
            return m_Path;
        }

    private:
        std::string m_Path;
    };

    inline constexpr char K_CORE_SHADER_BASE_PATH[]{"shaders"};
    using CoreShaderFile = FileType<K_CORE_SHADER_BASE_PATH>;

    inline constexpr char K_TEXTURE_BASE_PATH[]{"textures"};
    using TextureFile = FileType<K_TEXTURE_BASE_PATH>;

    class Filesystem
    {
        template<typename T>
        // NOLINTNEXTLINE (*-convert-member-functions-to-static)
        void ReadFileInternal(const std::string& fileName, T* outBuf) const
        {
            if (auto* file = PHYSFS_openRead(fileName.c_str()))
            {
                i64 fileSize = PHYSFS_fileLength(file);
                outBuf->resize(fileSize);
                PHYSFS_readBytes(file, outBuf->data(), fileSize); // assume success for now
                PHYSFS_close(file);
            }
            else
            {
                SPDLOG_ERROR("Cannot open '{}': {}", fileName, PHYSFS_getLastError());
            }
        }

    public:
        ~Filesystem();

        template<typename TOutput, const char* TBaseDir>
        TOutput ReadFile(const FileType<TBaseDir>& fileName) const
        {
            auto    p = fileName.GetPath();
            TOutput buf;
            ReadFileInternal(p, &buf);
            return buf;
        }

        // NOLINTNEXTLINE (*-convert-member-functions-to-static)
        bool FileExists(const std::string& fileName) const
        {
            return PHYSFS_exists(fileName.c_str());
        }

    private:
        explicit Filesystem(char** platformArgument);

        std::string m_ContentRoot;

        friend Singleton<Filesystem>;
    };

    DECLARE_SINGLETON(fs, Filesystem);
} // namespace core
