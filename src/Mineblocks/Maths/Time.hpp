// Copied from https://github.com/EQMG/Acid/blob/master/Sources/Maths

#pragma once

#include <chrono>

namespace Mineblocks {
    using namespace std::chrono_literals;

    class Time {
      public:
        Time() = default;

        template <typename Rep, typename Period>
        constexpr Time(const std::chrono::duration<Rep, Period>& duration)
            : value(
                  std::chrono::duration_cast<std::chrono::microseconds>(duration).count())
        {
        }

        template <typename Rep = float>
        static constexpr auto Seconds(const Rep& seconds) -> Time
        {
            return Time(std::chrono::duration<Rep>(seconds));
        }

        template <typename Rep = int32_t>
        static constexpr auto Milliseconds(const Rep& milliseconds) -> Time
        {
            return Time(std::chrono::duration<Rep, std::micro>(milliseconds));
        }

        template <typename Rep = int64_t>
        static constexpr auto Microseconds(const Rep& microseconds) -> Time
        {
            return Time(std::chrono::duration<Rep, std::micro>(microseconds));
        }

        template <typename T = float>
        constexpr auto AsSeconds() const
        {
            return static_cast<T>(value.count()) / static_cast<T>(1000000);
        }

        template <typename T = int32_t>
        constexpr auto AsMilliseconds() const
        {
            return static_cast<T>(value.count()) / static_cast<T>(1000);
        }

        template <typename T = int64_t>
        constexpr auto AsMicroseconds() const
        {
            return static_cast<T>(value.count());
        }

        static auto Now() -> Time
        {
            static const auto LocalEpoch = std::chrono::high_resolution_clock::now();
            return std::chrono::duration_cast<std::chrono::microseconds>(
                std::chrono::high_resolution_clock::now() - LocalEpoch);
        }

        static auto GetDateTime(const std::string& format = "%Y-%m-%d %H:%M:%S")
            -> std::string
        {
            auto now = std::chrono::system_clock::now();
            auto timeT = std::chrono::system_clock::to_time_t(now);

            std::stringstream ss;
            ss << std::put_time(std::localtime(&timeT), format.c_str());
            return ss.str();
        }

        template <typename Rep, typename Period>
        constexpr operator std::chrono::duration<Rep, Period>() const
        {
            return std::chrono::duration_cast<std::chrono::duration<Rep, Period>>(value);
        }

        constexpr auto operator==(const Time& rhs) const -> bool;
        constexpr auto operator!=(const Time& rhs) const -> bool;
        constexpr auto operator<(const Time& rhs) const -> bool;
        constexpr auto operator<=(const Time& rhs) const -> bool;
        constexpr auto operator>(const Time& rhs) const -> bool;
        constexpr auto operator>=(const Time& rhs) const -> bool;

        constexpr auto operator-() const -> Time;

        friend constexpr auto operator+(const Time& lhs, const Time& rhs) -> Time;
        friend constexpr auto operator-(const Time& lhs, const Time& rhs) -> Time;
        friend constexpr auto operator*(const Time& lhs, float rhs) -> Time;
        friend constexpr auto operator*(const Time& lhs, int64_t rhs) -> Time;
        friend constexpr auto operator*(float lhs, const Time& rhs) -> Time;
        friend constexpr auto operator*(int64_t lhs, const Time& rhs) -> Time;
        friend constexpr auto operator/(const Time& lhs, float rhs) -> Time;
        friend constexpr auto operator/(const Time& lhs, int64_t rhs) -> Time;
        friend constexpr auto operator/(const Time& lhs, const Time& rhs) -> double;

        constexpr auto operator+=(const Time& rhs) -> Time&;
        constexpr auto operator-=(const Time& rhs) -> Time&;
        constexpr auto operator*=(float rhs) -> Time&;
        constexpr auto operator*=(int64_t rhs) -> Time&;
        constexpr auto operator/=(float rhs) -> Time&;
        constexpr auto operator/=(int64_t rhs) -> Time&;

      private:
        std::chrono::microseconds value{};
    };

    class ElapsedTime {
      public:
        explicit ElapsedTime(const Time& interval = -1s);

        auto GetElapsed() -> uint32_t;

        [[nodiscard]] auto GetStartTime() const -> const Time&;
        [[nodiscard]] auto GetInterval() const -> const Time&;

        void SetInterval(const Time& interval);
        void SetStartTime(const Time& startTime);

      private:
        Time startTime;
        Time interval;
    };

    class Delta {
      public:
        void Update();

        Time currentFrameTime;
        Time lastFrameTime;
        Time change;
    };

    class ChangePerSecond {
      public:
        void Update(const Time& time);

        uint32_t valueTemp = 0;
        uint32_t value = 0;
        Time valueTime;
    };
} // namespace Mineblocks