#include "EventManager.h"
#include <iostream>
#include <string>
int main() {
	try {
		MyEventManager::EventManager ev_man;
	} catch (MyException::Exception& e) {
		//~ std::string out(e.what());
		std::cout << e.user_what() << std::endl;		
	}
	
	std::cout << "Hello" << std::endl;
	return 0;
}

