// Copied from https://github.com/EQMG/Acid/blob/master/Sources/Maths

#include "Time.hpp"

namespace Mineblocks {
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
        return rhs * lhs;
    }

    constexpr auto operator*(int64_t lhs, const Time& rhs) -> Time
    {
        return rhs * lhs;
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

    ElapsedTime::ElapsedTime(const Time& interval)
        : startTime(Time::Now())
        , interval(interval)
    {
    }

    auto ElapsedTime::GetElapsed() -> uint32_t
    {
        auto now = Time::Now();
        auto elapsed = static_cast<uint32_t>(std::floor((now - startTime) / interval));

        if (elapsed != 0.0F) {
            startTime = now;
        }

        return elapsed;
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

    void Delta::Update()
    {
        currentFrameTime = Time::Now();
        change = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;
    }

    void ChangePerSecond::Update(const Time& time)
    {
        valueTemp++;

        if (std::floor(time.AsSeconds()) > std::floor(valueTime.AsSeconds())) {
            value = valueTemp;
            valueTemp = 0;
        }

        valueTime = time;
    }
} // namespace Mineblocks