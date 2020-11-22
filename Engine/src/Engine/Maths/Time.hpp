#pragma once

namespace Engine {
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
        static constexpr Time Seconds(const Rep& seconds)
        {
            return Time(std::chrono::duration<Rep>(seconds));
        }

        template <typename Rep = int32_t>
        static constexpr Time Milliseconds(const Rep& milliSeconds)
        {
            return Time(std::chrono::duration<Rep, std::milli>(milliSeconds));
        }

        template <typename Rep = int64_t>
        static constexpr Time Microseconds(const Rep& microSeconds)
        {
            return Time(std::chrono::duration<Rep, std::micro>(microSeconds));
        }

        template <typename T = float>
        constexpr auto AsSeconds() const
        {
            return static_cast<T>(value.count() / static_cast<T>(1000000));
        }

        template <typename T = uint32_t>
        constexpr auto AsMilliSeconds() const
        {
            return static_cast<T>(value.count() / static_cast<T>(1000));
        }

        template <typename T = uint64_t>
        constexpr auto AsMicroSeconds() const
        {
            return static_cast<T>(value.count());
        }

        static Time Now();

        static std::string GetDateTime(const std::string& format = "%H:%M:%S %d-%m-%Y");

        template <typename Rep, typename Period>
        constexpr operator std::chrono::duration<Rep, Period>() const
        {
            return std::chrono::duration_cast<std::chrono::duration<Rep, Period>>(value);
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
        std::chrono::microseconds value{};
    };

    class ElapsedTime {
      public:
        ElapsedTime(const Time& interval = Time::Seconds(-1));

        [[nodiscard]] const Time& GetStartTime() const;

        void SetStartTime(const Time& startTime);

        [[nodiscard]] const Time& GetInterval() const;

        void SetInterval(const Time& interval);

        uint32_t GetElapsed();

      private:
        Time startTime;
        Time interval;
    };

    class DeltaTime {
      public:
        void Update();

        Time currentTime;
        Time lastTime;
        Time change;
    };

    class ChangePerSecond {
      public:
        void Update(const Time& time);

        uint32_t valueTemp = 0;
        uint32_t value = 0;
        Time valueTime;
    };
} // namespace Engine