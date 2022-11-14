#include "../Simulationscreen.h"

void InfoBox::init() {
	bg_rect.setFillColor(sf::Color(0,0,0,255));
	bg_rect.setOutlineColor(sf::Color(255,255,255,255));
	bg_rect.setOutlineThickness(3);

	info_text.setFont(*font);
	info_text.setFillColor(sf::Color(255,255,255,255));
	info_text.setString("Info:");
	info_text.setStyle(sf::Text::Bold);

	coords_text.setFont(*font);
	coords_text.setFillColor(sf::Color(255,255,255,255));

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
	h = SCREEN_HEIGHT * 0.13f;
	w = h * 2.2f;
	x = stroke_width;
	y = SCREEN_HEIGHT - h - stroke_width - sim->gui.settings_button.rect.getSize().y;
	bg_rect.setPosition(x, y);
	bg_rect.setSize(sf::Vector2f(w, h));
	bg_rect.setOutlineThickness(stroke_width);

	x = bg_rect.getPosition().x + 10;
	y = bg_rect.getPosition().y + bg_rect.getSize().y * 0.01f;
	h = bg_rect.getSize().y * 0.2f;
	info_text.setPosition(x, y);
	info_text.setCharacterSize(h);

	h = info_text.getCharacterSize() * 0.7f;
	x = info_text.getPosition().x + info_text.getGlobalBounds().width * 1.2f;
	y = info_text.getPosition().y + info_text.getCharacterSize() * 0.5f - h * 0.4f;
	coords_text.setPosition(x, y);
	coords_text.setCharacterSize(h);

	x = bg_rect.getPosition().x + 10;
	y = info_text.getPosition().y + info_text.getCharacterSize() * 1.4f;
	h = bg_rect.getSize().y * 0.12f;
	name_text.setPosition(x, y);
	name_text.setCharacterSize(h);

	x = bg_rect.getPosition().x + 10;
	y = name_text.getPosition().y + name_text.getCharacterSize() * 1.3f;
	electricity_text.setPosition(x, y);
	electricity_text.setCharacterSize(h);

	x = bg_rect.getPosition().x + 10;
	y = electricity_text.getPosition().y + electricity_text.getCharacterSize() * 1.3f;
	additional_data_text.setPosition(x, y);
	additional_data_text.setCharacterSize(h);

	x = bg_rect.getPosition().x + 10;
	y = additional_data_text.getPosition().y + additional_data_text.getCharacterSize() * 1.3f;
	last_additional_data_text.setPosition(x, y);
	last_additional_data_text.setCharacterSize(h);

}
void InfoBox::update() {
	if (sim->mouse_over_board) {
		std::string name = item_names[this_board[long(floor(board_mouse.y) * board_width + floor(board_mouse.x)) * 4]];
		name_text.setString("Name: " + name);
		
		electricity_text.setString((name == item_names[BRIDGE] ? "Electricity horizontal: " : "Electricity.: ") 
								+ std::to_string(this_board[long(floor(board_mouse.y) * board_width + floor(board_mouse.x)) * 4 + 1]));
		
		additional_data_text.setString( (name == item_names[REPEATER] ? "Delay Value: " :
										name == item_names[BRIDGE] ? "Electricity vertical: " :
										name == item_names[CLOCK] ? "Clock resettime: " :
										"Additional Data: ")
								+ std::to_string(this_board[long(floor(board_mouse.y) * board_width + floor(board_mouse.x)) * 4 + 2] + 
												(name == item_names[REPEATER] ? -2 : 0)) + (name == item_names[REPEATER] || name == item_names[CLOCK] ? " (+/-)" : ""));
		
		last_additional_data_text.setString((name == item_names[CLOCK] ? "Current time: " :
											"Additional Data: ") 
			+ std::to_string(this_board[long(floor(board_mouse.y) * board_width + floor(board_mouse.x)) * 4 + 3]));
		
		coords_text.setString(sim->selection_set ? "W:" + std::to_string(int(sim->selection_end_x - sim->selection_start_x + 1)) + 
						" H:" + std::to_string(int(sim->selection_end_y - sim->selection_start_y + 1)) :
							"X:" + std::to_string(int(floor(board_mouse.x))) + " Y:" + std::to_string(int(floor(board_mouse.y))));
	}
}
void InfoBox::render(sf::RenderTarget &window) {
	window.draw(bg_rect);
	window.draw(info_text);
	window.draw(coords_text);
	window.draw(name_text);
	window.draw(electricity_text);
	window.draw(additional_data_text);
	window.draw(last_additional_data_text);
}
