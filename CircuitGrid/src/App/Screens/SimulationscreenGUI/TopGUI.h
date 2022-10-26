#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../../../GUI/Button.h"

class Simulationscreen;

class TopGUI
{
public:
	Simulationscreen* sim;

	Button pause_button;

	Button item_button;

	sf::Text tps_text;
	Slider tps_slider;

	Button edit_button;
	Button fill_button;
	Button reset_button;
	Button grid_button;
	Button detail_button;

	void init();
	void update_item_button_texture();
	void update();
	void resize();
	void render(sf::RenderTarget& window);
};

