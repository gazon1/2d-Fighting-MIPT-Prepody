#ifndef FIGHTER_H_
#define FIGHTER_H_

//~ #include "Animation.h"

#include <SFML/Graphics.hpp>
using sf::Vector2f;
//~ class Face;
//~ class Body;

enum class Direction {
	//TODO: добавить UP-RIGHT, UP-LEFT и т.д.
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
	
	Fighter();
	Fighter(Vector2f l_position, Vector2f l_increment);
	
	void MoveFighter(Direction where, float l_fElapsed);
	void JumpFighter(float l_fElapsed); //TODO: реализовать
	
	void Draw();
	private:

		//~ Face * m_face;
		//~ Body * m_body;

		FightChars m_chars;
		
		//m_increment - "константа скорости", а m_velocity уже меняется в зависимости от направления
		Vector2f m_position;
		Vector2f m_velocity;
		Vector2f m_increment;
};

	



#endif
