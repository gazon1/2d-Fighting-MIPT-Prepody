#include "Engine.h"

int main(int argc, char** argv) {
	Engine eng;
	eng.Initilize(new Fighter(eng.GetWindow()), new Fighter(eng.GetWindow()));
	
	while (eng.is_ok()) {
		eng.HandleInput();
		eng.Update();
		eng.Render();
	}
	
	eng.CloseWindow();	
	
	return 0;
}
