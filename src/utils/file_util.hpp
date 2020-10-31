#pragma once

#include <fstream>
#include <vector>

namespace mineblocks {
    class FileUtil {
      public:
        static std::vector<char> readFile(const std::string& path);
    };
} // namespace mineblocks