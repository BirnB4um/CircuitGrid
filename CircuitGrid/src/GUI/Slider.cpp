#include "Slider.h"

void Slider::init() {
	pressed = false;
	value = 0.0f;
	//nob_rect.setFillColor(sf::Color::White);
	nob_rect.setTexture(gui_texture);
	line_rect.setFillColor(sf::Color(255, 255, 255, 255));
	line_rect.setOutlineColor(sf::Color::Transparent);
	line_rect.setOutlineThickness(0);

	rect.setPosition(0, 0);
	rect.setSize(sf::Vector2f(100, 40));
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
	nob_rect.setSize(sf::Vector2f(int(rect.getSize().y), int(rect.getSize().y)));
	nob_rect.setPosition(int(rect.getPosition().x + value * (rect.getSize().x - nob_rect.getSize().x)), int(rect.getPosition().y));

	line_rect.setSize(sf::Vector2f(int(rect.getSize().x - nob_rect.getSize().x), int(rect.getSize().y / 20)));
	line_rect.setPosition(int(rect.getPosition().x + nob_rect.getSize().x / 2), int(rect.getPosition().y + rect.getSize().y / 2 - line_rect.getSize().y));
}

bool Slider::check_over_slider(int& x, int& y) {
	return x >= rect.getPosition().x && x <= rect.getPosition().x + rect.getSize().x &&
		y >= rect.getPosition().y && y <= rect.getPosition().y + rect.getSize().y;
}

void Slider::set_position(int x, int y) {
	rect.setPosition(x, y);

	update_scale();
}
void Slider::set_size(float w, float h) {
	rect.setSize(sf::Vector2f(w, h));

	update_scale();
}
void Slider::set_nob_texture_inrect(float x, float y, float w, float h) {
	nob_rect.setTextureRect(sf::IntRect(x, y, w, h));
}
void Slider::render(sf::RenderTarget& window) {
	window.draw(line_rect);
	window.draw(nob_rect);
}