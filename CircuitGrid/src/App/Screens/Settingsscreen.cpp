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


	save_board_button.init();
	save_board_button.set_texture_inrect(200, 0, 20,9);
	save_board_button.set_hoverover_texture_inrect(200, 9, 20,9);
	save_board_button.set_pressed_texture_inrect(200, 18, 20,9);
	save_board_button.set_function([&]() {
		save_board();
		});

	load_board_button.init();
	load_board_button.set_texture_inrect(178, 0, 22,9);
	load_board_button.set_hoverover_texture_inrect(178, 9, 22,9);
	load_board_button.set_pressed_texture_inrect(178, 18, 22,9);
	load_board_button.set_function([&]() {
		load_board();
		screen_id = SIMULATION;
		});


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


	h = SCREEN_HEIGHT * 0.06f;
	w = h * (float(back_button.texture_width) / back_button.texture_height);
	x = SCREEN_WIDTH - w;
	y = SCREEN_HEIGHT - h;
	back_button.set_position(x, y);
	back_button.set_size(w, h);

	h = SCREEN_HEIGHT * 0.08f;
	w = h * (float(save_board_button.texture_width) / save_board_button.texture_height);
	x = middle_line.getPosition().x + (SCREEN_WIDTH - middle_line.getPosition().x) * 0.5f - w - 5;
	y = board_text.getPosition().y + board_text.getCharacterSize() * 2.0f;
	save_board_button.set_position(x, y);
	save_board_button.set_size(w, h);

	h = SCREEN_HEIGHT * 0.08f;
	w = h * (float(load_board_button.texture_width) / load_board_button.texture_height);
	x = middle_line.getPosition().x + (SCREEN_WIDTH - middle_line.getPosition().x) * 0.5f + 5;
	y = board_text.getPosition().y + board_text.getCharacterSize() * 2.0f;
	load_board_button.set_position(x, y);
	load_board_button.set_size(w, h);

}

void Settingsscreen::on_closing() {

}

void Settingsscreen::save_board() {
	/*
	1 byte: VERSION
	4 byte: WIDTH
	4 byte: HEIGHT
	x byte: DATA
	*/

	std::string file_name = io_data.choose_save_file(1);


	uint8_t version = 0x01;
	uint32_t width = board_width;
	uint32_t height = board_height;

	uint64_t size = 9 + board_size * 4;
	uint8_t* out_data = new uint8_t[size];

	memcpy(&out_data[0], &version, 1);
	memcpy(&out_data[1], &width, 4);
	memcpy(&out_data[5], &height, 4);
	memcpy(&out_data[9], this_board, board_size * 4);

	io_data.save_to_file(file_name, (char*)out_data, size, false);

	delete[] out_data;
}

void Settingsscreen::load_board() {
	std::string file_name = io_data.choose_open_file(1);

	std::vector<char> data;
	data.reserve(1000000);
	io_data.read_from_file(file_name, data);

	if (file_name == "") {
		std::cout << "ERROR: couldnt read board_data!" << std::endl;
		return;
	}
	if (data.size() == 0) {
		std::cout << "ERROR: couldnt read board_data!" << std::endl;
		return;
	}
	if ((uint8_t)data[0] != board_version) {
		std::cout << "ERROR: board version is too old!" << std::endl;
		return;
	}

	uint32_t width = *(uint32_t*)&data[1];
	uint32_t height = *(uint32_t*)&data[5];

	board_width = width;
	board_height = height;
	board_size = board_width * board_height;

	update_list.clear();
	update_list.shrink_to_fit();
	update_list.reserve(board_size);

	if (update_list_copy != nullptr) {
		delete[] update_list_copy;
	}
	update_list_copy = new uint32_t[board_size];
	memset(update_list_copy, 0, board_size * 4);

	if (update_checklist != nullptr) {
		delete[] update_checklist;
	}
	update_checklist = new bool[board_size];
	memset(update_checklist, 0, board_size * sizeof(bool));

	target_board_offset_x = float(board_width) / 2;
	board_offset_x = target_board_offset_x;
	target_board_offset_y = float(board_height) / 2;
	board_offset_y = target_board_offset_y;
	target_zoom_factor = 1;
	zoom_factor = 0.01f;

	if (this_board != nullptr) {
		delete[] this_board;
	}
	this_board = new uint8_t[board_size * 4];
	memset(this_board, 0, board_size * 4);

	if (next_board != nullptr) {
		delete[] next_board;
	}
	next_board = new uint8_t[board_size * 4];
	memset(next_board, 0, board_size * 4);

	//set data
	memcpy(&this_board[0], &data[9], board_size * 4);
	memcpy(&next_board[0], &data[9], board_size * 4);

	board_data_texture->create(board_width, board_height);
	board_data_texture->update(this_board);

	board_shader->setUniform("board_data_texture", *board_data_texture);
	board_shader->setUniform("board_width", board_width);
	board_shader->setUniform("board_height", board_height);

	//go back to simulation
	screen_id = SIMULATION;
}

void Settingsscreen::handle_events(sf::Event& ev) {
	if (ev.type == sf::Event::KeyReleased) {
		if (ev.key.code == sf::Keyboard::L) {
		}
	}
}

void Settingsscreen::update() {
	back_button.update(window_mouse.x, window_mouse.y);

	save_board_button.update(window_mouse.x, window_mouse.y);
	load_board_button.update(window_mouse.x, window_mouse.y);
}

void Settingsscreen::render(sf::RenderTarget& window) {

	window.draw(middle_line);

	back_button.render(window);

	window.draw(board_text);
	save_board_button.render(window);
	load_board_button.render(window);
}