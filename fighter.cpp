#include "fighter.h"
#include <cmath>
void Fighter::MoveFighter(Direction where, float fElapsed) {
	
	switch (where) {
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
	}
	m_position.x += m_velocity.x * fElapsed;
	m_position.y += m_velocity.y * fElapsed;
}

Fighter::Fighter() {
	m_position = sf::Vector2f(0, 0);
	
	m_velocity = sf::Vector2f(5, 5);
	
	m_increment = sf::Vector2f(5, 5);	
}

Fighter::Fighter(Vector2f l_position, Vector2f l_increment) {
	m_position = l_position;
	m_increment = sf::Vector2f(abs(l_increment.x), abs(l_increment.y));
}
