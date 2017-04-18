#include "object.h"

namespace MyObject
{
		Object::Object(const Vector & position, const Vector & velocity, const Vector & acceleration)
			: m_position(position),
			  m_velocity(velocity),
			  m_acceleration(acceleration),
			  m_isActive(true)
			{};

		Object::~Object()
			{};

		bool Object::isActive()
		{
			return m_isActive;
		}

		void Object::move()
		{

		};

		void Object::draw()
		{

		};

		void Object::control()
		{

		};

		void Object::logic()
		{

		};
}