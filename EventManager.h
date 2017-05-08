#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

#include "const.h"
#include "Exception.h"
using MyException::Exception;
using MyException::ExcType;

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using sf::RenderWindow;
using sf::Event;
using sf::Vector2i;
using sf::Uint32;
using sf::Mouse;

#include <vector>
using std::vector;

#include <unordered_map>
using std::unordered_map;

#include <functional>
using std::function;
using std::bind;

#include <fstream>
#include <sstream>
#include <iostream>
using std::ifstream;

using std::pair;
using std::string;

namespace MyEventManager {
	
	//TODO: придумать способ разделения eventManager на части
	//в зависимости от состояния игры(пауза, игра)
	//Обозначаем Event'ы, которые мы обрабатываем
	enum class EventType {
		KeyDown = Event::KeyPressed,
		KeyUp = Event::KeyReleased,
		MButtonDown = Event::MouseButtonPressed,
		MButtonUp = Event::MouseButtonReleased,
		MouseWheel = sf::Event::MouseWheelMoved,
		WindowResized = Event::Resized,
		GainedFocus = Event::GainedFocus,
		LostFocus = Event::LostFocus,
		MouseEntered = Event::MouseEntered,
		MouseLeft = Event::MouseLeft,
		Closed = Event::Closed,
		TextEntered = Event::TextEntered,
		Keyboard = Event::Count + 1, Mouse, Joystick,
		fff = 30	
	};
	
	//EventInfo хранит код кнопки, к которой мы привяжем 
	//функцию, обрабатывающую выбранное событие
	struct EventInfo{
		EventInfo(){ m_code = 0; }
		EventInfo(int l_event){ m_code = l_event; }
		
		int m_code;
	};
	
	//EventDetails хранит пользовательское название события
	//и информацию о вводе(код кнопки, коорд. курсора,
	//сдвиг колеса мышки, введеный текст)
	struct EventDetails{
		EventDetails(const string& l_bindName)
			: m_name(l_bindName){
			Clear();
		}
		
		string m_name;
	
		Vector2i m_size;
		Uint32 m_textEntered;
		Vector2i m_mouse;
		int m_mouseWheelDelta;
		int m_keyCode; // Single key code.
	
		void Clear() {
			m_size = Vector2i(0, 0);
			m_textEntered = 0;
			m_mouse = Vector2i(0, 0);
			m_mouseWheelDelta = 0;
			m_keyCode = -1;
		}
	};
	
	//Events = [ [Событие; Кнопка, его вызывающая] ] (кнопка может быть не одна)
	using Events = vector<pair<EventType, EventInfo> >;
	
	
	struct Binding{
		Binding(const string& l_name): 
			m_name(l_name), 
			m_details(l_name), 
			c(0)
		{}
		
		void BindEvent(EventType l_type, EventInfo l_info = EventInfo()){
			m_events.emplace_back(l_type, l_info);
		}
	
		Events m_events;
		
		//Binding и EventDetails должны иметь имя, потому что
		//один Event вообще говоря может вызываться несколькими кнопками
		string m_name;
	
		EventDetails m_details;
		unsigned int c; // Count of events that are "happening".
	};
	
	//Bindings = [ [Имя события; 
	//				Binding - структура, хранящая Input и коды кнопок] ]
	using Bindings = unordered_map<string, Binding*>;
	//Callbacks = [ [Имя события; 
	//				 Ссылка на функцию, которую нужно вызвать, 
	//				 при нажатии на нужные кнопки] ]
	using Callbacks = unordered_map<string, function<void(EventDetails*)> >;
	
	
	class EventManager{
	public:
		//TODO:реализовать конструктор с параметром std::string PathToSettings - путь до файла настроек
		EventManager();
		~EventManager();
	
		bool AddBinding(Binding *l_binding);
		bool RemoveBinding(string l_name);
	
		void SetFocus(const bool& l_focus);
	
		// Needs to be defined in the header!
		template<class T>
		bool AddCallback(const string& l_name, 
						 void(T::*l_func)(EventDetails*), 
						 T* l_instance)
		{
			function<void(EventDetails*)> temp = 
				bind(l_func,l_instance, std::placeholders::_1);
			return m_callbacks.emplace(l_name, temp).second;
		}
	
		void RemoveCallback(const string& l_name){
			m_callbacks.erase(l_name);
		}
	
		void HandleEvent(Event& l_event);
		void Update();
	
		Vector2i GetMousePos(RenderWindow* l_wind = nullptr){
			return (l_wind ? Mouse::getPosition(*l_wind) : Mouse::getPosition());
		}
	private:
		void LoadBindings();
	
		Bindings m_bindings;
		Callbacks m_callbacks;
		bool m_hasFocus;
	};

}

#endif
