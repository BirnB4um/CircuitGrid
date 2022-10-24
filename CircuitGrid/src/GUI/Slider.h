#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include "GUI_Item.h"

using namespace std;

class Slider :GUI_Item
{
private:
	sf::RectangleShape line_rect;
	sf::RectangleShape nob_rect;
	std::function<void()> func;

public:
	sf::RectangleShape rect;
	bool pressed = false;
	float value = 0.0f;

	//called everytime value gets changed ('pressed = false' when slider is released)
	void set_function(std::function<void()> f);
	void press(int& mouse_x, int& mouse_y);
	void update(int& mouse_x, int& mouse_y);
	void update_scale();
	void init();
	bool check_over_slider(int& x, int& y);
	void set_position(float x, float y);
	void set_size(float w, float h);
	void set_nob_texture_inrect(float x, float y, float w, float h);
	void render(sf::RenderTarget& window);
};
