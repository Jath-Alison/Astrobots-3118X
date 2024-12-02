#pragma once

#include <chrono>

/**
 * @brief A Point in time
 *
 * A TimePoint is just an alias for
 * std::chrono::time_point<std::chrono::high_resolution_clock>. TimePoint is
 * just way easier to type and makes the code more readable
 */
typedef std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint;

class Timer
{
public:
    Timer(double duration);

    void reset();

    double getTimePassed();
    bool expired();

private:
    TimePoint m_start;
    double m_duration;
};