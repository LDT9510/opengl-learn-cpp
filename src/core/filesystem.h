#pragma once

#include "core/types.h"
#include "utils/singleton.h"

#include <fmt/format.h>
#include <physfs.h>

#include <filesystem>
#include <string>

namespace core
{
template<size_t N>
struct str_lit {
	char value[N];

	explicit constexpr str_lit(const char (&str)[N])
	        : value{}
	{
		std::copy_n(str, N, value);
	}
};

template<str_lit TBasePath>
class file_type {
    public:
	explicit file_type(std::string_view path)
	        : m_path{ fmt::format("/{}/{}", TBasePath.value, path) }
	{
	}

	std::string get_path() const
	{
		return m_path;
	}

    private:
	std::string m_path;
};

using core_shader_file_t = file_type<str_lit("shaders")>;
using texture_file_t = file_type<str_lit("textures")>;

class filesystem {
	template<typename T>
	void read_file_internal(const std::string &file_name, T *out_buf) const
	{
		if (auto *file = PHYSFS_openRead(file_name.c_str())) {
			i64 file_size = PHYSFS_fileLength(file);
			out_buf->resize(file_size);
			PHYSFS_readBytes(file, out_buf->data(),
			                 file_size); // assume success for now
			PHYSFS_close(file);
		} else {
			SPDLOG_ERROR("Cannot open '{}': {}", file_name, PHYSFS_getLastError());
		}
	}

    public:
	~filesystem();

	filesystem(const filesystem &other) = delete;
	filesystem &operator=(const filesystem &other) = default;
	filesystem(filesystem &&other) noexcept = default;
	filesystem &operator=(filesystem &&other) noexcept = default;

	template<typename TOutput, str_lit BaseDir>
	TOutput read_file(const file_type<BaseDir> &file_name) const
	{
		auto    p = file_name.get_path();
		TOutput buf;
		read_file_internal(p, &buf);
		return buf;
	}

	// NOLINTNEXTLINE(*-convert-member-functions-to-static)
	bool file_exists(const std::string &file_name) const
	{
		return PHYSFS_exists(file_name.c_str());
	}

    private:
	explicit filesystem(char **platform_argument);

	std::string m_content_root;

	friend singleton<filesystem>;
};

// ReSharper disable once CppInconsistentNaming
DECLARE_SINGLETON(fs, filesystem);
} // namespace core
