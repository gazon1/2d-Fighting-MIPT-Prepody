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
						m_velocity.x = m_incrementFlight.x;
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
						m_velocity.x = -m_incrementFlight.x;
					} else {
						m_velocity = Vector2f(-m_increment.x, 0);
					}
				} else {
					m_velocity.x = 0;
				}	
			break;
		//~ case Direction::Up:
				//~ if (m_isInAir) {
					//~ m_velocity += Vector2f(0, m_incrementFlight.y);
				//~ }
			//~ break;
		case Direction::Down:
				if (m_isInAir) {
					m_velocity = Vector2f(0, -m_incrementFlight.y);
				} else {
					//Если мы на земле и нажимаем вниз, то мы ни опутимся ниже
					m_velocity.x = 0;
				}
			break;
		case Direction::DownLeft:
			//~ if (m_isInAir) {
				//~ m_velocity = Vector2f(-m_incrementFlight.x, -m_incrementFlight.y);
			//~ } else {
				//~ //Если мы на земле и нажимаем вниз, то мы ни опутимся ниже
				//~ m_velocity.x = 0;
			//~ }
			if (m_position.x >= 0) {
				m_velocity = Vector2f(-m_incrementFlight.x, -m_incrementFlight.y);
			} else {
				m_velocity = Vector2f(0, -m_incrementFlight.y);
			}
			break;
		case Direction::DownRight:
			if (m_position.x <= size.x - m_bodySize.x) {
				m_velocity = Vector2f(m_incrementFlight.x, -m_incrementFlight.y);
			} else {
				m_velocity = Vector2f(0, -m_incrementFlight.y);
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
	
	if (m_position.y < size.y - m_bodySize.y) {
		m_acceleration.y = MyConst::accelerationOfFreeFall;
		time_for_ac += fElapsed;
	} else {
		m_acceleration.y = 0;
		time_for_ac = 0;
		m_isInAir = false;
		m_position = Vector2f(m_position.x, size.y - m_bodySize.y);
	}
	
 	m_position.x += m_velocity.x * fElapsed + 0.5 * m_acceleration.x * pow(time_for_ac, 2);
	m_position.y += m_velocity.y * fElapsed + 0.5 * m_acceleration.y * pow(time_for_ac, 2);
	
	//~ std::cout << m_isInAir;
	
}

void Fighter::Jump() {
	
	if (!m_isInAir) {
		m_isInAir = true;
		this->SetDirection(Direction::Down);
		//(position.y - 5) - начальная координата
		//вычисляется таким образом, чтобы избежать проверки
		//условия на остановку в начале прыжка
		this->setPosition(m_position.x, m_position.y - 5);
	}
}

void Fighter::JumpLeft() {

	if (m_isInAir == false) {
		m_isInAir = true;
		this->SetDirection(Direction::DownLeft);
		this->setPosition(m_position.x, m_position.y - 5);
	}
	
	std::cout << "JumpLeft" << std::endl;
	//~ Jump();
}

void Fighter::JumpRight() {
	if (m_isInAir == false) {
		m_isInAir = true;
		this->SetDirection(Direction::DownRight);
		this->setPosition(m_position.x, m_position.y - 5);
	}
	
	std::cout << "JumpRight" << std::endl;
	//~ Jump();
}

void Fighter::moveLeft() {
	if (!m_isInAir) {
		this->SetDirection(Direction::Left);
	}
}

void Fighter::moveRight() {
	this->SetDirection(Direction::Right); 
}

//~ void Fighter::PunchByArm() {
	
//~ }

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
		
		m_window->GetRealTimeInputManager()->AddCallback("RightPlayer_moveLeft",
			&Fighter::moveLeft, this);
		m_window->GetRealTimeInputManager()->AddCallback("RightPlayer_moveRight",
			&Fighter::moveRight, this);
			
		//Настраиваем прыжки
		m_window->GetRealTimeInputManager()->AddCallback("RightPlayer_Jump",
			&Fighter::Jump, this);
		m_window->GetRealTimeInputManager()->AddCallback("RightPlayer_JumpRight",
			&Fighter::JumpRight, this);
			
		m_window->GetRealTimeInputManager()->AddCallback("RightPlayer_JumpLeft",
			&Fighter::JumpLeft, this);
			
	} else
	if (!IsBot && !m_isRightPlayer) {
		
		m_window->GetRealTimeInputManager()->AddCallback("LeftPlayer_moveLeft",
			&Fighter::moveLeft, this);
		m_window->GetRealTimeInputManager()->AddCallback("LeftPlayer_moveRight",
			&Fighter::moveRight, this);
			
		//Настраиваем прыжки
		m_window->GetRealTimeInputManager()->AddCallback("LeftPlayer_Jump",
			&Fighter::Jump, this);
			
		m_window->GetRealTimeInputManager()->AddCallback("LeftPlayer_JumpRight",
			&Fighter::JumpRight, this);
			
		m_window->GetRealTimeInputManager()->AddCallback("LeftPlayer_JumpLeft",
			&Fighter::JumpLeft, this);
			
		//Настраиваем удары
		//~ m_window->GetRealTimeInputManager()->AddCallback("LeftPlayer_PunchByArm",
			//~ &Fighter::PunchByArm, this);
	}
}


void Fighter::control() {}

void Fighter::moveBot() {
	//TODO: Реализовать логику бота
}
