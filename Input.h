#include <SFML/Graphics.hpp>

class Input {
public:
	void catch_events(sf::Window& m_window); //В этой ф-ии находится цикл который вызывает handle_event
	void handle_event(sf::Window& m_window, Event m_event); //эта ф-ия обрабатывает события
};
