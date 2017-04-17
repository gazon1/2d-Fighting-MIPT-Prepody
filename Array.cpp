#include "Array.h"

Array::Array() {
	m_length = 0;
}

int Array::length() {
	return m_length;
}
void Array::put(Fighter *obj) {
	if (m_length < _NUM_OF_HEROS) {
		m_ar[m_length] = obj;
		++m_length;
	} else {
		//TODO: дописать обработку ошибки
	}
	
}

Fighter* Array::operator[](int i) {
	if (i < _NUM_OF_HEROS && i >= 0) {
		return m_ar[i];
	} else {
		//TODO: дописать обработку ошибки
	}
}
