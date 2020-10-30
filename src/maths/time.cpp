#include "time.hpp"

#include <cmath>
#include <iomanip>
#include <sstream>

namespace mineblocks {
    Time Time::now()
    {
        static const auto localEpoch = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now() - localEpoch);
    }

    std::string Time::getDateTime(const std::string& format)
    {
        auto now = std::chrono::system_clock::now();
        auto timeT = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&timeT), format.c_str());
        return ss.str();
    }

    constexpr bool Time::operator==(const Time& rhs) const
    {
        return m_value == rhs.m_value;
    }

    constexpr bool Time::operator!=(const Time& rhs) const
    {
        return m_value != rhs.m_value;
    }

    constexpr bool Time::operator<(const Time& rhs) const
    {
        return m_value < rhs.m_value;
    }

    constexpr bool Time::operator<=(const Time& rhs) const
    {
        return m_value <= rhs.m_value;
    }

    constexpr bool Time::operator>(const Time& rhs) const
    {
        return m_value > rhs.m_value;
    }

    constexpr bool Time::operator>=(const Time& rhs) const
    {
        return m_value >= rhs.m_value;
    }

    constexpr Time Time::operator-() const
    {
        return Time(-m_value);
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
        return lhs.m_value + rhs.m_value;
    }

    constexpr Time operator-(const Time& lhs, const Time& rhs)
    {
        return lhs.m_value - rhs.m_value;
    }

    constexpr Time operator*(const Time& lhs, float rhs)
    {
        return lhs.m_value * rhs;
    }

    constexpr Time operator*(const Time& lhs, int64_t rhs)
    {
        return lhs.m_value * rhs;
    }

    constexpr Time operator*(float lhs, const Time& rhs)
    {
        return lhs * rhs.m_value;
    }

    constexpr Time operator*(int64_t lhs, const Time& rhs)
    {
        return lhs * rhs.m_value;
    }

    constexpr Time operator/(const Time& lhs, float rhs)
    {
        return lhs.m_value / rhs;
    }

    constexpr Time operator/(const Time& lhs, int64_t rhs)
    {
        return lhs.m_value / rhs;
    }

    constexpr double operator/(const Time& lhs, const Time& rhs)
    {
        return lhs.m_value / rhs.m_value;
    }

    ElapsedTime::ElapsedTime(const Time& interval)
        : m_startTime(Time::now())
        , m_interval(interval)
    {
    }

    const Time& ElapsedTime::getStartTime() const
    {
        return m_startTime;
    }

    void ElapsedTime::setStartTime(const Time& startTime)
    {
        m_startTime = startTime;
    }

    const Time& ElapsedTime::getInterval() const
    {
        return m_interval;
    }

    void ElapsedTime::setInterval(const Time& interval)
    {
        m_interval = interval;
    }

    uint32_t ElapsedTime::getElapsed()
    {
        if (m_interval.asMicroSeconds<int>() < 0) {
            return -1;
        }

        auto now = Time::now();
        auto elapsed =
            static_cast<uint32_t>(std::floor((now - m_startTime) / m_interval));

        if (elapsed != 0.0f) {
            m_startTime = now;
        }

        return elapsed;
    }

    void DeltaTime::update()
    {
        currentTime = Time::now();
        change = currentTime - lastTime;
        lastTime = currentTime;
    }

    void ChangePerSecond::update(const Time& time)
    {
        valueTemp++;

        if (std::floor(time.asSeconds()) > std::floor(valueTime.asSeconds())) {
            value = valueTemp;
            valueTemp = 0;
        }

        valueTime = time;
    }
} // namespace mineblocks