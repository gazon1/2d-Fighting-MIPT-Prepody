#ifndef FIGHTER_H_
#define FIGHTER_H_

//~ #include "Animation.h"

#include <SFML/Graphics.hpp>
#include "Timer.h"
using sf::Vector2f;
//~ class Face;
//~ class Body;

enum class Direction {
	//TODO: добавить UP-RIGHT, UP-LEFT и т.д.
	Continue, //двигаться по инерции
	Right,
	Left,
	Up,
	Down
};


class Fighter
{
	public:

	struct FightChars
	{
		int health;
		int force;
		float speed;
	};
	
	Fighter(sf::RenderWindow& l_window);
	
	void MoveFighter();
	void SetDirection(Direction l_dir);
	void JumpFighter(float l_fElapsed); //TODO: реализовать

	void Update();
	void setPosition(float x, float y);
	
	void Draw();
	
	//Для теста
	sf::RectangleShape m_body;
	
	//Таймер устанавливается из Engine'a
	void Set_Timer(Timer* l_Timer);
	private:
		Direction m_dir;
		Timer* m_Timer;
		
		//~ Face * m_face;
		//~ Body * m_body;

		FightChars m_chars;
		
		//m_increment - "константа скорости", а m_velocity уже меняется в зависимости от направления
		Vector2f m_position;
		Vector2f m_velocity;
		Vector2f m_accelaration;
		Vector2f m_increment;
		
		//Созданием окна занимается Engine, Fighter может только принимать Window как параметр конструктора
		sf::RenderWindow& m_window;
};
#endif
