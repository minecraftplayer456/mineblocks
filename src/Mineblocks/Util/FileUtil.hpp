#pragma once

namespace Mineblocks {
    EXCEPTION(Exception, FileException)

    class FileUtil {
      public:
        static auto GetFileContents(const std::string& filePath) -> std::string;
    };
} // namespace Mineblocks