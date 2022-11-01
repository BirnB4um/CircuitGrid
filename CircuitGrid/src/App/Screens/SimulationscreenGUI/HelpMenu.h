#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../../../GUI/Button.h"

class Simulationscreen;

class HelpMenu
{
public:
	Simulationscreen* sim;

	sf::RectangleShape help_bg_rect;
	sf::Text help_tps_slider_text;
	sf::Text help_edit_button_text;
	sf::Text help_fill_button_text;
	sf::Text help_reset_button_text;
	sf::Text help_grid_button_text;
	sf::Text help_details_button_text;
	sf::Text help_selection_button_text;
	sf::Text help_item_button_text;
	sf::Text help_hotkeys_text;
	sf::Text help_close_text;


	void init();
	void resize();
	void update();
	void render(sf::RenderTarget& window);

};

