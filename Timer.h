#ifndef TIMER_H_
#define TIMER_H_
#include <SFML/Graphics.hpp>
class Timer {
public:
	Timer();
	sf::Time GetElapsed();//Получить время с последнего сброса таймера
	void RestartClock();//Сбосить таймер
	
private:
	sf::Clock m_clock;
	sf::Time m_elapsed;
};

#endif
