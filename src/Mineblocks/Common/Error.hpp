#pragma once

#include <stdexcept>

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define EXCEPTION_LOC __FUNCTION__, __FILENAME__, __LINE__

#define EXCEPTION(Super, Current)                                                        \
    class Current : public Super {                                                       \
      public:                                                                            \
        Current(const char* description, const char* function = "?",                     \
                const char* file = "?", const int line = -1)                             \
            : Super(#Current, description, function, file, line)                         \
        {                                                                                \
        }                                                                                \
    };

#define THROW(Exception, Msg)                                                            \
    {                                                                                    \
        throw(Exception(Msg, EXCEPTION_LOC));                                          \
    }

namespace Mineblocks {
    class Exception : std::exception {
      public:
        Exception(const char* name, const char* description, const char* function,
                  const char* file, int line);

        [[nodiscard]] auto what() const noexcept -> const char* override;

        [[nodiscard]] auto GetName() const -> const char*;
        [[nodiscard]] auto GetDescription() const -> const char*;
        [[nodiscard]] auto GetFunction() const -> const char*;
        [[nodiscard]] auto GetFile() const -> const char*;
        [[nodiscard]] auto GetLine() const -> int;

      protected:
        std::string msg;

        const char* name;
        const char* description;
        const char* function;
        const char* file;
        int line;
    };
} // namespace Mineblocks
