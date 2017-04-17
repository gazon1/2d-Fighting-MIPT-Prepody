#ifndef ARRAY_H_
#define ARRAY_H_

#include <SFML/Graphics.hpp>
#include "fighter.h"
#include "CONST.h"

//-------Массив для объектов
class Array {
public:
	Array();
	void put(Fighter *obj); //Setter
	Fighter* operator[](int i); //Getter
	int length(); //выдать кол-во объектов в m_ar
	
private:
	int 	 m_length;
	Fighter* m_ar[_NUM_OF_HEROS];
};

#endif
