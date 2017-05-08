#ifndef REAL_TIME_INPUT_MANAGER_H_
#define REAL_TIME_INPUT_MANAGER_H_

#include "const.h"

#include <iostream>

#include "Exception.h"
using MyException::Exception;
using MyException::ExcType;

#include <set>
using std::set;

#include <map>
using std::map;
using std::multimap;

#include <utility>
using std::pair;
using std::make_pair;

#include <sstream>
using std::stringstream;

#include <fstream>
using std::ifstream;

#include <string>
using std::string;
using std::endl;
using std::getline;

#include <SFML/Graphics.hpp>
using sf::Keyboard;

#include <unordered_map>
using std::unordered_map;

#include <functional>
using std::function;
using std::bind;

#include <list>
using std::list;

namespace MyRealTimeInputManager {
	
	using Callbacks = unordered_map<string, function<void()> >;
	
	struct CommandInfo {
		public:
			CommandInfo() {
				Clear();
			}
			
			string CommandName;
			set<int> Commands; //здесь хранится имя команды и коды кнопок, с ней связанны
			bool is_active;
			
			int count; //здесь хранится кол-во кнопок, связанное с коммандой, т.е. размер Commands
			
		private:
			void Clear() {
				count = 0;
				is_active = false;
			}
	};
	
	using Command = list <CommandInfo>;
	
	class RealTimeInputManager {
		public:
			RealTimeInputManager();
			
			void Update();
			void SetFocus(const bool& l_focus);
			
			void HandleRealTimeInput();
	
			// Needs to be defined in the header!
			template<class T>
			bool AddCallback(const string& l_name, 
							 void(T::*l_func)(), 
							 T* l_instance)
			{
				function<void()> temp = 
					bind(l_func,l_instance);
				return m_callbacks.emplace(l_name, temp).second;
			}
		
			void RemoveCallback(const string& l_name){
				m_callbacks.erase(l_name);
			}
			
		private:
			Command m_command;
			map<int, bool> Codes; //здесь хранится код кнопки и флаг, обозначащий нажатие
			
			map<string, function<void()> > m_callbacks; //имя команды - функция, которая эту команду исполняет
					
			void LoadBindings();
			void Clear(); //обнулить массив Codes
			bool m_hasFocus;
	};

}


#endif
