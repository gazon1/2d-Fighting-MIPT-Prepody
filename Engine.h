#ifndef ENGINE_H_
#define ENGINE_H_

#include "Exception.h"
using MyException::Exception;
using MyException::ExcType;

#include <iostream>
#include "const.h"

#include "Window.h"
using MyWindow::Window;

#include <SFML/Graphics.hpp>
using sf::RenderWindow;
using sf::VideoMode;
using sf::Color;
using sf::Keyboard;
using sf::Event;

#include "fighter.h"

#include "objects.h" //замена для Array.h
using MyObjects::ArrayOfObjects;

#include "Timer.h"

enum class Direction;

namespace MyEngine {
	
	
	class Engine {
	public:
		void AddPlayer(Fighter* l_Fighter);
		void AddObject(Object* l_Object); 
		Engine();
		~Engine();
		
		void Update();
		void logic();
		void draw();
		
		Window* GetWindow();
		bool IsWindowToBeClosed();
		
		EventManager* GetEventManager();
		void Set_Timer(Timer* l_Timer);
		
		//Подсчитать результат удара
		//~ void CalcPanch();
		
		//для теста:
		void changeColor(EventDetails* e);
		
	private:
		void Setup();
	
		ArrayOfObjects* m_ar = nullptr;
		Fighter* m_LeftPlayer = nullptr;
		Fighter* m_RightPlayer = nullptr;
		Timer* m_Timer = nullptr;// = new Timer(); //Таймер, Общий для всех(Так сделано для синхронизации времени между объектами)
		Window* m_window = nullptr;// = new Window(MyConst::TitleOfMainWindow, MyConst::DefaultSizeOfMainWindow);
		Window pm_window;
	};
}
#endif
