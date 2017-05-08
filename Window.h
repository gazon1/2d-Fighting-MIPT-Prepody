#ifndef WINDOW_H_
#define WINDOW_H_

#include "RealTimeInputManager.h"
using MyRealTimeInputManager::RealTimeInputManager;

#include <string>
using std::string;

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
using sf::RenderWindow;
using sf::Vector2u;
using sf::Event;

#include "EventManager.h"
using MyEventManager::EventManager;
using MyEventManager::EventDetails;

namespace MyWindow {
	
	class Window{
	public:
		Window();
		Window(const string& title, const Vector2u& size);
		~Window();
	
		void BeginDraw();
		//void Draw();
		void EndDraw();
	
		void Update();
	
		bool IsDone(); //Если isDone == false, то продолжаем игру. Иначе - закрываем окно
		bool IsFullscreen();
		bool IsFocused();
	
		void ToggleFullscreen(EventDetails* l_details);
		void Close(EventDetails* l_details = nullptr);
	
		RenderWindow& GetRenderWindow();
		
		EventManager* GetEventManager();
		RealTimeInputManager* GetRealTimeInputManager();
		
		Vector2u GetWindowSize();
				
	private:
		RenderWindow m_window;
		EventManager* m_eventManager = nullptr;
		RealTimeInputManager* m_realTimeInputManager = nullptr;
		
		Vector2u m_windowSize;
		string m_windowTitle;
		bool m_isDone;
		bool m_isFullscreen;
		bool m_isFocused;
		
		void Create();
		void Setup(const string& title, const Vector2u& size);
		
		sf::Color BackgroundColor = sf::Color::Black;
	};
	
}

#endif
