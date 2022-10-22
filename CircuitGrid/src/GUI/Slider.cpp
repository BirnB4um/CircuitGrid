#include "Slider.h"

void Slider::init() {
	pressed = false;
	value = 0.0f;
	nob_rect.setFillColor(sf::Color::White);
	//nob_rect.setTexture(gui_texture);
	//nob_rect.setTextureRect(sf::IntRect(0, 0, 16, 16));
	line_rect.setFillColor(sf::Color(255, 255, 255, 255));
	line_rect.setOutlineColor(sf::Color::Transparent);
	line_rect.setOutlineThickness(0);

	bound_rect.top = 0;
	bound_rect.left = 0;
	bound_rect.width = 100;
	bound_rect.height = 40;
	update_scale();
}

void Slider::press(int& mouse_x, int& mouse_y) {
	if (mouse_x > nob_rect.getPosition().x && mouse_x < nob_rect.getPosition().x + nob_rect.getSize().x &&
		mouse_y > nob_rect.getPosition().y && mouse_y < nob_rect.getPosition().y + nob_rect.getSize().y) {
		pressed = true;
	}
}

void Slider::set_function(std::function<void()> f) {
	func = f;
}

void Slider::update(int& mouse_x, int& mouse_y) {
	if (!pressed)
		return;

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		pressed = false;

	value = float(mouse_x - line_rect.getPosition().x) / line_rect.getSize().x;
	value = value < 0 ? 0 : value > 1 ? 1 : value;

	func();

	update_scale();
}

void Slider::update_scale() {
	nob_rect.setSize(sf::Vector2f(bound_rect.height, bound_rect.height));
	nob_rect.setPosition(bound_rect.left + value * (bound_rect.width - nob_rect.getSize().x), bound_rect.top);

	line_rect.setSize(sf::Vector2f(bound_rect.width - nob_rect.getSize().x, bound_rect.height / 20));
	line_rect.setPosition(bound_rect.left + nob_rect.getSize().x / 2, bound_rect.top + bound_rect.height / 2 - line_rect.getSize().y);
}

bool Slider::check_over_slider(int& x, int& y) {
	return x >= bound_rect.left && x <= bound_rect.left + bound_rect.width &&
		y >= bound_rect.top && y <= bound_rect.top + bound_rect.height;
}

void Slider::set_position(float x, float y) {
	bound_rect.left = x;
	bound_rect.top = y;

	update_scale();
}
void Slider::set_size(float w, float h) {
	bound_rect.width = w;
	bound_rect.height = h;

	update_scale();
}
void Slider::set_nob_texture_inrect(float x, float y, float w, float h) {
	nob_rect.setTextureRect(sf::IntRect(x, y, w, h));
}
void Slider::render(sf::RenderTarget& window) {
	window.draw(line_rect);
	window.draw(nob_rect);
}