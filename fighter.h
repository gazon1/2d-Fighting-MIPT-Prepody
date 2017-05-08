#ifndef FIGHTER_H_
#define FIGHTER_H_

#include "const.h"

#include "RealTimeInputManager.h"
using MyRealTimeInputManager::RealTimeInputManager;

#include <cmath>
#include "Window.h"
using MyWindow::Window;

#include <SFML/Graphics.hpp>
using sf::RectangleShape;
using sf::Vector2f;
using sf::RenderWindow;

#include "Timer.h"
#include "object.h" //здесь базовый класс для Fighter'a
using MyObject::Object;

enum class Direction {
	None,
	Continue, //двигаться по инерции
	Right,
	Left,
	Up,
	Down,
	DownRight,
	DownLeft
};

using std::string;

class Fighter: public Object
{
	public:

	struct FightChars
	{
		int health;
		int force;
		int speed;//процентное соотношение от maxSpeedOfEveryFighter, на которое увеличивается m_velocity
	};
	
	Fighter(bool l_isRightPlayer, bool l_IsBot = false);
	
	void SetDirection(Direction l_dir);

	void setPosition(float x, float y);
	Vector2f getPosition();
	
	void move();
	void draw();
	void control();
	void logic();	
	
	//Для теста
	RectangleShape m_body;
	sf::Color m_bodyColor = sf::Color::Red;
	
	//Таймер устанавливается из Engine'a
	void Set_Timer(Timer* l_Timer);
	void Set_Window(Window* l_Window);
	void Setup(); //вызвать эту функцию, после того, как Fighter получил окно
	bool isRightPlayer();
	
	private:	
		Direction m_dir;
		Timer* m_Timer;
		
		const Vector2f m_bodySize = Vector2f(100, 100);		
		
		bool m_isRightPlayer = false;
		bool IsBot = false;
		bool m_isInAir = false;
		
		void Jump();
		void JumpRight();
		void JumpLeft();
		
		void moveLeft();
		void moveRight();
		
		void moveBot(); //TODO: реализовать логику поведения бота

		FightChars m_chars;
		
		//m_increment - "константа скорости", а m_velocity уже меняется в зависимости от направления
		const Vector2f m_increment = Vector2f(100, 100);
		const Vector2f m_incrementFlight = Vector2f(100, 1000);
		float time_for_ac = 0;
		
		//Созданием окна занимается Engine, Fighter может только принимать Window как параметр конструктора
		Window* m_window;
};
#endif
