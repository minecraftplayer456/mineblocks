#include "Error.hpp"

namespace Mineblocks {
    Exception::Exception(const char* name, const char* description, const char* function,
                         const char* file, const int line)
        : name(name)
        , description(description)
        , function(function)
        , file(file)
        , line(line)
    {
        std::ostringstream str;
        str << "(<" << name << "> in " << function << " at " << file << ":" << line
            << "): " << description;
        msg = str.str();
    }

    auto Exception::what() const noexcept -> const char*
    {
        return msg.c_str();
    }
    auto Exception::GetName() const -> const char*
    {
        return name;
    }

    auto Exception::GetDescription() const -> const char*
    {
        return description;
    }

    auto Exception::GetFunction() const -> const char*
    {
        return function;
    }

    auto Exception::GetFile() const -> const char*
    {
        return file;
    }

    auto Exception::GetLine() const -> int
    {
        return line;
    }

} // namespace Mineblocks