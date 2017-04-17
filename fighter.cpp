#include "fighter.h"
#include <cmath>
void Fighter::setPosition(float x, float y) {
	m_position = Vector2f(x, y);
}

void Fighter::Set_Timer(Timer* l_Timer) {
	m_Timer = l_Timer;
}

void Fighter::SetDirection(Direction l_dir) {
	m_dir = l_dir;
}

void Fighter::MoveFighter() {
	switch (m_dir) {
		case Direction::Right:
				m_velocity = sf::Vector2f(m_increment.x, 0);
			break;
		case Direction::Left:
				m_velocity = sf::Vector2f(-m_increment.x, 0);
			break;
		case Direction::Up:
				m_velocity = sf::Vector2f(0, m_increment.y);
			break;
		case Direction::Down:
				m_velocity = sf::Vector2f(0, -m_increment.y);
			break;
		case Direction::Continue:
			break;
	}
	float fElapsed = m_Timer->GetElapsed().asSeconds();
	
	m_position.x += m_velocity.x * fElapsed;
	m_position.y += m_velocity.y * fElapsed;
}
void Fighter::Update() {
	MoveFighter();
}
void Fighter::Draw() {
	//В Engine нужно сналача m_window.clear(sf::Color::Black);
	m_body.setFillColor(sf::Color::Red);
	m_body.setSize(sf::Vector2f(100, 100));
	m_body.setPosition(m_position);
	m_window.draw(m_body);
}

Fighter::Fighter(sf::RenderWindow &l_window):
	m_window(l_window)
{	
	//TODO: вынести эти настройки в файл и загружать и оттуда
	m_position = sf::Vector2f(0, 0);
	m_increment = sf::Vector2f(50, 50);
	m_velocity = sf::Vector2f(0, 0);
}
