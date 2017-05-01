#ifndef CONST_H_
#define CONST_H_

#include <SFML/Graphics.hpp>
using sf::Vector2u;


namespace MyConst {
	
	const size_t arrayOfObjectsCapacity = 2;
	const double maxSpeedOfEveryFighter = 100;
	const std::string TitleOfMainWindow = "GAME FIGHTING!";
	const Vector2u DefaultSizeOfMainWindow = Vector2u(800, 600);
	
	//~ const std::string PathToBotInitialSettings = "Settings/bot_initial_settings";
	//~ const std::string PathToPlayerInitialSettings = "Settings/player_initial_settings";
	
	const std::string PathToPlayerSettings = "Settings/keys_for_events.cfg";
}

#endif
