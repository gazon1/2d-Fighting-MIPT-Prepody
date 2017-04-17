#include "Engine.h"


void Engine::Set_Timer(Timer* l_Timer) {
	m_Timer = l_Timer;
}
bool Engine::is_ok() {
	return ok;
}

void Engine::CloseWindow() {
	m_window.close();
}
Engine::Engine() {
	m_window.create(sf::VideoMode(800, 600), "Title");
	m_Timer->RestartClock();
}
sf::RenderWindow& Engine::GetWindow() {
	return m_window;
}

void Engine::Initilize(Fighter* Fighter1, Fighter* Fighter2) {
	Fighter1->Set_Timer(m_Timer);
	Fighter2->Set_Timer(m_Timer);
	sf::Vector2u size = m_window.getSize();
	Fighter1->setPosition(0, (float)size.y - 100);
	Fighter2->setPosition((float)size.x -100, (float)size.y -100);
	m_ar.put(Fighter1);
	m_ar.put(Fighter2);
}

Engine::Engine(Fighter* Fighter1, Fighter* Fighter2) {
	m_window.create(sf::VideoMode(800, 600), "Title");	
	
	m_ar.put(Fighter1);
	m_ar.put(Fighter2);
	
	m_Timer->RestartClock();
}

void Engine::Render() {
	m_window.clear(sf::Color::Black);
	for (int i = 0; i < 2; ++i) { //2 - потому что у нас всего 2 героя(и только их мы и отрисовываем)
		m_ar[i]->Draw();		
	}
	m_window.display();
}

Engine::~Engine() {
	delete m_ar[0];
	delete m_ar[1];
	delete m_Timer;
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
	
	switch (l_event.type)
	{
		case sf::Event::Closed:
			ok = false;
			break;
		case sf::Event::KeyPressed:
			switch (l_event.key.code) {
				//TODO: добавить проверку на бота
				//---------First Fighter
				case sf::Keyboard::Right:
					Fighter1->SetDirection(Direction::Right); 
					break;
				case sf::Keyboard::Left:
					Fighter1->SetDirection(Direction::Left); 
					break;
				case sf::Keyboard::Up:
					Fighter1->SetDirection(Direction::Up); 
					break;
				case sf::Keyboard::Down:
					Fighter1->SetDirection(Direction::Down); 
					break;
				case sf::Keyboard::RShift:
					//Jump Fighter1
					break;
				case sf::Keyboard::RAlt:
					//Sneak Fighter1
					break;
				//---------Second Fighter
				case sf::Keyboard::D:
					Fighter2->SetDirection(Direction::Right);
					break;
				case sf::Keyboard::A:
					Fighter2->SetDirection(Direction::Left); 
					break;
				case sf::Keyboard::W:
					Fighter2->SetDirection(Direction::Down);
					break;
				case sf::Keyboard::S:
					Fighter2->SetDirection(Direction::Up); 
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

void Engine::Update() {
	for (int i = 0; i < 2; ++i) {
		m_ar[i]->Update();
	}
	m_Timer->RestartClock();
}

