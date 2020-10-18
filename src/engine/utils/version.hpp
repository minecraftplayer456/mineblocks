#pragma once

namespace engine::utils {
    class Version {
      public:
        Version(int major, int minor, int patch);

        int getMajor() const;
        int getMinor() const;
        int getPatch() const;

      private:
        int m_major;
        int m_minor;
        int m_patch;
    };
} // namespace engine::utils