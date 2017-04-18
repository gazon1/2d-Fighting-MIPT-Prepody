#include "objects.h"

namespace MyObjects
{
	ArrayOfObjects::ArrayOfObjects()
		: 	m_objects(),
			m_count(0)
		{};

	ArrayOfObjects::~ArrayOfObjects()
	{
		auto iter = begin();

		while(!isEmpty())
		{
			deleteObject(iter.object());
			++iter;
		}
	};

	bool ArrayOfObjects::isFull() const
	{
		return m_count == capacity;
	};

	bool ArrayOfObjects::isEmpty() const
	{
		m_count == 0;
	};

	bool ArrayOfObjects::isOutOfRange(int index) const
	{
		return index < 0 || index >= m_count;
	};

	Object * ArrayOfObjects::operator[](int index)
	{
		if(isOutOfRange(index))
			throw indexOutOfRangeException;
		else
			return m_objects[index];
	};

	Object * ArrayOfObjects::first()
	{
		return this->operator[](0);
	};

	Object * ArrayOfObjects::last()
	{
		return this->operator[](m_count - 1);
	};

	int ArrayOfObjects::count() const
	{
		return m_count;
	};

	ArrayOfObjects::iterator ArrayOfObjects::begin()
	{
		return iterator(this, m_objects);
	};

	ArrayOfObjects::iterator ArrayOfObjects::end()
	{
		return iterator(this, m_objects + m_count - 1);
	};

	template <typename argType>
	void ArrayOfObjects::forEach(void (*action)(Object &, argType &), argType & argument)
	{
		for(auto iter = begin(); iter != end(); ++iter)
			action(*iter.object(), argument);
	};

	template <typename argType>
	void ArrayOfObjects::forEach(void (*action)(Object &, argType &), argType & argument, iterator start, iterator finish)
	{
		for(auto iter = start; iter != finish; ++iter)
			action(*iter.object(), argument);
	};

	void ArrayOfObjects::forEach(void (*action)(Object &))
	{
		for(auto iter = begin(); iter != end(); ++iter)
			action(*iter.object());
	};

	void ArrayOfObjects::forEach(void (*action)(Object &), iterator start, iterator finish)
	{
		for(auto iter = start; iter != finish; ++iter)
			action(*iter.object());
	};

	void ArrayOfObjects::addObject(Object * object)
	{
		if(isFull())
			throw overflowException;

		if(!object)
			throw nullPtrException;

		m_objects[m_count++] = object;
	};

	void ArrayOfObjects::deleteObject(Object * object)
	{
		Object * currentObject, * lastObject;

		for(auto iter = begin(); iter != end(); ++iter)
		{
			currentObject = iter.object();

			if(currentObject == object)
			{
				lastObject = last();
				swap(currentObject, lastObject);

				lastObject = last();
				delete lastObject;
				m_count--;

				return;
			}
		}

		throw notFoundException;
	};

	void ArrayOfObjects::clear()
	{
		for(auto iter = begin(); iter != end(); ++iter)
		{
			auto object = iter.object();

			if(!object->isActive())
				deleteObject(object);
		}
	};

	ArrayOfObjects::iterator::iterator(ArrayOfObjects * objects, Object ** current)
		: m_objects(objects),
		  m_current(current)
		{};

	bool ArrayOfObjects::iterator::isFirst()
	{
		return object() == m_objects->first();
	};

	bool ArrayOfObjects::iterator::isLast()
	{
		return object() == m_objects->last();
	};

	Object * ArrayOfObjects::iterator::object()
	{
		return *m_current;
	};

	const Object * ArrayOfObjects::iterator::object() const
	{
		return *m_current;
	};

	ArrayOfObjects & ArrayOfObjects::iterator::objects()
	{
		return *m_objects;
	};

	ArrayOfObjects ArrayOfObjects::iterator::objects() const
	{
		return *m_objects;
	};

	bool ArrayOfObjects::iterator::operator==(const iterator & iter)
	{
		return object() == iter.object();
	};

	bool ArrayOfObjects::iterator::operator!=(const iterator & iter)
	{
		return object() != iter.object();
	};

	void ArrayOfObjects::iterator::operator++()
	{
		if(isLast())
			throw iterOutOfRangeException;

		auto currentObject = object();
		if(!currentObject->isActive())
			this->operator++();

		m_current++;
	};

	void ArrayOfObjects::iterator::operator--()
	{
		if(isFirst())
			throw iterOutOfRangeException;

		auto currentObject = object();
		if(!currentObject->isActive())
			this->operator--();

		m_current--;
	};

	void ArrayOfObjects::iterator::operator+=(int offset)
	{
		for(int forward = 0; forward < offset; forward++)
			this->operator++();
	};

	void ArrayOfObjects::iterator::operator-=(int offset)
	{
		for(int back = 0; back < offset; back++)
			this->operator--();
	};
}
