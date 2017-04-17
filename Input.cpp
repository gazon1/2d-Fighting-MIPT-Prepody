#include "Input.h"

void Input::handle_event(sf::Window& m_window, Event m_event) {
	switch (m_event.type)
	{
		case Event::Closed:
			m_window.close();
			break;
		case Event::KeyPressed:
			switch (m_event.key.code) {
				//TODO: добавить проверку на бота
				//TODO: Как только будет move(), реализовать все, что ниже
				//---------First Fighter
				case sf::Keyboard::Right:
					//move Fighter1
					break;
				case sf::Keyboard::Left:
					//move Fighter1
					break;
				case sf::Keyboard::Up:
					//move Fighter1
					break;
				case sf::Keyboard::Down:
					//move Fighter1
					break;
				case sf::Keyboard::RShift:
					//Jump Fighter1
					break;
				case sf::Keyboard::RAlt:
					//Sneak Fighter1
					break;
				//---------Second Fighter
				case sf::Keyboard::D:
				
					break;
				case sf::Keyboard::A:
				
					break;
				case sf::Keyboard::W:
				
					break;
				case sf::Keyboard::S:
					
					break;
				case sf::Keyboard::Space:
					
					break;
				case sf::Keyboard::LAlt:
					
					break;
			}
	}
}

void Input::catch_events(sf::Window& m_window) {
	Event l_event;
	while (m_window.pollEvent(l_event)) {
		handle_event(m_window, l_event);
	}
}
