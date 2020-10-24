#pragma once

#include <chrono>
#include <string>

namespace engine::maths {
    class Time {
      public:
        Time() = default;

        template <typename Rep, typename Period>
        constexpr Time(const std::chrono::duration<Rep, Period>& duration)
            : m_value(
                  std::chrono::duration_cast<std::chrono::microseconds>(duration).count())
        {
        }

        template <typename Rep = float>
        static constexpr Time seconds(const Rep& seconds)
        {
            return Time(std::chrono::duration<Rep>(seconds));
        }

        template <typename Rep = int32_t>
        static constexpr Time milliSeconds(const Rep& milliSeconds)
        {
            return Time(std::chrono::duration<Rep>(milliSeconds));
        }

        template <typename Rep = int64_t>
        static constexpr Time microSeconds(const Rep& microSeconds)
        {
            return Time(std::chrono::duration<Rep>(microSeconds));
        }

        template <typename T = float>
        constexpr auto asSeconds() const
        {
            return static_cast<T>(m_value.count() / static_cast<T>(1000000));
        }

        template <typename T = uint32_t>
        constexpr auto asMilliSeconds() const
        {
            return static_cast<T>(m_value.count() / static_cast<T>(1000));
        }

        template <typename T = uint64_t>
        constexpr auto asMicroSeconds() const
        {
            return static_cast<T>(m_value.count());
        }

        static Time now();

        static std::string getDateTime(const std::string& format = "%H:%M:%S %d-%m-%Y");

        template <typename Rep, typename Period>
        constexpr operator std::chrono::duration<Rep, Period>() const
        {
            return std::chrono::duration_cast<std::chrono::duration<Rep, Period>>(
                m_value);
        }

        constexpr bool operator==(const Time& rhs) const;
        constexpr bool operator!=(const Time& rhs) const;
        constexpr bool operator<(const Time& rhs) const;
        constexpr bool operator<=(const Time& rhs) const;
        constexpr bool operator>(const Time& rhs) const;
        constexpr bool operator>=(const Time& rhs) const;

        constexpr Time operator-() const;

        friend constexpr Time operator+(const Time& lhs, const Time& rhs);
        friend constexpr Time operator-(const Time& lhs, const Time& rhs);
        friend constexpr Time operator*(const Time& lhs, float rhs);
        friend constexpr Time operator*(const Time& lhs, int64_t rhs);
        friend constexpr Time operator*(float lhs, const Time& rhs);
        friend constexpr Time operator*(int64_t lhs, const Time& rhs);
        friend constexpr Time operator/(const Time& lhs, float rhs);
        friend constexpr Time operator/(const Time& lhs, int64_t rhs);
        friend constexpr double operator/(const Time& lhs, const Time& rhs);

        constexpr Time& operator+=(const Time& rhs);
        constexpr Time& operator-=(const Time& rhs);
        constexpr Time& operator*=(float rhs);
        constexpr Time& operator*=(int64_t rhs);
        constexpr Time& operator/=(float rhs);
        constexpr Time& operator/=(int64_t rhs);

      private:
        std::chrono::microseconds m_value{};
    };

    class ElapsedTime {
      public:
        ElapsedTime(const Time& interval = Time::seconds(-1));

        [[nodiscard]] const Time& getStartTime() const;

        void setStartTime(const Time& startTime);

        [[nodiscard]] const Time& getInterval() const;

        void setInterval(const Time& interval);

        uint32_t getElapsed();

      private:
        Time m_startTime;
        Time m_interval;
    };

    class DeltaTime {
      public:
        void update();

        Time currentTime;
        Time lastTime;
        Time change;
    };

    class ChangePerSecond {
      public:
        void update(const Time& time);

        uint32_t valueTemp = 0;
        uint32_t value = 0;
        Time valueTime;
    };
} // namespace engine::maths
