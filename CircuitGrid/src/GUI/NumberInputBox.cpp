#include "NumberInputBox.h"

NumberInputBox::NumberInputBox() {

}
NumberInputBox::~NumberInputBox() {

}


void NumberInputBox::init() {
	text.setFont(*font);
}

bool NumberInputBox::check_over_button(int& x, int& y) {
	return x > bound_rect.getPosition().x && x < bound_rect.getPosition().x + bound_rect.getSize().y &&
		y > bound_rect.getPosition().y && y < bound_rect.getPosition().y + bound_rect.getSize().y;
}

int NumberInputBox::get_value() {
	return value;
}

void NumberInputBox::update() {

}

void NumberInputBox::set_position(int x, int y) {

}

void NumberInputBox::set_size(int width, int height) {

}

void NumberInputBox::render(sf::RenderTarget &window) {
	window.draw(bound_rect);
	window.draw(text);
}

