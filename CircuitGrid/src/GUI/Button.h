#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <functional>
#include "GUI_Item.h"

struct Button :GUI_Item
{
private:

public:
	int texture_top, texture_left, texture_width, texture_height;
	int hoverover_texture_top, hoverover_texture_left, hoverover_texture_width, hoverover_texture_height;
	int pressed_texture_top, pressed_texture_left, pressed_texture_width, pressed_texture_height;

	bool hover_over;
	bool pressed;

	sf::RectangleShape rect;
	std::function<void()> func;

	void init();
	bool update(int& mouse_x, int& mouse_y);
	void set_function(std::function<void()> f);
	void set_position(float x, float y);
	void set_size(float w, float h);
	void set_texture_inrect(int x, int y, int w, int h);
	void set_hoverover_texture_inrect(int x, int y, int w, int h);
	void set_pressed_texture_inrect(int x, int y, int w, int h);
	void render(sf::RenderTarget& window);

	Button();
	Button(float pos_x, float pos_y, float width, float height);
	~Button();
};
