#include "Settingsscreen.h"

Settingsscreen::Settingsscreen() {

}
Settingsscreen::~Settingsscreen() {

}

void Settingsscreen::init() {
	middle_line.setFillColor(sf::Color(255,255,255,255));
	middle_line.setOutlineThickness(0);
	

	back_button.init();
	back_button.set_texture_inrect(159, 0, 19,9);
	back_button.set_hoverover_texture_inrect(159, 9, 19,9);
	back_button.set_pressed_texture_inrect(159, 18, 19,9);
	back_button.set_function([&]() {
		screen_id = SIMULATION;
		});

	board_text.setFont(*font);
	board_text.setString("Board settings");
	board_text.setStyle(sf::Text::Bold);



}

void Settingsscreen::resize() {
	int x, y, w, h, stroke_width;

	x = SCREEN_WIDTH * 0.7f;
	y = 0;
	w = 2;
	h = SCREEN_HEIGHT;
	middle_line.setPosition(x, y);
	middle_line.setSize(sf::Vector2f(w,h));


	h = SCREEN_HEIGHT * 0.05f;
	board_text.setPosition(0,0);
	board_text.setCharacterSize(h);
	x = middle_line.getPosition().x + ((SCREEN_WIDTH - middle_line.getPosition().x) - board_text.getGlobalBounds().width) * 0.5f;
	y = SCREEN_HEIGHT * 0.1f;
	board_text.setPosition(x, y);


	h = SCREEN_HEIGHT * 0.05f;
	w = h * (19.0f / 9.0f);
	x = SCREEN_WIDTH - w;
	y = SCREEN_HEIGHT - h;
	back_button.set_position(x, y);
	back_button.set_size(w, h);

}

void Settingsscreen::on_closing() {

}

void Settingsscreen::handle_events(sf::Event& ev) {
	if (ev.type == sf::Event::KeyReleased) {
		if (ev.key.code == sf::Keyboard::L) {
		}
	}
}

void Settingsscreen::update() {
	back_button.update(window_mouse.x, window_mouse.y);
}

void Settingsscreen::render(sf::RenderTarget& window) {

	window.draw(middle_line);

	back_button.render(window);

	window.draw(board_text);
}