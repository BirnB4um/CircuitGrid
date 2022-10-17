#pragma once

#include <SFML/Graphics.hpp>

#include "AppData.h"
#include "../GUI/GUI_Item.h"
#include "Screens/Homescreen.h"
#include "Screens/Simulationscreen.h"

class Application
{
private:
	//window stuff
	sf::RenderWindow window;
	sf::View normal_view;
	sf::Event sf_event;

	//Screens
	Homescreen homescreen;
	Simulationscreen simulationscreen;

	void create_window(unsigned int width, unsigned int height, bool fullscreen, int fps, std::string title);
	void on_closing();
	void on_resize();
	void handle_events();
	void update();
	void draw();

public:
	Application();
	~Application();
	void init();
	void run();
};
