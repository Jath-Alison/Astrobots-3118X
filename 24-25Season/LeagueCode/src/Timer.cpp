#include "Timer.h"

Timer::Timer(double duration) : m_duration(duration)
{
    m_start = std::chrono::high_resolution_clock::now();
}

void Timer::reset()
{
    m_start = std::chrono::high_resolution_clock::now();
}

double Timer::getTimePassed()
{
    auto current_time = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(current_time - m_start).count() / 1000000.0;
}

bool Timer::expired()
{
    return getTimePassed() >= m_duration;
}
