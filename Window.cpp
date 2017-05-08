#include "Window.h"

namespace MyWindow {
	
	Window::Window(){ 
		Setup("Window", Vector2u(640,480));
	}
	
	Window::Window(const string& title, const Vector2u& size) {
		Setup(title,size);
	}
	
	Window::~Window() {
		m_window.close();
		
		delete m_eventManager;
		m_eventManager = nullptr;
		
		delete m_realTimeInputManager;
		m_realTimeInputManager = nullptr;
	}
	
	void Window::Setup(const string& title, const Vector2u& size){
		
		m_eventManager = new EventManager();
		m_realTimeInputManager = new RealTimeInputManager();
		
		if (m_eventManager == nullptr ||
			m_realTimeInputManager == nullptr)
		{
			throw Exception(ExcType::badAlloc, "In Window Constructor");
		}
		
		m_windowTitle = title;
		m_windowSize = size;
		m_isFullscreen = false;
		m_isDone = false;
		m_isFocused = true;
	
		m_eventManager->AddCallback("Fullscreen_toggle", &Window::ToggleFullscreen,this);
		m_eventManager->AddCallback("Window_close", &Window::Close, this);	
	
		Create();
	}
	
	void Window::Create(){
		sf::Uint32 style = sf::Style::Default;
		if(m_isFullscreen){ style = sf::Style::Fullscreen; }
	
		m_window.create(sf::VideoMode(m_windowSize.x,m_windowSize.y,32),m_windowTitle,style);
	}
	
	void Window::BeginDraw(){ m_window.clear(BackgroundColor); }
	void Window::EndDraw(){ m_window.display(); }
	
	bool Window::IsDone(){ return m_isDone; }
	bool Window::IsFullscreen(){ return m_isFullscreen; }
	bool Window::IsFocused(){ return m_isFocused; }
	
	RenderWindow& Window::GetRenderWindow(){ return m_window; }
	EventManager* Window::GetEventManager(){ return m_eventManager; }
	RealTimeInputManager* Window::GetRealTimeInputManager() { return m_realTimeInputManager; }
	Vector2u Window::GetWindowSize(){ return m_windowSize; }
	
	void Window::ToggleFullscreen(EventDetails* l_details){
		m_isFullscreen = !m_isFullscreen;
		m_window.close();
		Create();
	}
	
	void Window::Close(EventDetails* l_details){ m_isDone = true; }
	
	void Window::Update(){
		sf::Event event;
	
		while(m_window.pollEvent(event)){
			if (event.type == Event::LostFocus){ m_isFocused = false; m_eventManager->SetFocus(false); }
			else if (event.type == Event::GainedFocus){ m_isFocused = true; m_eventManager->SetFocus(true); }
			m_eventManager->HandleEvent(event);
		}
		
		m_eventManager->Update();
		m_realTimeInputManager->HandleRealTimeInput();
		m_realTimeInputManager->Update();
	}

}
