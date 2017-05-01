#ifndef WINDOW_H_
#define WINDOW_H_

#include <string>
using std::string;

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
using sf::RenderWindow;
using sf::Vector2u;

#include "EventManager.h"
using MyEventManager::EventManager;
using MyEventManager::EventDetails;

//~ #include "RealTimeInputManager.h"

//~ #include "Exception.h"
//~ using MyException::Exception;
//~ using MyException::ExcType;

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
		Vector2u GetWindowSize();
		
		//для теста:
		void changeBackground(EventDetails* l_EventDetails);
				
	private:
		RenderWindow m_window;
		EventManager m_eventManager;
		//~ RealTimeInputManager m_realTimeInputManager;
		
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
