#pragma once

namespace Mineblocks {
    EXCEPTION(Exception, FileException)

    class FileUtil {
      public:
        static auto GetFileContents(const char* filePath) -> std::string;
    };
} // namespace Mineblocks