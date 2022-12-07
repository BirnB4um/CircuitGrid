#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../AppData.h"
#include "../../GUI/Button.h"
#include "../../GUI/NumberInputBox.h"


class Settingsscreen
{
private:


public:

	sf::RectangleShape middle_line;

	Button back_button;

	sf::Text board_text;
	Button save_board_button;
	Button load_board_button;

	sf::Text board_width_text;
	sf::Text board_height_text;
	
	Button create_board_button;

	void load_board();
	void save_board();

	void create_board(int width, int height);

	Settingsscreen();
	~Settingsscreen();
	void init();
	void resize();
	void on_closing();
	void handle_events(sf::Event& ev);
	void update();
	void render(sf::RenderTarget& window);

};

