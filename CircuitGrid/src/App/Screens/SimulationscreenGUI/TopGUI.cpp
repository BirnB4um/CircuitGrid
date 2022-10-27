#include "../Simulationscreen.h"

void TopGUI::init() {
	pause_button.init();
	pause_button.set_texture_inrect(26, 0, 9, 9);
	pause_button.set_hoverover_texture_inrect(26, 9, 9, 9);
	pause_button.set_pressed_texture_inrect(26, 18, 9, 9);
	pause_button.set_function([&]() {
		simulation_paused = !simulation_paused;
		one_simulations_step = false;
		if (simulation_paused) {
			pause_button.set_texture_inrect(26, 0, 9, 9);
			pause_button.set_hoverover_texture_inrect(26, 9, 9, 9);
			pause_button.set_pressed_texture_inrect(26, 18, 9, 9);
		}
		else {
			pause_button.set_texture_inrect(35, 0, 9, 9);
			pause_button.set_hoverover_texture_inrect(35, 9, 9, 9);
			pause_button.set_pressed_texture_inrect(35, 18, 9, 9);
		}
		});

	item_button.init();
	item_button.set_function([&]() {
		sim->show_inventory = !sim->show_inventory;
		});
	update_item_button_texture();

	tps_text.setFont(*font);
	tps_text.setFillColor(sf::Color(255, 255, 255, 255));
	tps_text.setOutlineThickness(0);

	tps_slider.init();
	tps_slider.set_nob_texture_inrect(80, 27, 14, 14);
	tps_slider.value = log(board_tps) / (log(1.007) * 1000);
	tps_slider.set_function([&]() {
		board_tps = std::pow(1.007, tps_slider.value * 1000);
		if (board_tps > 1000)
			board_tps = 10000000;
		});

	edit_button.init();
	edit_button.set_texture_inrect(44, 0, 18, 18);
	edit_button.set_hoverover_texture_inrect(44, 18, 18, 18);
	edit_button.set_pressed_texture_inrect(44, 36, 18, 18);
	edit_button.set_function([&]() {
		sim->edit_mode = !sim->edit_mode;
		if (sim->edit_mode) {
			edit_button.set_texture_inrect(44, 0, 18, 18);
			edit_button.set_hoverover_texture_inrect(44, 18, 18, 18);
			edit_button.set_pressed_texture_inrect(44, 36, 18, 18);
		}
		else {
			edit_button.set_texture_inrect(62, 0, 18, 18);
			edit_button.set_hoverover_texture_inrect(62, 18, 18, 18);
			edit_button.set_pressed_texture_inrect(62, 36, 18, 18);
		}
		});

	fill_button.init();
	fill_button.set_texture_inrect(80, 0, 9, 9);
	fill_button.set_hoverover_texture_inrect(80, 9, 9, 9);
	fill_button.set_pressed_texture_inrect(80, 18, 9, 9);
	fill_button.set_function([&]() {
		sim->fill_mode = !sim->fill_mode;
		if (sim->fill_mode) {
			fill_button.set_texture_inrect(80, 18, 9, 9);
			fill_button.set_hoverover_texture_inrect(80, 9, 9, 9);
			fill_button.set_pressed_texture_inrect(80, 0, 9, 9);
		}
		else {
			fill_button.set_texture_inrect(80, 0, 9, 9);
			fill_button.set_hoverover_texture_inrect(80, 9, 9, 9);
			fill_button.set_pressed_texture_inrect(80, 18, 9, 9);
		}
		});

	reset_button.init();
	reset_button.set_texture_inrect(89, 0, 9, 9);
	reset_button.set_hoverover_texture_inrect(89, 9, 9, 9);
	reset_button.set_pressed_texture_inrect(89, 18, 9, 9);
	reset_button.set_function([&]() {
		sim->reset_simulation_bool = true;
		});

	grid_button.init();
	grid_button.set_texture_inrect(98, 0, 9, 9);
	grid_button.set_hoverover_texture_inrect(98, 9, 9, 9);
	grid_button.set_pressed_texture_inrect(98, 18, 9, 9);
	grid_button.set_function([&]() {
		sim->draw_grid = !sim->draw_grid;
		sim->board_shader.setUniform("draw_grid", sim->draw_grid);
		if (sim->draw_grid) {
			grid_button.set_texture_inrect(98, 18, 9, 9);
			grid_button.set_hoverover_texture_inrect(98, 9, 9, 9);
			grid_button.set_pressed_texture_inrect(98, 0, 9, 9);
		}
		else {
			grid_button.set_texture_inrect(98, 0, 9, 9);
			grid_button.set_hoverover_texture_inrect(98, 9, 9, 9);
			grid_button.set_pressed_texture_inrect(98, 18, 9, 9);
		}
		});

	detail_button.init();
	detail_button.set_texture_inrect(107, 0, 9, 9);
	detail_button.set_hoverover_texture_inrect(107, 9, 9, 9);
	detail_button.set_pressed_texture_inrect(107, 18, 9, 9);
	detail_button.set_function([&]() {
		sim->draw_details = !sim->draw_details;
		sim->board_shader.setUniform("draw_details", sim->draw_details);
		if (sim->draw_details) {
			detail_button.set_texture_inrect(107, 18, 9, 9);
			detail_button.set_hoverover_texture_inrect(107, 9, 9, 9);
			detail_button.set_pressed_texture_inrect(107, 0, 9, 9);
		}
		else {
			detail_button.set_texture_inrect(107, 0, 9, 9);
			detail_button.set_hoverover_texture_inrect(107, 9, 9, 9);
			detail_button.set_pressed_texture_inrect(107, 18, 9, 9);
		}
		});

	selection_button.init();
	selection_button.set_texture_inrect(116, 0, 9, 9);
	selection_button.set_hoverover_texture_inrect(116, 9, 9, 9);
	selection_button.set_pressed_texture_inrect(116, 18, 9, 9);
	selection_button.set_function([&]() {
		sim->selection_mode = !sim->selection_mode;
		sim->selection_set = false;
		sim->selection_part = 0;
		if (sim->selection_mode) {
			selection_button.set_texture_inrect(116, 18, 9, 9);
			selection_button.set_hoverover_texture_inrect(116, 9, 9, 9);
			selection_button.set_pressed_texture_inrect(116, 0, 9, 9);
		}
		else {
			selection_button.set_texture_inrect(116, 0, 9, 9);
			selection_button.set_hoverover_texture_inrect(116, 9, 9, 9);
			selection_button.set_pressed_texture_inrect(116, 18, 9, 9);
		}
		});
}

