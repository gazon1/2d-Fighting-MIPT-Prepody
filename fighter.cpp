#include "fighter.h"

void Fighter::setPosition(float x, float y) { m_position = Vector2f(x, y); }
void Fighter::Set_Window(Window* l_Window) { m_window = l_Window; }
void Fighter::Set_Timer(Timer* l_Timer) { m_Timer = l_Timer; }
void Fighter::SetDirection(Direction l_dir) { m_dir = l_dir; }
Vector2f Fighter::getPosition() { return m_position; }

bool Fighter::isRightPlayer() {
	return m_isRightPlayer;
}


void Fighter::move() {
	if (IsBot) { 
		moveBot();
	}
	
	sf::Vector2u size = m_window->GetRenderWindow().getSize();
	
	switch (m_dir) {
		case Direction::Right:
				if (this->getPosition().x != size.x)
				{
					if (m_isInAir) {
						m_velocity = Vector2f(m_incrementFlight.x, 0);
					} else {
						m_velocity = Vector2f(m_increment.x, 0);
					}
				} else {
					m_velocity.x = 0;
				}		
			break;
		case Direction::Left:
				if (this->getPosition().x != 0)
				{
					if (m_isInAir) {
						m_velocity = Vector2f(-m_incrementFlight.x, 0);
					} else {
						m_velocity = Vector2f(-m_increment.x, 0);
					}
				} else {
					m_velocity.x = 0;
				}	
			break;
		case Direction::Up:
				if (m_isInAir) {
					m_velocity += Vector2f(0, m_incrementFlight.y);
				}
			break;
		case Direction::Down:
				if (m_isInAir) {
					m_velocity += Vector2f(0, -m_incrementFlight.y);
				} else {
					//Если мы на земле и нажимаем вниз, то мы ни опутимся ниже
					m_velocity.x = 0;
				}
			break;
		case Direction::DownLeft:
			if (m_position.x == 0) {
				m_velocity = Vector2f(0, -m_incrementFlight.y);
			} else {
				m_velocity = Vector2f(-m_incrementFlight.x, -m_incrementFlight.y);
			}
			break;
		case Direction::DownRight:
			if (m_position.x == size.x - m_bodySize.x) {
				m_velocity = Vector2f(0, -m_incrementFlight.y);
			} else {
				m_velocity = Vector2f(m_incrementFlight.x, -m_incrementFlight.y);
			}
			break;
		case Direction::Continue:
				
			break;
		case Direction::None:
				m_velocity = Vector2f(0, 0);
			return;
	}
	
	if ((m_position.x + m_bodySize.x >= size.x && m_velocity.x > 0) ||
		(m_position.x <= 0 && m_velocity.x < 0))
	{
		m_velocity.x = 0;
		
		if (m_position.x + m_bodySize.x >= size.x) {
			m_position.x = size.x - m_bodySize.x;
		} else if (m_position.x  <= 0) {
			m_position.x  = 0;
		}
	}
	
	if (m_isInAir) {
		this->SetDirection(Direction::Continue);
	} else {
		this->SetDirection(Direction::None);
	}
	
	float fElapsed = m_Timer->GetElapsed().asSeconds();
	
	if (size.y - m_position.y > m_bodySize.y + 0.1) {
		m_acceleration.y = 5;
		time_for_ac += fElapsed;
		std::cout << "ac:: x:" << m_acceleration.x << "; y: " << m_acceleration.y << std::endl;
	} else {
		m_acceleration.y = 0;
		time_for_ac = 0;
		m_isInAir = false;
		m_position = Vector2f(m_position.x, size.y - m_bodySize.y);
	}
	
 	m_position.x += m_velocity.x * fElapsed + 0.5 * m_acceleration.x * pow(time_for_ac, 2);
	m_position.y += m_velocity.y * fElapsed + 0.5 * m_acceleration.y * pow(time_for_ac, 2);
	
}


