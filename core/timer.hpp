#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>


namespace Core
{
    typedef std::chrono::high_resolution_clock TimerHighResolution;
    typedef std::chrono::steady_clock          TimerSteady;
    typedef std::chrono::system_clock          TimerSystem;

    typedef std::chrono::hours                 TimerHours;
    typedef std::chrono::minutes               TimerMinutes;
    typedef std::chrono::seconds               TimerSeconds;
    typedef std::chrono::milliseconds          TimerMilliseconds;
    typedef std::chrono::microseconds          TimerMicroseconds;
    typedef std::chrono::nanoseconds           TimerNanoseconds;

    template<class Clock = TimerHighResolution, class ClockPrecision = TimerMilliseconds>
    class Timer
    {
    public:
        Timer() : m_isRunning(false), m_isPaused(false) {}

        void start()
        {
            m_startTime   = Clock::now();
            m_isRunning   = true;
            m_isPaused    = false;
            m_accumulator = 0;
        }

        void stop()
        {
            m_isRunning = false;
        }

        void pause()
        {
            if(m_isRunning && (!m_isPaused))
            {
                m_isPaused = true;
                std::chrono::duration<int> time = Clock::now() - m_startTime;
                m_accumulator += std::chrono::duration_cast<ClockPrecision>(time).count();
            }
        }

        void unpause()
        {
            m_startTime = Clock::now();
            m_isPaused = false;
        }

        int getTicks()
        {
            if(!m_isRunning)
                return 0;

            if(m_isPaused)
                return m_accumulator;

            std::chrono::duration<double> time = Clock::now() - m_startTime;
            return std::chrono::duration_cast<ClockPrecision>(time).count() + m_accumulator;
        }

        inline bool isPaused()
        {
            return m_isPaused;
        }

        inline bool isRunning()
        {
            return m_isRunning;
        }

        static auto getCurrentTime() -> decltype(Clock::now())
        {
            return Clock::now();
        }

    private:
        typedef typename Clock::time_point TimePoint;

        TimePoint m_startTime;
        int  m_accumulator;
        bool m_isRunning;
        bool m_isPaused;
    };
}

#endif
