#include "FileUtil.hpp"

namespace Mineblocks {
    auto FileUtil::GetFileContents(const char* filePath) -> std::string
    {
        std::ifstream inFile(filePath);

        if (!inFile.is_open()) {
            THROW_ARGS(FileException, "Couldn't open file: {}", filePath)
        }

        std::stringstream stream;

        stream << inFile.rdbuf();
        return stream.str();
    }
} // namespace Mineblocks