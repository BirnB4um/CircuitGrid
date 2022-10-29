#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../AppData.h"
#include "../../GUI/Button.h"


class Settingsscreen
{
private:


public:

	sf::RectangleShape middle_line;

	Button back_button;

	sf::Text board_text;

	Settingsscreen();
	~Settingsscreen();
	void init();
	void resize();
	void on_closing();
	void handle_events(sf::Event& ev);
	void update();
	void render(sf::RenderTarget& window);

};

