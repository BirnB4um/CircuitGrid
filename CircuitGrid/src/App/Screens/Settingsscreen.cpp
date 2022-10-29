#include "Settingsscreen.h"

Settingsscreen::Settingsscreen() {

}
Settingsscreen::~Settingsscreen() {

}

void Settingsscreen::init() {

}

void Settingsscreen::resize() {

}

void Settingsscreen::on_closing() {

}

void Settingsscreen::handle_events(sf::Event& ev) {
	if (ev.type == sf::Event::KeyReleased) {
		if (ev.key.code == sf::Keyboard::L) {
			screen_id = SIMULATION;
		}
	}
}

void Settingsscreen::update() {

}

void Settingsscreen::render(sf::RenderTarget& window) {

}