void Fighter::moveLeftPlayer(EventDetails* l_details) {
	//для теста:
	string temp;
	
	switch (l_details->m_keyCode) {
		case sf::Keyboard::D:
			this->SetDirection(Direction::Right);
			temp = "right";
			break;
		case sf::Keyboard::A:
			this->SetDirection(Direction::Left);
			temp = "left";
			break;
		case sf::Keyboard::W:
			this->SetDirection(Direction::Down);
			temp = "down";
			break;
		case sf::Keyboard::S:
			this->SetDirection(Direction::Up);
			temp = "up";
			break;
		case sf::Keyboard::Space:
			m_isInAir = true;
			this->SetDirection(Direction::Down);
			
			//(position.y - 5) - начальная координата
			//вычисляется таким образом, чтобы избежать проверки
			//условия на остановку в начале прыжка
			this->setPosition(m_position.x, m_position.y - 5);
			temp = "Space";
			break;
	}
	
	std::cout << "moving left player:_" << temp << "_;" << l_details->m_keyCode << std::endl;	
}

void Fighter::JumpLeft(EventDetails* l_details) {
	m_isInAir = true;
	this->SetDirection(Direction::DownLeft);
	this->setPosition(m_position.x, m_position.y - 5);
	
	std::cout << "Jumpring Left" << std::endl;
}

void Fighter::JumpRight(EventDetails* l_details) {
	m_isInAir = true;
	this->SetDirection(Direction::DownRight);
	this->setPosition(m_position.x, m_position.y - 5);
	
	std::cout << "Jumpring Right" << std::endl;
}

void Fighter::Move(EventDetails* l_details) {
	std::cout << "Move!" << std::endl;
}

void Fighter::moveRightPlayer(EventDetails* l_details)  {
	switch (l_details->m_keyCode) {
		case sf::Keyboard::Right:
			this->SetDirection(Direction::Right); 
			break;
		case sf::Keyboard::Left:
			this->SetDirection(Direction::Left); 
			break;
		case sf::Keyboard::Up:
			this->SetDirection(Direction::Up); 
			break;
		case sf::Keyboard::Down:
			this->SetDirection(Direction::Down); 
			break;
		case sf::Keyboard::RControl:
			m_isInAir = true;
			this->SetDirection(Direction::Down);
			
			//(position.y - 5) - начальная координата
			//вычисляется таким образом, чтобы избежать проверки
			//условия на остановку в начале прыжка
			this->setPosition(m_position.x, m_position.y - 5);
			break;
	}
	
	std::cout << "moving right player" << std::endl;
}

void Fighter::moveLeft(EventDetails* l_details) {
	this->SetDirection(Direction::Left); 
}

void Fighter::moveRight(EventDetails* l_details) {
	this->SetDirection(Direction::Right); 
}

void Fighter::logic() {
	move();
}

void Fighter::draw() {
	//В Engine нужно сналача m_window.clear(sf::Color::Black);
	m_body.setFillColor(m_bodyColor);
	m_body.setSize(m_bodySize);
	m_body.setPosition(m_position);
	m_window->GetRenderWindow().draw(m_body);
}

Fighter::Fighter(bool l_isRightPlayer, bool l_IsBot):
	Object(), m_isRightPlayer(l_isRightPlayer), IsBot(l_IsBot)
{	
		m_velocity = Vector2f(0, 0);
}

