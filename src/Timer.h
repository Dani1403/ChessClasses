#pragma once
#include "utilities.h"

class Timer
{
public:

	// Constructor
	Timer() : m_duration(std::chrono::duration<double>(0)) {}

	/*
	 * Start the timer.
	 */
	void start()
	{
		m_start = std::chrono::system_clock::now();
		m_isRunning = true;
	}

	/*
	 * Stop the timer.
	 * Calculate the duration of the timer.
	 */
	void stop()
	{
		m_end = std::chrono::system_clock::now();
		m_duration += m_end - m_start;
		m_isRunning = false;
	}

	/*
	 * Get the duration of the timer.
	 * @return the duration of the timer.
	 */
	std::chrono::duration<double> getDuration() const
	{
		return m_duration;
	}

	/*
	 * Get the duration of the timer when it is on.
	 * @return the duration of the timer when it is on.
	 */
	std::chrono::duration<double> getDurationWhenOn() const
	{
		if (!m_isRunning)
			return m_duration;
		return m_duration + std::chrono::system_clock::now() - m_start;
	}

private:
	std::chrono::time_point<std::chrono::system_clock> m_start, m_end;
	std::chrono::duration<double> m_duration;
	bool m_isRunning = false;
};