void TopGUI::update_item_button_texture() {
	item_button.set_texture_inrect(240, (selected_item & 0xFF) * 16, 16, 16);
	item_button.set_hoverover_texture_inrect(240, (selected_item & 0xFF) * 16, 16, 16);
	item_button.set_pressed_texture_inrect(240, (selected_item & 0xFF) * 16, 16, 16);
}

void TopGUI::resize() {
	int x, y, w, h, stroke_width;

	w = gui_scale * SCREEN_WIDTH * 0.04f;
	h = w;
	x = 8;
	y = 8;
	pause_button.set_position(x, y);
	pause_button.set_size(w, h);

	w = gui_scale * SCREEN_WIDTH * 0.04f;
	h = w;
	x = SCREEN_WIDTH - w - 10;
	y = 10;
	item_button.set_position(x, y);
	item_button.set_size(w, h);

	h = pause_button.rect.getSize().y * 0.8f;
	w = h * 6;
	x = pause_button.rect.getPosition().x + pause_button.rect.getSize().x * 1.5f;
	y = pause_button.rect.getPosition().y + pause_button.rect.getSize().y * 0.1f;
	tps_slider.set_position(x, y);
	tps_slider.set_size(w, h);

	h = tps_slider.rect.getSize().y * 0.6f;
	x = tps_slider.rect.getPosition().x + tps_slider.rect.getSize().x + gui_scale * 10;
	y = tps_slider.rect.getPosition().y + tps_slider.rect.getSize().y * 0.2f;
	tps_text.setCharacterSize(h);
	tps_text.setPosition(x, y);

	w = gui_scale * SCREEN_WIDTH * 0.04f;
	h = w;
	x = pause_button.rect.getPosition().x;
	y = gui_scale * SCREEN_HEIGHT * 0.1f;
	edit_button.set_position(x, y);
	edit_button.set_size(w, h);

	w = gui_scale * SCREEN_WIDTH * 0.04f;
	h = w;
	x = pause_button.rect.getPosition().x;
	y = edit_button.rect.getPosition().y + edit_button.rect.getSize().y * 1.1f * gui_scale;
	fill_button.set_position(x, y);
	fill_button.set_size(w, h);

	w = gui_scale * SCREEN_WIDTH * 0.04f;
	h = w;
	x = pause_button.rect.getPosition().x;
	y = fill_button.rect.getPosition().y + fill_button.rect.getSize().y * 1.1f * gui_scale;
	reset_button.set_position(x, y);
	reset_button.set_size(w, h);

	w = gui_scale * SCREEN_WIDTH * 0.04f;
	h = w;
	x = pause_button.rect.getPosition().x;
	y = reset_button.rect.getPosition().y + reset_button.rect.getSize().y * 1.1f * gui_scale;
	grid_button.set_position(x, y);
	grid_button.set_size(w, h);

	w = gui_scale * SCREEN_WIDTH * 0.04f;
	h = w;
	x = pause_button.rect.getPosition().x;
	y = grid_button.rect.getPosition().y + grid_button.rect.getSize().y * 1.1f * gui_scale;
	detail_button.set_position(x, y);
	detail_button.set_size(w, h);

	w = gui_scale * SCREEN_WIDTH * 0.04f;
	h = w;
	x = pause_button.rect.getPosition().x;
	y = detail_button.rect.getPosition().y + detail_button.rect.getSize().y * 1.1f * gui_scale;
	selection_button.set_position(x, y);
	selection_button.set_size(w, h);
}

