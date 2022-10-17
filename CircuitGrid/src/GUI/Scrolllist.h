#pragma once
#include "GUI_Item.h"
#include "Button.h"

class Scrolllist :GUI_Item
{
private:
	bool horizontal;
	bool pressed;

public:

	int steps;
	int current_step;
	float step_percentage;
	sf::RectangleShape bound_rect;
	sf::RectangleShape pad;
	Button button_one;
	Button button_two;

	void init(bool horizontal, unsigned int steps);
	void update(int& mouse_x, int& mouse_y);
	void resize();
	void set_position(float x, float y);
	void set_size(float w, float h);
	void render(sf::RenderTarget& window);

	Scrolllist();
	~Scrolllist();
};
