#pragma once

#include "utils/assertions.h"

#include <spdlog/spdlog.h>

#include <string>

namespace core
{
template<typename T>
class singleton {
    public:
	static const T &instance()
	{
		check_f(s_instance != nullptr, "Singleton '{}' not initialized.", s_name);
		return *s_instance;
	}

	template<typename... Args>
	static void create(Args &&...args)
	{
		SPDLOG_INFO("Initializing '{}' singleton.", s_name);
		if (!s_instance) {
			s_instance = new T{ std::forward<Args>(args)... };
		}
	};

	static void destroy()
	{
		SPDLOG_INFO("De-initializing '{}' singleton.", s_name);
		delete s_instance;
	}

    private:
	static T               *s_instance;
	static std::string_view s_name;
};

#define DECLARE_SINGLETON(var_name, type)                        \
	template<>                                               \
	inline type *singleton<type>::s_instance = nullptr;      \
	template<>                                               \
	inline std::string_view singleton<type>::s_name = #type; \
                                                                 \
	using var_name = singleton<type>;

} // namespace core
