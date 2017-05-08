#ifndef CONST_H_
#define CONST_H_

#include <SFML/Graphics.hpp>
using sf::Vector2u;


namespace MyConst {
	
	const size_t arrayOfObjectsCapacity = 2;
	
	const float maxSpeedOfEveryFighter = 100; //not used
	const float accelerationOfFreeFall = 50;
	
	const std::string TitleOfMainWindow = "GAME FIGHTING!";
	const Vector2u DefaultSizeOfMainWindow = Vector2u(800, 600);
	
	//~ const std::string PathToBotInitialSettings = "Settings/bot_initial_settings";
	//~ const std::string PathToPlayerInitialSettings = "Settings/player_initial_settings";
	
	const std::string PathToEventCommandsSettings = "Settings/keys_for_events.cfg";
	const std::string PathToRealTimeInputCommandsSettings = "Settings/keys_for_realTimeInput.cfg";
}

#endif
