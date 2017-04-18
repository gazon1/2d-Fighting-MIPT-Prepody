#ifndef OBJECT_H_
#define OBJECT_H_

#include <SFML/Graphics.hpp>
using sf::Vector2f;

namespace MyObject
{
	typedef Vector2f Vector;

	const Vector zeroVector(0, 0);

	class Object
	{
		public:
			
			explicit Object(const Vector & position = zeroVector, const Vector & velocity = zeroVector, const Vector & acceleration = zeroVector);
			virtual ~Object();

			bool isActive();

			virtual void move();
			virtual void draw();
			virtual void control();
			virtual void logic();

		protected:

			Vector m_position, m_velocity, m_acceleration;
			bool m_isActive;
	};
}

#endif
