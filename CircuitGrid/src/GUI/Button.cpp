#include "Button.h"

Button::~Button() {
}

Button::Button() {
	init();
}

Button::Button(float pos_x, float pos_y, float width, float height) {
	rect.setPosition(pos_x, pos_y);
	rect.setSize(sf::Vector2f(width, height));
	init();
}

void Button::init() {
	hover_over = false;
	pressed = false;
	rect.setTexture(gui_texture);
}

bool Button::check_over_button(int &x, int &y) {
	return x >= rect.getPosition().x && x <= rect.getPosition().x + rect.getSize().x &&
		   y >= rect.getPosition().y && y <= rect.getPosition().y + rect.getSize().y;
}

bool Button::update(int& mouse_x, int& mouse_y) {
	bool called_function = false;
	if (check_over_button(mouse_x, mouse_y)) {
		hover_over = true;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			pressed = true;
		}
		else if (pressed) {
			func();
			pressed = false;
			called_function = true;
		}
	}
	else {
		if (!hover_over)
			return false;

		hover_over = false;
		pressed = false;
	}

	if (hover_over) {
		if (pressed) {
			rect.setTextureRect(sf::IntRect(pressed_texture_left, pressed_texture_top, pressed_texture_width, pressed_texture_height));
		}
		else {
			rect.setTextureRect(sf::IntRect(hoverover_texture_left, hoverover_texture_top, hoverover_texture_width, hoverover_texture_height));
		}
	}
	else {
		rect.setTextureRect(sf::IntRect(texture_left, texture_top, texture_width, texture_height));
	}

	return called_function;
}

void Button::set_function(std::function<void()> f) {
	func = f;
}

void Button::set_position(float x, float y) {
	rect.setPosition(x, y);
}
void Button::set_size(float w, float h) {
	rect.setSize(sf::Vector2f(w, h));
}

void Button::set_texture_inrect(int x, int y, int w, int h) {
	texture_left = x;
	texture_top = y;
	texture_width = w;
	texture_height = h;
	rect.setTextureRect(sf::IntRect(x, y, w, h));
}
void Button::set_hoverover_texture_inrect(int x, int y, int w, int h) {
	hoverover_texture_left = x;
	hoverover_texture_top = y;
	hoverover_texture_width = w;
	hoverover_texture_height = h;
}
void Button::set_pressed_texture_inrect(int x, int y, int w, int h) {
	pressed_texture_left = x;
	pressed_texture_top = y;
	pressed_texture_width = w;
	pressed_texture_height = h;
}

void Button::render(sf::RenderTarget& window) {
	window.draw(rect);
}