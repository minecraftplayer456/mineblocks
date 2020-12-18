#pragma once

#include <stdexcept>

#include <fmt/format.h>

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define EXCEPTION_LOC __FUNCTION__, __FILENAME__, __LINE__

#define EXCEPTION(Super, Current)                                                        \
    class Current : public Super {                                                       \
      public:                                                                            \
        Current(const char* description, const char* function = "?",                     \
                const char* file = "?", int line = -1)                                   \
            : Super(#Current, description, function, file, line)                         \
        {                                                                                \
        }                                                                                \
                                                                                         \
        template <typename... Args>                                                      \
        Current(const char* description, const char* function = "?",                     \
                const char* file = "?", int line = -1, Args&&... args)                   \
            : Super(#Current, description, function, file, line,                         \
                    std::forward<Args>(args)...)                                         \
        {                                                                                \
        }                                                                                \
    };

#define THROW(Exception, Msg)                                                            \
    {                                                                                    \
        throw(Exception(Msg, EXCEPTION_LOC));                                            \
    }

#define THROW_ARGS(Exception, Msg, ...)                                                  \
    {                                                                                    \
        throw(Exception(Msg, EXCEPTION_LOC, __VA_ARGS__));                               \
    }

namespace Mineblocks {
    class Exception : std::exception {
      public:
        Exception(const char* name, const std::basic_string<char>& description,
                  const char* function, const char* file, int line);

        template <typename... Args>
        Exception(const char* name, const std::basic_string<char>& description,
                  const char* function = "?", const char* file = "?", int line = -1,
                  Args&&... args)
            : Exception(name, fmt::format(description, std::forward<Args>(args)...),
                        function, file, line)
        {
        }

        [[nodiscard]] auto what() const noexcept -> const char* override;

        [[nodiscard]] auto GetName() const -> const char*;
        [[nodiscard]] auto GetDescription() const -> std::basic_string<char>;
        [[nodiscard]] auto GetFunction() const -> const char*;
        [[nodiscard]] auto GetFile() const -> const char*;
        [[nodiscard]] auto GetLine() const -> int;

      protected:
        std::string msg;

        const char* name;
        const std::basic_string<char> description;
        const char* function;
        const char* file;
        int line;
    };
} // namespace Mineblocks
