#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../../../GUI/Button.h"

class Simulationscreen;

class InfoBox
{
public:
	Simulationscreen* sim;

	sf::RectangleShape bg_rect;
	sf::Text info_text;
	sf::Text coords_text;
	sf::Text name_text;
	sf::Text electricity_text;
	sf::Text additional_data_text;
	sf::Text last_additional_data_text;

	void init();
	void resize();
	void update();
	void render(sf::RenderTarget& window);
};