void TopGUI::update() {
	if (pause_button.check_over_button(window_mouse.x, window_mouse.y)) {
		sim->mouse_over_gui = true;
	}
	pause_button.update(window_mouse.x, window_mouse.y);

	if (item_button.check_over_button(window_mouse.x, window_mouse.y)) {
		sim->mouse_over_gui = true;
	}
	item_button.update(window_mouse.x, window_mouse.y);

	if (tps_slider.check_over_slider(window_mouse.x, window_mouse.y) || tps_slider.pressed) {
		sim->mouse_over_gui = true;
	}
	tps_slider.update(window_mouse.x, window_mouse.y);

	if (edit_button.check_over_button(window_mouse.x, window_mouse.y)) {
		sim->mouse_over_gui = true;
	}
	edit_button.update(window_mouse.x, window_mouse.y);

	if (fill_button.check_over_button(window_mouse.x, window_mouse.y)) {
		sim->mouse_over_gui = true;
	}
	fill_button.update(window_mouse.x, window_mouse.y);

	if (reset_button.check_over_button(window_mouse.x, window_mouse.y)) {
		sim->mouse_over_gui = true;
	}
	reset_button.update(window_mouse.x, window_mouse.y);

	if (grid_button.check_over_button(window_mouse.x, window_mouse.y)) {
		sim->mouse_over_gui = true;
	}
	grid_button.update(window_mouse.x, window_mouse.y);

	if (detail_button.check_over_button(window_mouse.x, window_mouse.y)) {
		sim->mouse_over_gui = true;
	}
	detail_button.update(window_mouse.x, window_mouse.y);

	if (selection_button.check_over_button(window_mouse.x, window_mouse.y)) {
		sim->mouse_over_gui = true;
	}
	selection_button.update(window_mouse.x, window_mouse.y);

	tps_text.setString("TPS:" + (board_tps == 10000000 ? "max" : std::to_string(int(board_tps))));
}

void TopGUI::render(sf::RenderTarget &window) {
	pause_button.render(window);
	item_button.render(window);
	tps_slider.render(window);
	edit_button.render(window);
	fill_button.render(window);
	reset_button.render(window);
	grid_button.render(window);
	detail_button.render(window);
	selection_button.render(window);
	window.draw(tps_text);
}


