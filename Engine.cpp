#include "Engine.h"


sf::Time Engine::GetElapsed() { return m_elapsed; }
void Engine::RestartClock() { m_elapsed = m_clock.restart(); }

Engine::Engine(Fighter* Fighter1, Fighter* Fighter2) {
	m_ar.put(Fighter1);
	m_ar.put(Fighter2);
	
	RestartClock();
}

Engine::~Engine() {
	delete m_ar[0];
	delete m_ar[1];
}


void Engine::HandleInput() {
	sf::Event l_event;
	while (m_window.pollEvent(l_event)) {
		proceed_event(l_event);
	}
}

void Engine::proceed_event(sf::Event l_event) {
	
	Fighter* Fighter1 = m_ar[0];
	Fighter* Fighter2 = m_ar[1];
	
	float fElapsed = m_elapsed.asSeconds();
	
	switch (l_event.type)
	{
		case sf::Event::Closed:
			m_window.close();
			break;
		case sf::Event::KeyPressed:
			switch (l_event.key.code) {
				//TODO: добавить проверку на бота
				//TODO: Как только будет move(), реализовать все, что ниже
				//---------First Fighter
				case sf::Keyboard::Right:
					Fighter1->MoveFighter(Direction::Right, fElapsed); 
					break;
				case sf::Keyboard::Left:
					Fighter1->MoveFighter(Direction::Left, fElapsed); 
					break;
				case sf::Keyboard::Up:
					Fighter1->MoveFighter(Direction::Up, fElapsed); 
					break;
				case sf::Keyboard::Down:
					Fighter1->MoveFighter(Direction::Down, fElapsed); 
					break;
				case sf::Keyboard::RShift:
					//Jump Fighter1
					break;
				case sf::Keyboard::RAlt:
					//Sneak Fighter1
					break;
				//---------Second Fighter
				case sf::Keyboard::D:
					Fighter2->MoveFighter(Direction::Right, fElapsed);
					break;
				case sf::Keyboard::A:
					Fighter2->MoveFighter(Direction::Left, fElapsed); 
					break;
				case sf::Keyboard::W:
					Fighter2->MoveFighter(Direction::Up, fElapsed); 
					break;
				case sf::Keyboard::S:
					Fighter2->MoveFighter(Direction::Down, fElapsed);
					break;
				case sf::Keyboard::Space:
					//Jump Fighter2
					break;
				case sf::Keyboard::LAlt:
					//Sneak Fighter2
					break;
			}
	}
}

