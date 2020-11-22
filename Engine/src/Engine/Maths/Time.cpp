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

    constexpr bool Time::operator==(const Time& rhs) const
    {
        return value == rhs.value;
    }

    constexpr bool Time::operator!=(const Time& rhs) const
    {
        return value != rhs.value;
    }

    constexpr bool Time::operator<(const Time& rhs) const
    {
        return value < rhs.value;
    }

    constexpr bool Time::operator<=(const Time& rhs) const
    {
        return value <= rhs.value;
    }

    constexpr bool Time::operator>(const Time& rhs) const
    {
        return value > rhs.value;
    }

    constexpr bool Time::operator>=(const Time& rhs) const
    {
        return value >= rhs.value;
    }

    constexpr Time Time::operator-() const
    {
        return Time(-value);
    }

    constexpr Time& Time::operator+=(const Time& rhs)
    {
        return *this = *this + rhs;
    }

    constexpr Time& Time::operator-=(const Time& rhs)
    {
        return *this = *this - rhs;
    }

    constexpr Time& Time::operator*=(float rhs)
    {
        return *this = *this * rhs;
    }

    constexpr Time& Time::operator*=(int64_t rhs)
    {
        return *this = *this * rhs;
    }

    constexpr Time& Time::operator/=(float rhs)
    {
        return *this = *this / rhs;
    }

    constexpr Time& Time::operator/=(int64_t rhs)
    {
        return *this = *this / rhs;
    }

    constexpr Time operator+(const Time& lhs, const Time& rhs)
    {
        return lhs.value + rhs.value;
    }

    constexpr Time operator-(const Time& lhs, const Time& rhs)
    {
        return lhs.value - rhs.value;
    }

    constexpr Time operator*(const Time& lhs, float rhs)
    {
        return lhs.value * rhs;
    }

    constexpr Time operator*(const Time& lhs, int64_t rhs)
    {
        return lhs.value * rhs;
    }

    constexpr Time operator*(float lhs, const Time& rhs)
    {
        return lhs * rhs.value;
    }

    constexpr Time operator*(int64_t lhs, const Time& rhs)
    {
        return lhs * rhs.value;
    }

    constexpr Time operator/(const Time& lhs, float rhs)
    {
        return lhs.value / rhs;
    }

    constexpr Time operator/(const Time& lhs, int64_t rhs)
    {
        return lhs.value / rhs;
    }

    constexpr double operator/(const Time& lhs, const Time& rhs)
    {
        return lhs.value / rhs.value;
    }

    ElapsedTime::ElapsedTime(const Time& interval)
        : startTime(Time::Now())
        , interval(interval)
    {
    }

    const Time& ElapsedTime::GetStartTime() const
    {
        return startTime;
    }

    void ElapsedTime::SetStartTime(const Time& startTime)
    {
        this->startTime = startTime;
    }

    const Time& ElapsedTime::GetInterval() const
    {
        return interval;
    }

    void ElapsedTime::SetInterval(const Time& interval)
    {
        this->interval = interval;
    }

    uint32_t ElapsedTime::GetElapsed()
    {
        if (interval.AsMicroSeconds<int>() < 0) {
            return -1;
        }

        auto now = Time::Now();
        auto elapsed = static_cast<uint32_t>(std::floor((now - startTime) / interval));

        if (elapsed != 0.0f) {
            startTime = now;
        }

        return elapsed;
    }

    void DeltaTime::Update()
    {
        currentTime = Time::Now();
        change = currentTime - lastTime;
        lastTime = currentTime;
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
} // namespace Engine