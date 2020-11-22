#include "Time.hpp"

namespace Engine {
    Time Time::Now()
    {
        static const auto localEpoch = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now() - localEpoch);
    }

    std::string Time::GetDateTime(const std::string& format)
    {
        auto now = std::chrono::system_clock::now();
        auto timeT = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&timeT), format.c_str());
        return ss.str();
    }

    constexpr auto Time::operator==(const Time& rhs) const -> bool
    {
        return value == rhs.value;
    }

    constexpr auto Time::operator!=(const Time& rhs) const -> bool
    {
        return value != rhs.value;
    }

    constexpr auto Time::operator<(const Time& rhs) const -> bool
    {
        return value < rhs.value;
    }

    constexpr auto Time::operator<=(const Time& rhs) const -> bool
    {
        return value <= rhs.value;
    }

    constexpr auto Time::operator>(const Time& rhs) const -> bool
    {
        return value > rhs.value;
    }

    constexpr auto Time::operator>=(const Time& rhs) const -> bool
    {
        return value >= rhs.value;
    }

    constexpr auto Time::operator-() const -> Time
    {
        return Time(-value);
    }

    constexpr auto Time::operator+=(const Time& rhs) -> Time&
    {
        return *this = *this + rhs;
    }

    constexpr auto Time::operator-=(const Time& rhs) -> Time&
    {
        return *this = *this - rhs;
    }

    constexpr auto Time::operator*=(float rhs) -> Time&
    {
        return *this = *this * rhs;
    }

    constexpr auto Time::operator*=(int64_t rhs) -> Time&
    {
        return *this = *this * rhs;
    }

    constexpr auto Time::operator/=(float rhs) -> Time&
    {
        return *this = *this / rhs;
    }

    constexpr auto Time::operator/=(int64_t rhs) -> Time&
    {
        return *this = *this / rhs;
    }

    constexpr auto operator+(const Time& lhs, const Time& rhs) -> Time
    {
        return lhs.value + rhs.value;
    }

    constexpr auto operator-(const Time& lhs, const Time& rhs) -> Time
    {
        return lhs.value - rhs.value;
    }

    constexpr auto operator*(const Time& lhs, float rhs) -> Time
    {
        return lhs.value * rhs;
    }

    constexpr auto operator*(const Time& lhs, int64_t rhs) -> Time
    {
        return lhs.value * rhs;
    }

    constexpr auto operator*(float lhs, const Time& rhs) -> Time
    {
        return lhs * rhs.value;
    }

    constexpr auto operator*(int64_t lhs, const Time& rhs) -> Time
    {
        return lhs * rhs.value;
    }

    constexpr auto operator/(const Time& lhs, float rhs) -> Time
    {
        return lhs.value / rhs;
    }

    constexpr auto operator/(const Time& lhs, int64_t rhs) -> Time
    {
        return lhs.value / rhs;
    }

    constexpr auto operator/(const Time& lhs, const Time& rhs) -> double
    {
        return static_cast<double>(lhs.value.count()) /
               static_cast<double>(rhs.value.count());
    }

    ElapsedTime::ElapsedTime(const Time& interval)
        : startTime(Time::Now())
        , interval(interval)
    {
    }

    auto ElapsedTime::GetStartTime() const -> const Time&
    {
        return startTime;
    }

    void ElapsedTime::SetStartTime(const Time& startTime)
    {
        this->startTime = startTime;
    }

    auto ElapsedTime::GetInterval() const -> const Time&
    {
        return interval;
    }

    void ElapsedTime::SetInterval(const Time& interval)
    {
        this->interval = interval;
    }

    auto ElapsedTime::GetElapsed() -> uint32_t
    {
        if (interval.AsMicroSeconds<int>() < 0) {
            return static_cast<uint32_t>(-1);
        }

        Time now = Time::Now();
        uint32_t elapsed =
            static_cast<uint32_t>(std::floor((now - startTime) / interval));

        if (elapsed != 0.0f) {
            startTime = now;
        }

        return elapsed;
    }

    void DeltaTime::Update()
    {
        CurrentTime = Time::Now();
        Change = CurrentTime - LastTime;
        LastTime = CurrentTime;
    }

    void ChangePerSecond::Update(const Time& time)
    {
        ValueTemp++;

        if (std::floor(time.AsSeconds()) > std::floor(ValueTime.AsSeconds())) {
            Value = ValueTemp;
            ValueTemp = 0;
        }

        ValueTime = time;
    }
} // namespace Engine