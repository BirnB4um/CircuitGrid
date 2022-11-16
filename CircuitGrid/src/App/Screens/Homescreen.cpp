#include "Homescreen.h"

Homescreen::Homescreen() {
}

Homescreen::~Homescreen() {
}

void Homescreen::init() {
	startbutton.init();
	startbutton.set_texture_inrect(0, 0, 26, 9);
	startbutton.set_hoverover_texture_inrect(0, 9, 26, 9);
	startbutton.set_pressed_texture_inrect(0, 18, 26, 9);
	startbutton.set_function([&]() {
		screen_id = SIMULATION;
		});

	logo.setTexture(GUI_Item::gui_texture);
	logo.setTextureRect(sf::IntRect(0,231, 130, 25));

	version_text.setFont(*font);
	version_text.setString(version_str);
	version_text.setFillColor(sf::Color(150,150,150,255));
}

void Homescreen::resize() {
	int x, y, w, h;

	h = SCREEN_HEIGHT * 0.15f;
	w = h * (float(logo.getTextureRect().width) / logo.getTextureRect().height);
	x = SCREEN_WIDTH / 2 - w / 2;
	y = SCREEN_HEIGHT / 4;
	logo.setSize(sf::Vector2f(w, h));
	logo.setPosition(x, y);

	h = SCREEN_HEIGHT * 0.1f;
	w = h * (float(startbutton.texture_width) / startbutton.texture_height);
	x = SCREEN_WIDTH / 2 - w / 2;
	y = SCREEN_HEIGHT / 2 - h / 2;
	startbutton.set_position(x, y);
	startbutton.set_size(w, h);

	h = SCREEN_HEIGHT * 0.02f;
	x = h * 0.5f;
	y = SCREEN_HEIGHT - h * 1.5f;
	version_text.setCharacterSize(h);
	version_text.setPosition(x, y);
}

void Homescreen::on_closing() {
}

void Homescreen::handle_events(sf::Event& ev) {
}

void Homescreen::update() {
	startbutton.update(window_mouse.x, window_mouse.y);
}

void Homescreen::render(sf::RenderTarget& window) {
	startbutton.render(window);
	window.draw(version_text);
	window.draw(logo);
}