#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../AppData.h"


class Settingsscreen
{
private:


public:
	Settingsscreen();
	~Settingsscreen();
	void init();
	void resize();
	void on_closing();
	void handle_events(sf::Event& ev);
	void update();
	void render(sf::RenderTarget& window);

};

