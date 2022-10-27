#include "../Simulationscreen.h"

void InfoBox::init() {
	bg_rect.setFillColor(sf::Color(0,0,0,255));
	bg_rect.setOutlineColor(sf::Color(255,255,255,255));
	bg_rect.setOutlineThickness(3);

	info_text.setFont(*font);
	info_text.setFillColor(sf::Color(255,255,255,255));
	info_text.setString("Info:");
	info_text.setStyle(sf::Text::Bold);

	name_text.setFont(*font);
	name_text.setFillColor(sf::Color(255,255,255,255));

	electricity_text.setFont(*font);
	electricity_text.setFillColor(sf::Color(255,255,255,255));

	additional_data_text.setFont(*font);
	additional_data_text.setFillColor(sf::Color(255,255,255,255));

	last_additional_data_text.setFont(*font);
	last_additional_data_text.setFillColor(sf::Color(255,255,255,255));
}
void InfoBox::resize() {
	int x, y, w, h, stroke_width;

	stroke_width = 2;
	h = SCREEN_HEIGHT * 0.15f;
	w = h * 1.5f;
	x = stroke_width;
	y = SCREEN_HEIGHT - h - stroke_width;
	bg_rect.setPosition(x, y);
	bg_rect.setSize(sf::Vector2f(w, h));
	bg_rect.setOutlineThickness(stroke_width);

	x = bg_rect.getPosition().x + 10;
	y = bg_rect.getPosition().y + bg_rect.getSize().y * 0.01f;
	h = bg_rect.getSize().y * 0.2;
	info_text.setPosition(x, y);
	info_text.setCharacterSize(h);

	x = bg_rect.getPosition().x + 10;
	y = info_text.getPosition().y + info_text.getCharacterSize() * 1.1f;
	h = bg_rect.getSize().y * 0.15f;
	name_text.setPosition(x, y);
	name_text.setCharacterSize(h);

	x = bg_rect.getPosition().x + 10;
	y = name_text.getPosition().y + name_text.getCharacterSize() * 1.1f;
	electricity_text.setPosition(x, y);
	electricity_text.setCharacterSize(h);

	x = bg_rect.getPosition().x + 10;
	y = electricity_text.getPosition().y + electricity_text.getCharacterSize() * 1.1f;
	additional_data_text.setPosition(x, y);
	additional_data_text.setCharacterSize(h);

	x = bg_rect.getPosition().x + 10;
	y = additional_data_text.getPosition().y + additional_data_text.getCharacterSize() * 1.1f;
	last_additional_data_text.setPosition(x, y);
	last_additional_data_text.setCharacterSize(h);

}
void InfoBox::update() {
	if (sim->mouse_over_board) {
		name_text.setString("Name: " + item_names[this_board[long(floor(board_mouse.y) * board_width + floor(board_mouse.x)) * 4]]);
		electricity_text.setString("Electricity.: " + std::to_string(this_board[long(floor(board_mouse.y) * board_width + floor(board_mouse.x)) * 4 + 1]));
		additional_data_text.setString("Additional Data: " + std::to_string(this_board[long(floor(board_mouse.y) * board_width + floor(board_mouse.x)) * 4 + 2]));
		last_additional_data_text.setString("Last Data: " + std::to_string(this_board[long(floor(board_mouse.y) * board_width + floor(board_mouse.x)) * 4 + 3]));
	}
}
void InfoBox::render(sf::RenderTarget &window) {
	window.draw(bg_rect);
	window.draw(info_text);
	window.draw(name_text);
	window.draw(electricity_text);
	window.draw(additional_data_text);
	window.draw(last_additional_data_text);
}
