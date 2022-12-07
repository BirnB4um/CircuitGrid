#pragma once
#include <SFML/Graphics.hpp>
#include "../App/AppData.h"

class NumberInputBox {

private:
	sf::RectangleShape bound_rect;
	sf::Text text;
	int value;


public:
	NumberInputBox();
	~NumberInputBox();

	bool check_over_button(int &x, int &y);

	void init();
	void set_position(int x, int y);
	void set_size(int width, int height);
	void update();
	void render(sf::RenderTarget& window);
	int get_value();

};