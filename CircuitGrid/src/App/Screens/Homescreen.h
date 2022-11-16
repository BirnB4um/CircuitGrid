#pragma once
#include <SFML/Graphics.hpp>
#include "../AppData.h"
#include "../../GUI/Button.h"

class Homescreen
{
private:
	Button startbutton;
	sf::RectangleShape logo;

public:
	Homescreen();
	~Homescreen();
	void init();
	void resize();
	void on_closing();
	void handle_events(sf::Event& ev);
	void update();
	void render(sf::RenderTarget& window);
};