void Fighter::Setup() {
	if (!IsBot && m_isRightPlayer) {
		
		//Настраиваем движение по верт. и гор. осям
		m_window->GetEventManager()->AddCallback("RightPlayer_moveLeft_1",
			&Fighter::moveLeft, this);
		m_window->GetEventManager()->AddCallback("RightPlayer_moveLeft_2",
			&Fighter::moveLeft, this);
		m_window->GetEventManager()->AddCallback("RightPlayer_moveLeft_3",
			&Fighter::moveLeft, this);
		m_window->GetEventManager()->AddCallback("RightPlayer_moveLeft_4",
			&Fighter::moveLeft, this);
		m_window->GetEventManager()->AddCallback("RightPlayer_moveLeft_5",
			&Fighter::moveLeft, this);
			
		m_window->GetEventManager()->AddCallback("RightPlayer_moveRight_1",
			&Fighter::moveRight, this);
		m_window->GetEventManager()->AddCallback("RightPlayer_moveRight_2",
			&Fighter::moveRight, this);
		m_window->GetEventManager()->AddCallback("RightPlayer_moveRight_3",
			&Fighter::moveRight, this);
		m_window->GetEventManager()->AddCallback("RightPlayer_moveRight_4",
			&Fighter::moveRight, this);
		m_window->GetEventManager()->AddCallback("RightPlayer_moveRight_5",
			&Fighter::moveRight, this);
			
		//Настраиваем прыжки
		m_window->GetEventManager()->AddCallback("RightPlayer_Jump",
			&Fighter::moveRightPlayer, this);
			
		m_window->GetEventManager()->AddCallback("RightPlayer_JumpRight_1",
			&Fighter::JumpRight, this);
		m_window->GetEventManager()->AddCallback("RightPlayer_JumpRight_2",
			&Fighter::JumpRight, this);
		
		m_window->GetEventManager()->AddCallback("RightPlayer_JumpLeft_1",
			&Fighter::JumpLeft, this);
		m_window->GetEventManager()->AddCallback("RightPlayer_JumpLeft_1",
			&Fighter::JumpLeft, this);
			
	} else
	if (!IsBot && !m_isRightPlayer) {
		
		//Настраиваем движение по верт. и гор. осям
		m_window->GetEventManager()->AddCallback("LeftPlayer_moveRight_1",
			&Fighter::moveLeft, this);
		m_window->GetEventManager()->AddCallback("LeftPlayer_moveRight_2",
			&Fighter::moveLeft, this);
		m_window->GetEventManager()->AddCallback("LeftPlayer_moveRight_3",
			&Fighter::moveLeft, this);
		m_window->GetEventManager()->AddCallback("LeftPlayer_moveRight_4",
			&Fighter::moveLeft, this);
		m_window->GetEventManager()->AddCallback("LeftPlayer_moveRight_5",
			&Fighter::moveLeft, this);
			
		m_window->GetEventManager()->AddCallback("LeftPlayer_moveRight_1",
			&Fighter::moveRight, this);
		m_window->GetEventManager()->AddCallback("LeftPlayer_moveRight_2",
			&Fighter::moveRight, this);
		m_window->GetEventManager()->AddCallback("LeftPlayer_moveRight_3",
			&Fighter::moveRight, this);
		m_window->GetEventManager()->AddCallback("LeftPlayer_moveRight_4",
			&Fighter::moveRight, this);
		m_window->GetEventManager()->AddCallback("LeftPlayer_moveRight_5",
			&Fighter::moveRight, this);
			
		//~ m_window->GetEventManager()->AddCallback("LeftPlayer_moveUp",
			//~ &Fighter::moveLeftPlayer, this);
		//~ m_window->GetEventManager()->AddCallback("LeftPlayer_moveDown",
			//~ &Fighter::moveLeftPlayer, this);
			
		//Настраиваем прыжки
		m_window->GetEventManager()->AddCallback("LeftPlayer_Jump",
			&Fighter::moveLeftPlayer, this);
			
		m_window->GetEventManager()->AddCallback("LeftPlayer_JumpRight_1",
			&Fighter::JumpRight, this);
		m_window->GetEventManager()->AddCallback("LeftPlayer_JumpRight_2",
			&Fighter::JumpRight, this);
			
		m_window->GetEventManager()->AddCallback("LeftPlayer_JumpLeft_1",
			&Fighter::JumpLeft, this);
		m_window->GetEventManager()->AddCallback("LeftPlayer_JumpLeft_2",
			&Fighter::JumpLeft, this);
			
		m_window->GetEventManager()->AddCallback("Move",
			&Fighter::Move, this);
	}
}


void Fighter::control() {}

void Fighter::moveBot() {
	//TODO: Реализовать логику бота
}
