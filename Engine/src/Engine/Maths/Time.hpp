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
        static constexpr auto Seconds(const Rep& seconds) -> Time
        {
            return Time(std::chrono::duration<Rep>(seconds));
        }

        template <typename Rep = int32_t>
        static constexpr auto Milliseconds(const Rep& milliSeconds) -> Time
        {
            return Time(std::chrono::duration<Rep, std::milli>(milliSeconds));
        }

        template <typename Rep = int64_t>
        static constexpr auto Microseconds(const Rep& microSeconds) -> Time
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

        static auto Now() -> Time;

        static auto GetDateTime(const std::string& format = "%H:%M:%S %d-%m-%Y")
            -> std::string;

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
        ElapsedTime(const Time& interval = Time::Seconds(-1));

        [[nodiscard]] auto GetStartTime() const -> const Time&;

        void SetStartTime(const Time& startTime);

        [[nodiscard]] auto GetInterval() const -> const Time&;

        void SetInterval(const Time& interval);

        auto GetElapsed() -> uint32_t;

      private:
        Time startTime;
        Time interval;
    };

    class DeltaTime {
      public:
        void Update();

        Time CurrentTime;
        Time LastTime;
        Time Change;
    };

    class ChangePerSecond {
      public:
        void Update(const Time& time);

        uint32_t ValueTemp = 0;
        uint32_t Value = 0;
        Time ValueTime;
    };
} // namespace Engine