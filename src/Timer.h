#pragma once
#include <chrono>
#include <iostream>
#include <iomanip>

const std::chrono::seconds DEFAULT_DURATION = std::chrono::seconds(15 * 60);

#include <chrono>
#include <iostream>
#include <iomanip>

class Timer {
public:
    Timer() : m_maxDuration(0), m_running(false) {}

    void start(const std::chrono::seconds duration) {
        m_startTime = std::chrono::steady_clock::now();
        m_maxDuration = duration;
        m_running = true;
    }

    bool isTimeUp() const {
        if (m_running) {
            const auto currentTime = std::chrono::steady_clock::now();
            const auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - m_startTime);
            return elapsedTime >= m_maxDuration;
        }
        return false; // Timer not started or already stopped
    }

    std::chrono::seconds elapsedTime() const {
        if (m_running) {
            const auto currentTime = std::chrono::steady_clock::now();
            const auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - m_startTime);
            return elapsedTime;
        }
        return std::chrono::seconds(0); // Timer not started or already stopped
    }

    std::chrono::seconds timeLeft() const {
        if (m_running) {
            const auto remainingTime = m_maxDuration - elapsedTime();
            return (remainingTime > std::chrono::seconds(0)) ? remainingTime : std::chrono::seconds(0);
        }
        return std::chrono::seconds(0); // Timer not started or already stopped
    }

    void stop() {
        m_running = false;
    }

private:
    std::chrono::steady_clock::time_point m_startTime;
    std::chrono::seconds m_maxDuration;
    bool m_running;
};

