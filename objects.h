#ifndef OBJECTS_H_
#define OBJECTS_H_

#include "Exception.h"
using MyException::Exception;
using MyException::ExcType;

#include "object.h"
using MyObject::Object;

#include "const.h"
using MyConst::arrayOfObjectsCapacity;

//-------Массив для объектов

//TODO: неплохо бы добавить void forEach(ObjectIter), либо ещё лучше отнаследоваться от std::array
//		можно перегрузить operator* вместо object
//		есть вариант сделать ArrayOfObjects умнее, добавив метод deletePassiveObjects() (вообще говоря update(), но звучит уж больно безлико), добавить проверку на то, что один объект не добавлен дважды

namespace MyObjects
{
	using std::swap;

	const int capacity = arrayOfObjectsCapacity;

	class ArrayOfObjects
	{
		public:

			enum exceptions
			{
				notFoundException,
				indexOutOfRangeException,
				iterOutOfRangeException,
				nullPtrException,
				overflowException
			};

			class iterator
			{
				public:

					bool isFirst();
					bool isLast();

					Object * object();
					const Object * object() const;

					ArrayOfObjects & objects();
					ArrayOfObjects objects() const;

					bool operator==(const iterator & iter);
					bool operator!=(const iterator & iter);

					void operator++();
					void operator--();
					void operator+=(int offset);
					void operator-=(int offset);

					friend class ArrayOfObjects;

				protected:

					iterator(ArrayOfObjects * objects, Object ** current);

				private:

					ArrayOfObjects * m_objects;
					Object ** m_current;
			};

			ArrayOfObjects();
			~ArrayOfObjects();

			bool isFull() const;
			bool isEmpty() const;
			bool isOutOfRange(int index) const;

			Object * operator[](int index);
			Object * first();
			Object * last();
			int count() const; //вывести m_count

			iterator begin();
			iterator end();
			iterator setOn();

			void forEach(void (*action)(Object &));
			void forEach(void (*action)(Object &), iterator start, iterator finish);
			
			template <typename argType>
			void forEach(void (*action)(Object &, argType &), argType & argument);
			template <typename argType>
			void forEach(void (*action)(Object &, argType &), argType & argument, iterator start, iterator finish);

			void addObject(Object * object);
			void deleteObject(Object * object);

			void clear();
			
		private:

			Object * m_objects[capacity];
			int m_count;
	};
}

#endif
