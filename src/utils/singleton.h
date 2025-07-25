#pragma once

#include "utils/assertions.h"

#include <spdlog/spdlog.h>

#include <string>

namespace core
{
    template<typename T>
    class Singleton
    {
    public:
        static const T& Instance()
        {
            CHECK_F(s_Instance != nullptr, "Singleton '{}' not initialized.", s_Name);
            return *s_Instance;
        }

        template<typename... Args>
        static void Create(Args&&... args)
        {
            SPDLOG_INFO("Initializing '{}' singleton.", s_Name);
            if (!s_Instance)
            {
                s_Instance = new T{std::forward<Args>(args)...};
            }
        };

        static void Destroy()
        {
            SPDLOG_INFO("De-initializing '{}' singleton.", s_Name);
            delete s_Instance;
        }

    private:
        static T*               s_Instance;
        static std::string_view s_Name;
    };

#define DECLARE_SINGLETON(varName, Type)                     \
    template<>                                               \
    inline Type* Singleton<Type>::s_Instance = nullptr;      \
    template<>                                               \
    inline std::string_view Singleton<Type>::s_Name = #Type; \
                                                             \
    using varName = Singleton<Type>;

} // namespace core
