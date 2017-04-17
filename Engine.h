#ifndef ENGINE_H_
#define ENGINE_H_

#include <SFML/Graphics.hpp>
#include "fighter.h"
#include "Array.h"
#include "Timer.h"

enum class Direction;

class Engine {
public:
	Engine(Fighter* Fighter1, Fighter* Fighter2);
	Engine();
	~Engine();
	void Initilize(Fighter* Fighter1, Fighter* Fighter2);
	void HandleInput(); //Обработка всех нажатий и часть логики
	void Update(); //Часть логики здесь
	void Render(); //Отрисовка
	sf::RenderWindow& GetWindow();
	void CloseWindow();
	
	bool is_ok();
	void Set_Timer(Timer* l_Timer);
private:
	Array m_ar;
	//Таймер, Общий для всех(Так сделано для синхронизации времени между объектами)
	Timer* m_Timer = new Timer();
	
	void proceed_event(sf::Event l_event);
	
	sf::RenderWindow m_window;
	
	//Если окно не хотят закрыть, то все ok
	bool ok = true;
};
#endif
