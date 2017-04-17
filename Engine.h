#ifndef ENGINE_H_
#define ENGINE_H_

#include <SFML/Graphics.hpp>
#include "fighter.h"
#include "Array.h"

enum class Direction;

//-----Сам Двигатель
class Engine {
public:	
	Engine(Fighter* Fighter1, Fighter* Fighter2);
	~Engine();
	
	void HandleInput(); //Обработка всех нажатий
	void Update();
	void Render(); //Отрисовка
	sf::RenderWindow* GetWindow();
	
	//Ф-ии для движения героев
	sf::Time GetElapsed();
	void RestartClock();  //TODO: Где-нибудь в game loop поставить вызова этой ф-ии
	
	
private:
	Array m_ar;
	
	sf::Clock m_clock;
	sf::Time m_elapsed;
	
	void proceed_event(sf::Event l_event);
	
	sf::RenderWindow m_window;
};
#endif
