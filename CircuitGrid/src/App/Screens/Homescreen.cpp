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
}

void Homescreen::resize() {
	int x, y, w, h;

	w = SCREEN_WIDTH * 0.2;
	h = w * (float(startbutton.texture_height) / startbutton.texture_width);
	x = SCREEN_WIDTH / 2 - w / 2;
	y = SCREEN_HEIGHT / 2 - h / 2;
	startbutton.set_position(x, y);
	startbutton.set_size(w, h);
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
}