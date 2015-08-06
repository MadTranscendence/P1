#ifndef FRAME_TIMER_HPP
#define FRAME_TIMER_HPP

#include "timer.hpp"


namespace Core
{
    class FrameTimer
    {
    public:
        FrameTimer() = default;
        ~FrameTimer() = default;

        void start()
        {
            m_didFpsChanged = false;

            m_prevTime = m_deltaTime = m_accumulator = 0.0;
            m_framesNum = m_framesAcc = m_fps = 0.0;
            m_timer.start();
        }

        void update()
        {
            m_didFpsChanged = false;

            m_prevTime += m_deltaTime;
            m_deltaTime = double(m_timer.getTicks()) - m_prevTime;

            m_accumulator = std::min<>(m_accumulator + m_deltaTime, 200.0);

            m_framesNum += 1.0;
            m_framesAcc += m_deltaTime;

            if(m_framesAcc >= 800.0)
            {
                m_fps = 1000.0 * m_framesNum / m_framesAcc;
                m_framesNum = 0.0;
                m_framesAcc = 0.0;

                m_didFpsChanged = true;
            }
        }

        inline double getDelta()
        {
            return m_deltaTime;
        }

        inline double getFps()
        {
            return m_fps;
        }

        inline bool didFpsChanged()
        {
            return m_didFpsChanged;
        }

        unsigned getFixedSteps(double fixedDelta)
        {
            unsigned fixedSteps = unsigned(m_accumulator / fixedDelta);
            m_accumulator -= float(fixedSteps) * fixedDelta;
            return fixedSteps;
        }

    protected:
        double m_prevTime;
        double m_deltaTime;
        double m_accumulator;

        double m_framesNum;
        double m_framesAcc;

        double m_fps;

        bool   m_didFpsChanged;

        Timer<> m_timer;
    };
}

#endif
