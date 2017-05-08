#include "RealTimeInputManager.h"

namespace MyRealTimeInputManager {
	
	bool compare_count(const CommandInfo first, const CommandInfo second) {
		return (first.count >= second.count);					
	}
	
	RealTimeInputManager::RealTimeInputManager():
		m_hasFocus(true)
	{
		LoadBindings();
	}
	
	void RealTimeInputManager::LoadBindings() {
		ifstream file(MyConst::PathToRealTimeInputCommandsSettings);
		
		if (!file.is_open()) {
			string msg = "No " + MyConst::PathToRealTimeInputCommandsSettings;
			throw Exception(ExcType::fileNotFound, msg);
		}
		
		string line;
		while (getline(file, line)) {
			stringstream codeStream(line);
			
			string CommandName;
			codeStream >> CommandName;
			if (CommandName == "") {
				continue;
			}
			
			CommandInfo *l_commandInfo = nullptr;
			l_commandInfo = new CommandInfo();
			if (l_commandInfo == nullptr) {
				string msg = "In LoadBindings, RealTimeInput";
				throw Exception(ExcType::badAlloc, msg);
			}
			
			while (!codeStream.eof()) {
				string keycode;
				codeStream >> keycode;
				
				int int_keycode = stoi(keycode);
				
				l_commandInfo->Commands.insert(int_keycode);
				++l_commandInfo->count;
				
				Codes.insert(make_pair(int_keycode, false));
						
			}
				l_commandInfo->CommandName = CommandName;
				m_command.push_back(*l_commandInfo);
				
				l_commandInfo = nullptr;
		}
		
		m_command.sort(compare_count);
		
		file.close();
	}
	
	void RealTimeInputManager::SetFocus(const bool& l_focus) {
		
		m_hasFocus = l_focus;
		
	}
	
	void RealTimeInputManager::Clear() {
		
		for (auto itr = Codes.begin(); itr != Codes.end(); ++itr) {
			itr->second = false;
		}
		
	}
	
	void RealTimeInputManager::HandleRealTimeInput() {
		
		for (auto itr = Codes.begin(); itr != Codes.end(); ++itr) {
			if (Keyboard::isKeyPressed(Keyboard::Key(itr->first))) {
				itr->second = true;
				
				//for test
				//~ if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(0))) {
					//~ std::cout << "pressed A" << std::endl;
				//~ }
				
			} else {
				itr->second = false;
			}
		}
		
	}
	
	void RealTimeInputManager::Update() {
		map<int, bool> l_codes;
		
		for (auto itr_1 = m_command.begin(); itr_1 != m_command.end();
			 ++itr_1)
		{
			
			l_codes = Codes;			
			int count = 0;
			
			for (auto itr_2 = itr_1->Commands.begin(); itr_2 != itr_1->Commands.end();
				 ++itr_2)
			{
				if (l_codes[(*itr_2)]) {
					
					l_codes[(*itr_2)] = false;
				} else {
					break;
				}
				
				++count;
				
				if (count == itr_1->count) {
					Codes = l_codes;
					itr_1->is_active = true;
				}
			}
			
		}
		
		for (auto itr = m_command.begin(); itr != m_command.end();
			 ++itr)
		{
			
			if (itr->is_active) {
				itr->is_active = false;
				auto callItr = m_callbacks.find(itr->CommandName);
				callItr->second();
			}
		}
		
		
		Clear();
		
	}
	
}
