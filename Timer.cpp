#include "Timer.h"

sf::Time Timer::GetElapsed() { return m_elapsed; }
void Timer::RestartClock() { m_elapsed = m_clock.restart(); }

Timer::Timer() {
	RestartClock();
}
