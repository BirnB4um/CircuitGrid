#include "Scrolllist.h"

Scrolllist::Scrolllist() {
}
Scrolllist::~Scrolllist() {
}

void Scrolllist::init(bool horizontal, unsigned int steps) {
	this->horizontal = horizontal;
	this->steps = steps;

	pressed = false;
	current_step = 0;
	step_percentage = 0;

	bound_rect.setFillColor(sf::Color(10, 10, 10, 255));
	bound_rect.setOutlineColor(sf::Color(255, 255, 255, 255));
	bound_rect.setOutlineThickness(2);
	pad.setOutlineColor(sf::Color(255, 255, 255, 255));
	pad.setOutlineThickness(2);

	if (horizontal) {// ___
		// <-
		button_one.set_texture_inrect(221, 27, 9, 9);
		button_one.set_hoverover_texture_inrect(221, 36, 9, 9);
		button_one.set_pressed_texture_inrect(221, 45, 9, 9);
		button_one.set_function([&]() {
			current_step--;
			});

		// ->
		button_two.set_texture_inrect(221, 0, 9, 9);
		button_two.set_hoverover_texture_inrect(221, 9, 9, 9);
		button_two.set_pressed_texture_inrect(221, 18, 9, 9);
		button_two.set_function([&]() {
			current_step++;
			});
	}
	else {//  |
		// ^
		button_one.set_texture_inrect(230, 27, 9, 9);
		button_one.set_hoverover_texture_inrect(230, 36, 9, 9);
		button_one.set_pressed_texture_inrect(230, 45, 9, 9);
		button_one.set_function([&]() {
			current_step--;
			});

		//  \/
		button_two.set_texture_inrect(230, 0, 9, 9);
		button_two.set_hoverover_texture_inrect(230, 9, 9, 9);
		button_two.set_pressed_texture_inrect(230, 18, 9, 9);
		button_two.set_function([&]() {
			current_step++;
			});
	}

	resize();
}

void Scrolllist::resize() {
	if (horizontal) {// ___
		button_one.set_size(bound_rect.getSize().y, bound_rect.getSize().y);
		button_one.set_position(bound_rect.getPosition().x, bound_rect.getPosition().y);

		button_two.set_size(bound_rect.getSize().y, bound_rect.getSize().y);
		button_two.set_position(bound_rect.getPosition().x + bound_rect.getSize().x - button_two.rect.getSize().x, bound_rect.getPosition().y);

		int pad_size = (bound_rect.getSize().x - 2 * button_one.rect.getSize().y) / steps;
		pad_size = float(pad_size) / (bound_rect.getSize().x - button_one.rect.getSize().x * 2) < 0.1f ? int((bound_rect.getSize().x - button_one.rect.getSize().x * 2) * 0.1f) : pad_size;
		pad.setSize(sf::Vector2f(pad_size, int(bound_rect.getSize().y)));
	}
	else {//  |
		button_one.set_size(bound_rect.getSize().x, bound_rect.getSize().x);
		button_one.set_position(bound_rect.getPosition().x, bound_rect.getPosition().y);

		button_two.set_size(bound_rect.getSize().x, bound_rect.getSize().x);
		button_two.set_position(bound_rect.getPosition().x, bound_rect.getPosition().y + bound_rect.getSize().y - button_two.rect.getSize().y);

		int pad_size = (bound_rect.getSize().y - 2 * button_one.rect.getSize().x) / steps;
		pad_size = float(pad_size) / (bound_rect.getSize().y - button_one.rect.getSize().y * 2) < 0.1f ? int((bound_rect.getSize().y - button_one.rect.getSize().y * 2) * 0.1f) : pad_size;
		pad.setSize(sf::Vector2f(int(bound_rect.getSize().x), pad_size));
	}
}

void Scrolllist::update(int& mouse_x, int& mouse_y) {
	//if (mouse_left_pressed) {
	if (mouse_x > pad.getPosition().x && mouse_x < pad.getPosition().x + pad.getSize().x &&
		mouse_y > pad.getPosition().y && mouse_y < pad.getPosition().y + pad.getSize().y) {
		pressed = true;
	}
	//}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		pressed = false;
	}

	if (pressed) {
		pad.setFillColor(sf::Color(200, 200, 200, 255));
	}
	else {
		pad.setFillColor(sf::Color(130, 130, 130, 255));
	}

	if (pressed) {
		if (horizontal) {
			step_percentage = float(mouse_x - bound_rect.getPosition().x - button_one.rect.getSize().x - pad.getSize().x / 2) / (bound_rect.getSize().x - 2 * button_one.rect.getSize().y - pad.getSize().x);
		}
		else {
			step_percentage = float(mouse_y - bound_rect.getPosition().y - button_one.rect.getSize().y - pad.getSize().y / 2) / (bound_rect.getSize().y - 2 * button_one.rect.getSize().x - pad.getSize().y);
		}
	}

	if (button_one.update(mouse_x, mouse_y) || button_two.update(mouse_x, mouse_y)) {
		current_step = current_step < 0 ? 0 : current_step > steps - 1 ? steps - 1 : current_step;
		step_percentage = float(current_step + 0.0001f) / (steps - 1);
	}
	step_percentage = step_percentage < 0 ? 0 : step_percentage > 1 ? 1 : step_percentage;

	current_step = step_percentage * (steps - 1);

	if (horizontal) {
		pad.setPosition(int(bound_rect.getPosition().x + button_one.rect.getSize().x + step_percentage * (bound_rect.getSize().x - 2 * button_one.rect.getSize().y - pad.getSize().x)), int(bound_rect.getPosition().y));
	}
	else {
		pad.setPosition(int(bound_rect.getPosition().x), int(bound_rect.getPosition().y + button_one.rect.getSize().y + step_percentage * (bound_rect.getSize().y - 2 * button_one.rect.getSize().x - pad.getSize().y)));
	}
}

void Scrolllist::set_position(float x, float y) {
	bound_rect.setPosition(int(x), int(y));
	resize();
}

void Scrolllist::set_size(float w, float h) {
	bound_rect.setSize(sf::Vector2f(int(w), int(h)));
	resize();
}

void Scrolllist::render(sf::RenderTarget& window) {
	window.draw(bound_rect);
	button_one.render(window);
	button_two.render(window);
	window.draw(pad);
}