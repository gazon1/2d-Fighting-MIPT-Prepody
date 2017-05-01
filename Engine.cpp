#include "Engine.h"
namespace MyEngine {
	
	void Engine::Set_Timer(Timer* l_Timer) {
		m_Timer = l_Timer;
	}
	bool Engine::IsWindowToBeClosed() {
		return m_window->IsDone();
	}
	
	Engine::Engine() {
		m_window = new Window(MyConst::TitleOfMainWindow, 
							  MyConst::DefaultSizeOfMainWindow);
		m_Timer = new Timer();
		m_ar = new ArrayOfObjects();
		
		//TODO: поймать где-нибудь exc.
		if (m_window == nullptr ||
			m_Timer == nullptr || 
			m_ar == nullptr) 
		{
			throw Exception(ExcType::badAlloc, "In Engine Constructor");
		}
		
		//Устанавливаем свзяку событие - функция changeColor():
		m_window->GetEventManager()->AddCallback("change_LeftPlayerColor", &Engine::changeColor, this);
		
		m_Timer->RestartClock();
	}
	
	Window* Engine::GetWindow() {
		return m_window;
	}
	
	void Engine::AddPlayer(Fighter* l_Fighter) {
		l_Fighter->Set_Timer(m_Timer);
		l_Fighter->Set_Window(m_window);
		l_Fighter->Setup();
		//Расставляем игроков на экране
		sf::Vector2u size = m_window->GetRenderWindow().getSize();
		if (l_Fighter->isRightPlayer()) {
			m_RightPlayer = l_Fighter;
			l_Fighter->setPosition((float)size.x -100, (float)size.y -100);
		} else {
			m_LeftPlayer = l_Fighter;
			l_Fighter->setPosition(0, (float)size.y - 100);
		}
		
		//TODO: учесть где-то, что здесь может вылететь exc.
		//если переполнение или nullptr
		m_ar->addObject(l_Fighter);
	}
	
	void Engine::AddObject(Object* l_Object) {
		//TODO: реализовать
	}
	
	void Engine::draw() {
		m_window->BeginDraw();
		
		for (int i = 0; i < m_ar->count(); ++i) {
			(*m_ar)[i]->draw();		
		}
		
		m_window->EndDraw();
	}
	
	Engine::~Engine() {
		delete m_window;
		m_window = nullptr;
		
		m_ar->clear();
		m_ar = nullptr;
		
		delete m_Timer;
		m_Timer = nullptr;
		
		m_RightPlayer = nullptr;
		m_LeftPlayer = nullptr;		
	}
	
	
	void Engine::Update() {
		//здесь мы вызывает eventpoll
		m_window->Update();
	}
	
	void Engine::logic() {
		for (int i = 0; i < m_ar->count(); ++i) {
			(*m_ar)[i]->logic();
		}
		m_Timer->RestartClock();
	}
	
	//Для теста EventManager'a
	//Изменить цвет левого игрока
	void Engine::changeColor(EventDetails* l_details) {
		if (m_LeftPlayer != nullptr) {
			m_LeftPlayer->m_bodyColor = sf::Color::Blue;
			
			std::cout << "Changing Color of body" << l_details->m_keyCode << std::endl;
		} else {
			throw Exception(ExcType::nullPtr, "In change Color");
		}
	}	
}

