#pragma once

namespace Mineblocks {
    EXCEPTION(Exception, FileException);

    class FileUtil {
      public:
        static auto GetFileContents(const std::string_view& filePath) -> std::string;
    };
} // namespace Mineblocks