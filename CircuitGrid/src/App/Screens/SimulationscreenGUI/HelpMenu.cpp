#include "../Simulationscreen.h"

void HelpMenu::init() {
	help_bg_rect.setFillColor(sf::Color(0, 0, 0, 150));

	help_tps_slider_text.setFont(*font);
	help_tps_slider_text.setString("< Change tickspeed (ticks per second)");
	help_tps_slider_text.setFillColor(sf::Color(255, 255, 255, 255));

	help_edit_button_text.setFont(*font);
	help_edit_button_text.setString("< Change Edit/Interact-Mode (Pencil:Edit, Hand:Interact) [B]");
	help_edit_button_text.setFillColor(sf::Color(255, 255, 255, 255));

	help_fill_button_text.setFont(*font);
	help_fill_button_text.setString("< Toggle Fill-Mode (fills whole space when drawing) [F]");
	help_fill_button_text.setFillColor(sf::Color(255, 255, 255, 255));

	help_reset_button_text.setFont(*font);
	help_reset_button_text.setString("< Reset Simulation (clear all electricity) [R]");
	help_reset_button_text.setFillColor(sf::Color(255, 255, 255, 255));

	help_grid_button_text.setFont(*font);
	help_grid_button_text.setString("< Toggle Grid [G]");
	help_grid_button_text.setFillColor(sf::Color(255, 255, 255, 255));

	help_details_button_text.setFont(*font);
	help_details_button_text.setString("< Toggle Details when zoomed in [Y]");
	help_details_button_text.setFillColor(sf::Color(255, 255, 255, 255));

	help_selection_button_text.setFont(*font);
	help_selection_button_text.setString("< Toggle to select area [Z]");
	help_selection_button_text.setFillColor(sf::Color(255, 255, 255, 255));

	help_item_button_text.setFont(*font);
	help_item_button_text.setString("Selected Item [E] >");
	help_item_button_text.setFillColor(sf::Color(255, 255, 255, 255));

	help_close_text.setFont(*font);
	help_close_text.setString("Press H to exit this menu");
	help_close_text.setFillColor(sf::Color(255, 255, 255, 255));

	help_hotkeys_text.setFont(*font);
	help_hotkeys_text.setString("W/A/S/D - move board\n"
		"H - show help menu\n"
		"E - open/close inventory\n"
		"SPACE - pause simulation\n"
		"B - toggle edit-mode\n"
		"F - toggle fill-mode\n"
		"R - reset simulation\n"
		"G - toggle grid\n"
		"Y - toggle details\n"
		"Z - toggle selection-mode\n"
		"0 - zoom to origin\n"
		"drag middle mouse button - drag board\n"
		"SCROLL - zoom\n"
		"SCROLL + Ctrl - change brushsize\n"
		"drag left mouse - draw pixels\n"
		"draw + SHIFT - draw rect\n"
		"draw + CTRL - draw line\n"
		"X + R_CTRL - clear board\n"
		"C + CTRL - copy selected area\n"
		"V + CTRL - paste copied area\n"
		"X + CTRL - clear selected area\n"
		"\n=== Debug stuff ===\n"
		"L - reload resources (shader/images/...)\n"
		"CTRL + SHIFT + M - toggle debug info\n"
	);
	help_hotkeys_text.setFillColor(sf::Color(255, 255, 255, 255));
}

void HelpMenu::resize() {
	help_bg_rect.setPosition(0, 0);
	help_bg_rect.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

	help_tps_slider_text.setCharacterSize(sim->gui.tps_slider.rect.getSize().y * 0.4);
	help_tps_slider_text.setPosition(sim->gui.tps_text.getPosition().x + sim->gui.tps_text.getGlobalBounds().width + 10,
										sim->gui.tps_slider.rect.getPosition().y + sim->gui.tps_slider.rect.getSize().y * 0.2f);

	help_edit_button_text.setCharacterSize(sim->gui.edit_button.rect.getSize().y * 0.4);
	help_edit_button_text.setPosition(sim->gui.edit_button.rect.getPosition().x + sim->gui.edit_button.rect.getSize().x + 10,
										sim->gui.edit_button.rect.getPosition().y + sim->gui.edit_button.rect.getSize().y * 0.2f);

	help_fill_button_text.setCharacterSize(sim->gui.fill_button.rect.getSize().y * 0.4);
	help_fill_button_text.setPosition(sim->gui.fill_button.rect.getPosition().x + sim->gui.fill_button.rect.getSize().x + 10,
									  sim->gui.fill_button.rect.getPosition().y + sim->gui.fill_button.rect.getSize().y * 0.2f);

	help_reset_button_text.setCharacterSize(sim->gui.reset_button.rect.getSize().y * 0.4);
	help_reset_button_text.setPosition(sim->gui.reset_button.rect.getPosition().x + sim->gui.reset_button.rect.getSize().x + 10,
										sim->gui.reset_button.rect.getPosition().y + sim->gui.reset_button.rect.getSize().y * 0.2f);

	help_grid_button_text.setCharacterSize(sim->gui.grid_button.rect.getSize().y * 0.4);
	help_grid_button_text.setPosition(sim->gui.grid_button.rect.getPosition().x + sim->gui.grid_button.rect.getSize().x + 10,
										sim->gui.grid_button.rect.getPosition().y + sim->gui.grid_button.rect.getSize().y * 0.2f);

	help_details_button_text.setCharacterSize(sim->gui.detail_button.rect.getSize().y * 0.4);
	help_details_button_text.setPosition(sim->gui.detail_button.rect.getPosition().x + sim->gui.detail_button.rect.getSize().x + 10,
										sim->gui.detail_button.rect.getPosition().y + sim->gui.detail_button.rect.getSize().y * 0.2f);

	help_selection_button_text.setCharacterSize(sim->gui.selection_button.rect.getSize().y * 0.4);
	help_selection_button_text.setPosition(sim->gui.selection_button.rect.getPosition().x + sim->gui.selection_button.rect.getSize().x + 10,
										sim->gui.selection_button.rect.getPosition().y + sim->gui.selection_button.rect.getSize().y * 0.2f);

	help_item_button_text.setCharacterSize(sim->gui.item_button.rect.getSize().y * 0.4);
	help_item_button_text.setPosition(sim->gui.item_button.rect.getPosition().x - help_item_button_text.getGlobalBounds().width - 10,
										sim->gui.item_button.rect.getPosition().y + sim->gui.item_button.rect.getSize().y * 0.2f);

	help_hotkeys_text.setCharacterSize(sim->gui.item_button.rect.getSize().y * 0.3);
	help_hotkeys_text.setPosition(SCREEN_WIDTH - help_hotkeys_text.getGlobalBounds().width * 1.1f,
										SCREEN_HEIGHT - help_hotkeys_text.getGlobalBounds().height);

	help_close_text.setCharacterSize(sim->gui.item_button.rect.getSize().y * 0.5);
	help_close_text.setPosition(SCREEN_WIDTH * 0.2f, SCREEN_HEIGHT * 0.7f);
}

void HelpMenu::update() {

}

void HelpMenu::render(sf::RenderTarget &window) {
	window.draw(help_bg_rect);

	window.draw(help_tps_slider_text);
	window.draw(help_edit_button_text);
	window.draw(help_fill_button_text);
	window.draw(help_reset_button_text);
	window.draw(help_grid_button_text);
	window.draw(help_details_button_text);
	window.draw(help_selection_button_text);
	window.draw(help_item_button_text);
	window.draw(help_hotkeys_text);
	window.draw(help_close_text);
}
