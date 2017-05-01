#include "Engine.h"
#include "Exception.h"
using MyException::Exception;

int main(int argc, char** argv) {
	
	try {
		MyEngine::Engine eng;
		
		eng.AddPlayer(new Fighter(true, false));
		eng.AddPlayer(new Fighter(false, false));
		
		while (!eng.IsWindowToBeClosed()) {
			eng.Update();
			eng.logic();
			eng.draw();
		}
	} catch (Exception e) {
		std::cerr << e.user_what() << std::endl;
	} catch (std::exception e) {
		std::cerr << e.what() << std::endl;
	}
		
	return 0;
}
