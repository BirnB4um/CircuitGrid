#include "Simulationscreen.h"

Simulationscreen::Simulationscreen() {
	inventory.sim = this;
	helpmenu.sim = this;
	gui.sim = this;
}

Simulationscreen::~Simulationscreen() {
	if (this_board != nullptr) {
		delete[] this_board;
		this_board = nullptr;
	}
	if (next_board != nullptr) {
		delete[] next_board;
		next_board = nullptr;
	}
}

void Simulationscreen::load_resources() {
	std::cout << "== Loading resources ==" << std::endl;

	//load fonts
	std::cout << "load fonts..." << std::endl;

	if (!font->loadFromFile("res/fonts/arial.ttf")) {
		std::cout << "ERROR: couldnt load font 'arial.ttf'" << std::endl;
	}

	//reload texture
	std::cout << "load textures..." << std::endl;

	GUI_Item::gui_texture->loadFromFile("res/images/gui_texture.png");

	if (!pixel_color_texture.loadFromFile("res/images/pixel_color_texture.png")) {
		std::cout << "ERROR: failed to load 'pixel_color_texture.png'!" << std::endl;
	}

	if (!large_pixel_texture.loadFromFile("res/images/large_pixel_texture.png")) {
		std::cout << "ERROR: failed to load 'large_pixel_texture.png'!" << std::endl;
	}



	//board shader
	std::cout << "loading shader..." << std::endl;

	if (!board_shader.loadFromFile("res/shader/board_shader.frag", sf::Shader::Fragment)) {
		std::cout << "ERROR: failed to load 'board_shader.frag'!" << std::endl;
	}
	board_shader.setUniform("pixel_color_texture", pixel_color_texture);
	board_shader.setUniform("large_pixel_texture", large_pixel_texture);
	board_shader.setUniform("offset_x", board_offset_x);
	board_shader.setUniform("offset_y", board_offset_y);
	board_shader.setUniform("zoom_factor", zoom_factor);
	board_shader.setUniform("board_data_texture", board_data_texture);
	board_shader.setUniform("board_width", board_width);
	board_shader.setUniform("board_height", board_height);
	board_shader.setUniform("screen_width", SCREEN_WIDTH);
	board_shader.setUniform("screen_height", SCREEN_HEIGHT);
	board_shader.setUniform("mouse_x", 0.0f);
	board_shader.setUniform("mouse_y", 0.0f);
	board_shader.setUniform("brush_size", 0.0f);
	board_shader.setUniform("draw_grid", draw_grid);
	board_shader.setUniform("draw_details", draw_details);
}

void Simulationscreen::init_update_functions() {
	
	update_functions.push_back(&Simulationscreen::update_air);
	item_list.push_back(0x00000000);
	item_names.push_back("Air");

	update_functions.push_back(&Simulationscreen::update_wire);
	item_list.push_back(0x00000101);
	item_names.push_back("Wire");

	update_functions.push_back(&Simulationscreen::update_out);
	item_list.push_back(0x00000102);
	item_names.push_back("Out");

	update_functions.push_back(&Simulationscreen::update_battery);
	item_list.push_back(0x00000203);
	item_names.push_back("Battery");

	update_functions.push_back(&Simulationscreen::update_repeater);
	item_list.push_back(0x000A0104);
	item_names.push_back("Repeater");

	update_functions.push_back(&Simulationscreen::update_bridge);
	item_list.push_back(0x00000105);
	item_names.push_back("Bridge");

	update_functions.push_back(&Simulationscreen::update_lamp);
	item_list.push_back(0x00000106);
	item_names.push_back("Lamp");

	update_functions.push_back(&Simulationscreen::update_button);
	item_list.push_back(0x00000107);
	item_names.push_back("Button");

	update_functions.push_back(&Simulationscreen::update_switch);
	item_list.push_back(0x00000108);
	item_names.push_back("Switch");

	update_functions.push_back(&Simulationscreen::update_not);
	item_list.push_back(0x00000009);
	item_names.push_back("NOT");

	update_functions.push_back(&Simulationscreen::update_or);
	item_list.push_back(0x0000000A);
	item_names.push_back("OR");

	update_functions.push_back(&Simulationscreen::update_nor);
	item_list.push_back(0x0000000B);
	item_names.push_back("NOR");

	update_functions.push_back(&Simulationscreen::update_xor);
	item_list.push_back(0x0000000C);
	item_names.push_back("XOR");

	update_functions.push_back(&Simulationscreen::update_xnor);
	item_list.push_back(0x0000000D);
	item_names.push_back("XNOR");

	update_functions.push_back(&Simulationscreen::update_and);
	item_list.push_back(0x0000000E);
	item_names.push_back("AND");

	update_functions.push_back(&Simulationscreen::update_nand);
	item_list.push_back(0x0000000F);
	item_names.push_back("NAND");

	item_count = item_names.size();

}

void Simulationscreen::init() {
	brush_size = 1;
	can_drag_with_keyboard = true;
	show_debug_info = false;
	update_time_taken = 0;
	upload_texture_to_gpu_time_taken = 0;
	number_of_pixels_to_update = 0;
	move_speed = 16;
	zoom_factor = 1;
	target_zoom_factor = 1;
	clear_board_bool = false;
	reset_simulation_bool = false;
	dragging_board = false;
	drag_start_x = 0;
	drag_start_y = 0;
	drag_start_offset_x = 0;
	drag_start_offset_y = 0;
	edit_mode = true;
	fill_mode = false;
	draw_details = false;
	show_help_menu = false;
	selection_mode = false;
	selection_start_x = -1;
	selection_start_y = -1;
	selection_end_x = -1;
	selection_end_y = -1;
	selection_set = false;
	selection_part = 0;
	

	//debug stuff
	upload_to_gpu_time_text.setFont(*font);
	upload_to_gpu_time_text.setFillColor(sf::Color(255, 255, 255, 255));
	update_board_time_text.setFont(*font);
	update_board_time_text.setFillColor(sf::Color(255, 255, 255, 255));
	updates_number_text.setFont(*font);
	updates_number_text.setFillColor(sf::Color(255, 255, 255, 255));


	init_update_functions();

	selected_item = item_list[WIRE];
	simulation_paused = true;
	board_tps = 10;
	show_inventory = false;
	one_simulations_step = false;

	start_drawing_rectangle = false;
	drawing_rectangle = false;
	start_drawing_line = false;
	drawing_line = false;
	drawing_start_x = 0;
	drawing_start_y = 0;
	drawing_end_x = 0;
	drawing_end_y = 0;

	mouse_over_gui = false;
	mouse_over_board = false;
	last_mouse_over_board = false;

	selection_rect.setFillColor(sf::Color::Transparent);
	selection_rect.setOutlineColor(sf::Color(255,255,255,255));
	selection_rect.setOutlineThickness(4);

	drawing_rect_shape.setFillColor(sf::Color(255,0,0,0));
	drawing_rect_shape.setOutlineColor(sf::Color(255, 0, 0, 255));
	drawing_rect_shape.setOutlineThickness(4);

	drawing_line_shape.setFillColor(sf::Color(255, 0, 0, 255));

	render_texture.create(1, 1);
	render_rect.setPosition(0, 0);
	render_rect.setTexture(&render_texture);

	create_board(500, 500);

	//load shader
	load_resources();

	//init threads
	update_board_thread = std::thread(&Simulationscreen::th_update_board, this);

	//init help menu
	helpmenu.init();


	//init GUI
	gui.init();

	//init inventory GUI
	inventory.init();


	resize();
}

void Simulationscreen::resize() {
	board_shader.setUniform("screen_width", SCREEN_WIDTH);
	board_shader.setUniform("screen_height", SCREEN_HEIGHT);

	render_rect.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

	//GUI
	int x, y, w, h;
	int stroke_width;
	gui.resize();

	//inventory GUI
	inventory.resize();

	//help menu
	helpmenu.resize();


	//debug info
	upload_to_gpu_time_text.setCharacterSize(SCREEN_HEIGHT * 0.02f);
	upload_to_gpu_time_text.setPosition(gui.edit_button.rect.getPosition().x + gui.edit_button.rect.getSize().x * 1.1f, gui.pause_button.rect.getPosition().y + gui.pause_button.rect.getSize().y * 1.1f);

	update_board_time_text.setCharacterSize(SCREEN_HEIGHT * 0.02f);
	update_board_time_text.setPosition(gui.edit_button.rect.getPosition().x + gui.edit_button.rect.getSize().x * 1.1f, upload_to_gpu_time_text.getPosition().y + upload_to_gpu_time_text.getCharacterSize() * 1.5f);

	updates_number_text.setCharacterSize(SCREEN_HEIGHT * 0.02f);
	updates_number_text.setPosition(gui.edit_button.rect.getPosition().x + gui.edit_button.rect.getSize().x * 1.1f, update_board_time_text.getPosition().y + update_board_time_text.getCharacterSize() * 1.5f);
}

void Simulationscreen::on_closing() {
	update_board_thread.join();
}

void Simulationscreen::create_board(unsigned int width, unsigned int height) {
	board_width = width;
	board_height = height;
	board_size = board_width * board_height;

	selection_start_x = -1;
	selection_start_y = -1;
	selection_end_x = -1;
	selection_end_y = -1;

	update_list.clear();
	update_list.shrink_to_fit();
	update_list.reserve(board_size);

	if (update_list_copy != nullptr) {
		delete[] update_list_copy;
		update_list_copy = nullptr;
	}
	update_list_copy = new uint32_t[board_size];
	memset(update_list_copy, 0, board_size * 4);

	if (update_checklist != nullptr) {
		delete[] update_checklist;
		update_checklist = nullptr;
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
		this_board = nullptr;
	}
	this_board = new uint8_t[board_size * 4];
	memset(this_board, 0, board_size * 4);

	if (next_board != nullptr) {
		delete[] next_board;
		next_board = nullptr;
	}
	next_board = new uint8_t[board_size * 4];
	memset(next_board, 0, board_size * 4);

	board_data_texture.create(board_width, board_height);
	board_data_texture.update(this_board);

	board_shader.setUniform("board_data_texture", board_data_texture);
	board_shader.setUniform("board_width", board_width);
	board_shader.setUniform("board_height", board_height);
}

void Simulationscreen::add_to_update_list(uint32_t i) {
	if (i < board_width || i > board_size - board_width || this_board[i*4] == AIR)
		return;

	if (update_checklist[i] == 0) {
		update_checklist[i] = 1;
		update_list.push_back(i);
	}
}

void Simulationscreen::reset_simulation() {
	update_list.clear();
	memset(&update_checklist[0], 0, board_size * sizeof(bool));
	for (uint32_t i = 0; i < board_size;i++) {
		if (this_board[i * 4] == BATTERY || this_board[i * 4] >= NOT) {
			add_to_update_list(i);
			add_to_update_list(i - 1);
			add_to_update_list(i + 1);
			add_to_update_list(i - board_width);
			add_to_update_list(i + board_width);
		}
		*(uint32_t*)&next_board[i * 4] = item_list[this_board[i*4]];
		*(uint32_t*)&this_board[i * 4] = item_list[this_board[i*4]];
	}
}

void Simulationscreen::clear_board() {
	memset(&this_board[0], 0, board_size * 4);
	memset(&next_board[0], 0, board_size * 4);
	update_list.clear();
	memset(update_checklist, 0, board_size * sizeof(bool));
}

bool Simulationscreen::draw_to_board() {
	if (drawinstruction_list.size() == 0)
		return false;

	//get instructions
	Drawinstruction* instruction_list;
	size_t list_size = 0;
	{
		std::lock_guard<std::mutex> draw_lock(draw_mutex);

		list_size = drawinstruction_list.size();
		instruction_list = new Drawinstruction[list_size];
		memcpy(instruction_list, &drawinstruction_list[0], list_size * 7 * 4);
		drawinstruction_list.clear();
	}

	//draw to board
	for (int instruction_index = 0; instruction_index < list_size; instruction_index++) {
		if (instruction_list[instruction_index].data[0] == POINT) {
			int index = instruction_list[instruction_index].data[5] + instruction_list[instruction_index].data[6] * board_width;
			*(uint32_t*)&this_board[index * 4] = instruction_list[instruction_index].data[2];

			int x = instruction_list[instruction_index].data[5];
			int y = instruction_list[instruction_index].data[6];
			add_to_update_list(x + y * board_width);
			add_to_update_list(x+1 + y * board_width);
			add_to_update_list(x-1 + y * board_width);
			add_to_update_list(x + (y+1) * board_width);
			add_to_update_list(x + (y-1) * board_width);
		}
		else if (instruction_list[instruction_index].data[0] == LINE) {
			uint32_t steps = 0;
			uint32_t start_x = instruction_list[instruction_index].data[3];
			uint32_t start_y = instruction_list[instruction_index].data[4];
			uint32_t end_x = instruction_list[instruction_index].data[5];
			uint32_t end_y = instruction_list[instruction_index].data[6];
			long dx = long(instruction_list[instruction_index].data[5]) - long(instruction_list[instruction_index].data[3]);
			long dy = long(instruction_list[instruction_index].data[6]) - long(instruction_list[instruction_index].data[4]);
			steps = std::abs(dx) > std::abs(dy) ? std::abs(dx) : std::abs(dy);

			double factor;
			uint32_t x, y;
			for (uint32_t i = 0; i < steps + 1; i++) {
				factor = double(i) / steps;
				x = start_x + uint32_t(factor * dx);
				y = start_y + uint32_t(factor * dy);

				for (int _y = y - (brush_size - 1); _y < y + brush_size; _y++) {
					for (int _x = x - (brush_size - 1); _x < x + brush_size; _x++) {

						if (_y >= 0 && _y < board_height && _x >= 0 && _x < board_width) {
							if (sqrt((_x - x) * (_x - x) + (_y - y) * (_y - y)) <= brush_size - 1) {
								*(uint32_t*)&this_board[(_x + _y * board_width) * 4] = instruction_list[instruction_index].data[2];
								add_to_update_list(_x + _y * board_width);
								add_to_update_list(_x + 1 + _y * board_width);
								add_to_update_list(_x - 1 + _y * board_width);
								add_to_update_list(_x + (_y + 1) * board_width);
								add_to_update_list(_x + (_y - 1) * board_width);
							}
						}
					}
				}

				//*(uint32_t*)&this_board[(x + y * board_width) * 4] = instruction_list[instruction_index].data[2];
				//add_to_update_list(x + y * board_width);
				//add_to_update_list(x + 1 + y * board_width);
				//add_to_update_list(x - 1 + y * board_width);
				//add_to_update_list(x + (y + 1) * board_width);
				//add_to_update_list(x + (y - 1) * board_width);
			}
		}
		else if (instruction_list[instruction_index].data[0] == RECT) {
			uint32_t start_x = instruction_list[instruction_index].data[3];
			uint32_t start_y = instruction_list[instruction_index].data[4];
			uint32_t end_x = instruction_list[instruction_index].data[5];
			uint32_t end_y = instruction_list[instruction_index].data[6];

			if (start_x > end_x) {
				uint32_t temp = end_x;
				end_x = start_x;
				start_x = temp;
			}
			if (start_y > end_y) {
				uint32_t temp = end_y;
				end_y = start_y;
				start_y = temp;
			}

			for (uint32_t y = start_y; y <= end_y; y++) {
				for (uint32_t x = start_x; x <= end_x; x++) {
					*(uint32_t*)&this_board[(x + y * board_width) * 4] = instruction_list[instruction_index].data[2];
				}
			}

			for (uint32_t y = (long(start_y)-1) < 0 ? 0 : start_y-1; y <= ((end_y+1)>= board_height ? board_height-1 : end_y+1); y++) {
				for (uint32_t x = (long(start_x)-1) < 0 ? 0 : start_x-1; x <= ((end_x+1) >= board_width ? board_width-1 : end_x+1); x++) {
					add_to_update_list(x + y * board_width);
				}
			}
		}
		else if (instruction_list[instruction_index].data[0] == FILL) {
			uint32_t start_x = instruction_list[instruction_index].data[5];
			uint32_t start_y = instruction_list[instruction_index].data[6];

			uint8_t item_to_override = this_board[(start_y * board_width + start_x) * 4];
			if (item_to_override == (selected_item & 0xFF))
				continue;

			std::vector<uint32_t> test_list;
			test_list.reserve(4 * 1000);
			test_list.push_back(start_y * board_width + start_x);

			uint32_t next_i;
			while (test_list.size() > 0) {
				next_i = test_list[test_list.size() - 1];
				test_list.pop_back();
				if (this_board[next_i * 4] == item_to_override) {
					memcpy(&this_board[next_i * 4], &instruction_list[instruction_index].data[2], 4);
					
					if(next_i > 0)
						test_list.push_back(next_i - 1 );
					if(next_i < board_size-1)
						test_list.push_back(next_i + 1 );
					if (next_i < board_size - board_width)
						test_list.push_back(next_i + board_width );
					if (next_i >= board_width)
						test_list.push_back(next_i - board_width );
				}
			}

		}
	}

	delete[] instruction_list;
	return true;
}

void Simulationscreen::th_update_board() {
	Timer timer;
	bool drawn_to_board = false;

	while (true) {
		if (closing)break;

		long long start_frame_time = timer.get_time();
		//draw to texture
		drawn_to_board = draw_to_board();

		if (clear_board_bool) {
			clear_board_bool = false;
			clear_board();
			drawn_to_board = true;
		}
		if (reset_simulation_bool) {
			reset_simulation_bool = false;
			reset_simulation();
			drawn_to_board = true;
		}

		if (simulation_paused) {
			if (one_simulations_step) {
				one_simulations_step = false;

				update_board();

				drawn_to_board = true;
			}else if (!drawn_to_board) {
				std::this_thread::sleep_for(std::chrono::milliseconds(100));//wait with 10 tps
				continue;
			}
		}
		else {
			while (timer.get_time() - start_frame_time < 1000.0f / FPS)
			{
				timer.start();
				update_board();
				timer.stop();
				update_time_taken = timer.get_duration();
				int wait_time = int(1000.0f / board_tps - update_time_taken);
				std::this_thread::sleep_for(std::chrono::milliseconds(wait_time));
			}
			drawn_to_board = true;
		}

		if (drawn_to_board || !simulation_paused) {
			timer.start();
			board_data_texture.update(this_board);
			timer.stop();
			upload_texture_to_gpu_time_taken = timer.get_duration();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(int(1000.0f / FPS - (timer.get_time() - start_frame_time))));
	}
}

void Simulationscreen::update_board() {
	number_of_pixels_to_update = update_list.size();
	if (number_of_pixels_to_update == 0)return;

	memcpy(next_board, this_board, board_size * 4);//copy board

	memset(update_list_copy, 0, number_of_pixels_to_update * 4);
	memcpy(update_list_copy, &update_list[0], number_of_pixels_to_update * 4);//copy update_list
	update_list.clear();
	memset(update_checklist, 0, board_size * sizeof(bool));//clear checklist marks

	uint32_t index = 0;
	for (uint32_t i = 0; i < number_of_pixels_to_update; i++) {
		index = update_list_copy[i];
		if ((this->*update_functions[this_board[index * 4]])(index)) {
			add_to_update_list(index);
			add_to_update_list(index - board_width);
			add_to_update_list(index + board_width);
			add_to_update_list(index - 1);
			add_to_update_list(index + 1);
		}
	}


	//switch boards
	uint8_t* temp = this_board;
	this_board = next_board;
	next_board = temp;
}

void Simulationscreen::handle_events(sf::Event& ev) {

	if (show_help_menu) {//toggle help_mode
		if (ev.type == sf::Event::KeyReleased && ev.key.code == sf::Keyboard::H) {
			show_help_menu = !show_help_menu;
		}
		return;
	}

	///// KEY /////
	//Pressed
	if (ev.type == sf::Event::KeyPressed) {
	}

	//Released
	else if (ev.type == sf::Event::KeyReleased) {
		if (ev.key.code == sf::Keyboard::L) {//load resources
			load_resources();
		}
		else if (ev.key.code == sf::Keyboard::Num0) {//center screen
			target_board_offset_x = float(board_width) / 2;
			target_board_offset_y = float(board_height) / 2;
			target_zoom_factor = 1;
		}
		else if (ev.key.code == sf::Keyboard::M && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {//(un-)pause simulation
			show_debug_info = !show_debug_info;
		}
		else if (ev.key.code == sf::Keyboard::Space) {//(un-)pause simulation
			gui.pause_button.func();
		}
		else if (ev.key.code == sf::Keyboard::H) {//toggle help_mode
			show_help_menu = !show_help_menu;
			if (!simulation_paused)
				gui.pause_button.func();
		}
		else if (ev.key.code == sf::Keyboard::F) {//toggle fill_mode
			gui.fill_button.func();
		}
		else if (ev.key.code == sf::Keyboard::G) {//toggle grid
			gui.grid_button.func();
		}
		else if (ev.key.code == sf::Keyboard::Y) {//toggle details
			gui.detail_button.func();
		}
		else if (ev.key.code == sf::Keyboard::Z) {//toggle selectionmode
			gui.selection_button.func();
		}
		else if (ev.key.code == sf::Keyboard::X && sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) {//clear board
			clear_board_bool = true;
		}
		else if (ev.key.code == sf::Keyboard::B) {//toggle edit mode
			gui.edit_button.func();
		}
		else if (ev.key.code == sf::Keyboard::R) {//reset simulation
			reset_simulation_bool = true;
		}
		else if (ev.key.code == sf::Keyboard::E) {//open/close inventory
			gui.item_button.func();
		}
		else if (ev.key.code == sf::Keyboard::Right) {//one step
			one_simulations_step = true;
		}
		else if (ev.key.code == sf::Keyboard::I) {//print info about pixel
			uint32_t i = (int(board_mouse.x) + int(board_mouse.y) * board_width)*4;
			std::cout << "id:" << int(this_board[i]) << ", elec:" << int(this_board[i + 1]) << ", 3rd:" << int(this_board[i + 2]) << ", light:" << int(this_board[i + 3]) << std::endl;
		}
	}

	////Mouse////
	//wheel
	else if (ev.type == sf::Event::MouseWheelMoved) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {//change brushsize
			int new_brush_size = int(brush_size) + ev.mouseWheel.delta * (brush_size * 0.1f < 1.0f ? 1.0f : brush_size*0.1f);
			brush_size = new_brush_size < 1 ? 1 : new_brush_size > board_width * 2 ? board_width * 2 : new_brush_size;
			if (brush_size == 1) {
				board_shader.setUniform("brush_size", 0.0f);
			}
			else {
				board_shader.setUniform("brush_size", float(brush_size));
			}
		}
		else {//zoom
			target_zoom_factor += zoom_factor * (ev.mouseWheel.delta) * zoom_speed;
		}
	}

	//Pressed
	else if (ev.type == sf::Event::MouseButtonPressed) {

		if (ev.key.code == sf::Mouse::Left) {

			//draw/change selection box
			if (selection_mode) {
				if (mouse_over_board && !mouse_over_gui) {
					if (!selection_set) {
						selection_set = true;
						selection_start_x = floor(board_mouse.x);
						selection_start_y = floor(board_mouse.y);
						selection_end_x = floor(board_mouse.x);
						selection_end_y = floor(board_mouse.y);
						selection_part = 4;
					}
					else {
						if (Utils::point_vs_rect(board_mouse.x, board_mouse.y, selection_start_x, selection_start_y,
							selection_end_x - selection_start_x, selection_end_y - selection_start_y)) {//all
							selection_part = 9;
						}
						else if (board_mouse.x <= selection_start_x && board_mouse.y <= selection_start_y) {//top left
							selection_part = 1;
						}
						else if (board_mouse.x >= selection_end_x && board_mouse.y <= selection_start_y) {//top right
							selection_part = 2;
						}
						else if (board_mouse.x <= selection_start_x && board_mouse.y >= selection_end_y) {//bottom left
							selection_part = 3;
						}
						else if (board_mouse.x >= selection_end_x && board_mouse.y >= selection_end_y) {//bottom right
							selection_part = 4;
						}
						else if (board_mouse.y <= selection_start_y) {//top
							selection_part = 5;
						}
						else if (board_mouse.x <= selection_start_x) {//left
							selection_part = 6;
						}
						else if (board_mouse.x >= selection_end_x) {//right
							selection_part = 7;
						}
						else if (board_mouse.y >= selection_start_y) {//bottom
							selection_part = 8;
						}
						std::cout << int(selection_part ) << std::endl;
					}

					selection_mouse_offset_x = floor(board_mouse.x) - selection_start_x;
					selection_mouse_offset_y = floor(board_mouse.y) - selection_start_y;
				}
			}
			//interacte with board
			else if (!edit_mode && mouse_over_board && !mouse_over_gui) {
				std::lock_guard<std::mutex> draw_lock(draw_mutex);

				uint32_t x = floor(board_mouse.x);
				uint32_t y = floor(board_mouse.y);

				if (this_board[(y * board_width + x) * 4] == BUTTON) {
					if (this_board[(y * board_width + x) * 4 + 1] == 1) {
						Drawinstruction instruction;
						instruction.data[0] = POINT;
						instruction.data[1] = brush_size;
						instruction.data[2] = 0x00000200 + BUTTON;
						instruction.data[3] = floor(last_board_mouse.x);
						instruction.data[4] = floor(last_board_mouse.y);
						instruction.data[5] = x;
						instruction.data[6] = y;
						drawinstruction_list.push_back(instruction);
					}
				}
				else if (this_board[(y * board_width + x) * 4] == SWITCH) {
					if (this_board[(y * board_width + x) * 4 + 1] == 1) {
						Drawinstruction instruction;
						instruction.data[0] = POINT;
						instruction.data[1] = brush_size;
						instruction.data[2] = 0x00000200 + SWITCH;
						instruction.data[3] = floor(last_board_mouse.x);
						instruction.data[4] = floor(last_board_mouse.y);
						instruction.data[5] = x;
						instruction.data[6] = y;
						drawinstruction_list.push_back(instruction);
					} 
					else if (this_board[(y * board_width + x) * 4 + 1] == 2) {
						Drawinstruction instruction;
						instruction.data[0] = POINT;
						instruction.data[1] = brush_size;
						instruction.data[2] = 0x00000000 + SWITCH;
						instruction.data[3] = floor(last_board_mouse.x);
						instruction.data[4] = floor(last_board_mouse.y);
						instruction.data[5] = x;
						instruction.data[6] = y;
						drawinstruction_list.push_back(instruction);
					}
				}


			}

			//start drawing rectangle
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
				start_drawing_rectangle = true;
			}
			//start drawing line
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
				start_drawing_line = true;
			}

			gui.tps_slider.press(window_mouse.x, window_mouse.y);
		}

		//start dragging board
		if (!mouse_over_gui && ev.key.code == sf::Mouse::Middle) {
			dragging_board = true;
			drag_start_x = window_mouse.x;
			drag_start_y = window_mouse.y;
			drag_start_offset_x = board_offset_x;
			drag_start_offset_y = board_offset_y;
		}
	}

	//Released
	else if (ev.type == sf::Event::MouseButtonReleased) {
		if (ev.key.code == sf::Mouse::Right) {
			if (Utils::point_vs_rect(board_mouse.x, board_mouse.y, 0, 0, board_width, board_height)) {
				selected_item = *(uint32_t*)&this_board[int(floor(board_mouse.y) * board_width + floor(board_mouse.x)) * 4];
				gui.update_item_button_texture();
			}
		}

		//start dragging board
		if (ev.key.code == sf::Mouse::Middle) {
			dragging_board = false;
		}
	}

	//Moved
	else if (ev.type == sf::Event::MouseMoved) {
	}
}

void Simulationscreen::update() {
	
	//help menu
	if (show_help_menu) {
		show_inventory = false;
		return;
	}

	//update board_mouse
	last_board_mouse = board_mouse;
	board_mouse.x = (window_mouse.x - (float(SCREEN_WIDTH) / 2 - board_offset_x * zoom_factor)) / zoom_factor;
	board_mouse.y = (window_mouse.y - (float(SCREEN_HEIGHT) / 2 - board_offset_y * zoom_factor)) / zoom_factor;
	board_shader.setUniform("mouse_x", board_mouse.x);
	board_shader.setUniform("mouse_y", board_mouse.y);
	mouse_over_gui = false;
	mouse_over_board = Utils::point_vs_rect(board_mouse.x, board_mouse.y, 0, 0, board_width, board_height);
	last_mouse_over_board = Utils::point_vs_rect(last_board_mouse.x, last_board_mouse.y, 0, 0, board_width, board_height);

	//update GUI
	gui.update();

	if (show_inventory) {
		inventory.update();
	}

	//update board_offset
	if (can_drag_with_keyboard) {
		float speed = move_speed / zoom_factor;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			target_board_offset_y -= speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			target_board_offset_y += speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			target_board_offset_x -= speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			target_board_offset_x += speed;
		}
	}

	if (dragging_board) {
		target_board_offset_x = drag_start_offset_x + (drag_start_x - window_mouse.x) / zoom_factor;
		target_board_offset_y = drag_start_offset_y + (drag_start_y - window_mouse.y) / zoom_factor;
	}

	target_board_offset_x = target_board_offset_x < 0 ? 0 : target_board_offset_x > board_width ? board_width : target_board_offset_x;
	target_board_offset_y = target_board_offset_y < 0 ? 0 : target_board_offset_y > board_height ? board_height : target_board_offset_y;
	if (std::abs(target_board_offset_x - board_offset_x) < 0.01f) {
		board_offset_x = target_board_offset_x;
	}
	else {
		board_offset_x += (target_board_offset_x - board_offset_x) * 0.5f;
	}
	if (std::abs(target_board_offset_y - board_offset_y) < 0.01f) {
		board_offset_y = target_board_offset_y;
	}
	else {
		board_offset_y += (target_board_offset_y - board_offset_y) * 0.5f;
	}

	//update zoom factor
	target_zoom_factor = target_zoom_factor < 1 ? 1 : target_zoom_factor > 500 ? 500 : target_zoom_factor;
	if (std::abs(target_zoom_factor - zoom_factor) < 0.01f) {
		zoom_factor = target_zoom_factor;
	}
	else {
		zoom_factor += (target_zoom_factor - zoom_factor) * 0.2f;
	}

	//selectionmode
	if (selection_mode) {
		start_drawing_rectangle = false;
		start_drawing_line = false;


		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (selection_part == 9) {//all
				selection_end_x = floor(board_mouse.x) - selection_mouse_offset_x + (selection_end_x - selection_start_x);
				selection_end_y = floor(board_mouse.y) - selection_mouse_offset_y + (selection_end_y - selection_start_y);
				selection_start_x = floor(board_mouse.x) - selection_mouse_offset_x;
				selection_start_y = floor(board_mouse.y) - selection_mouse_offset_y;
			}
			else if (selection_part == 1) {//top left
				selection_start_x = floor(board_mouse.x);
				selection_start_y = floor(board_mouse.y);
			}
			else if (selection_part == 2) {//top right
				selection_end_x = floor(board_mouse.x);
				selection_start_y = floor(board_mouse.y);
			}
			else if (selection_part == 3) {//bottom left
				selection_start_x = floor(board_mouse.x);
				selection_end_y = floor(board_mouse.y);
			}
			else if (selection_part == 4) {//bottom reight
				selection_end_x = floor(board_mouse.x);
				selection_end_y = floor(board_mouse.y);
			}
			else if (selection_part == 5) {//top
				selection_start_y = floor(board_mouse.y);
			}
			else if (selection_part == 6) {//left
				selection_start_x = floor(board_mouse.x);
			}
			else if (selection_part == 7) {//right
				selection_end_x = floor(board_mouse.x);
			}
			else if (selection_part == 8) {//bottom
				selection_end_y = floor(board_mouse.y);
			}
		}

		selection_start_x = selection_start_x < 0 ? 0 : selection_start_x > board_width - 1 ? board_width - 1 : selection_start_x;
		selection_end_x = selection_end_x < 0 ? 0 : selection_end_x > board_width - 1 ? board_width - 1 : selection_end_x;
		selection_start_y = selection_start_y < 0 ? 0 : selection_start_y > board_height - 1 ? board_height - 1 : selection_start_y;
		selection_end_y = selection_end_y < 0 ? 0 : selection_end_y > board_height - 1 ? board_height - 1 : selection_end_y;
		
		//switch if not in order
		if (selection_end_x < selection_start_x) {
			long temp = selection_start_x;
			selection_start_x = selection_end_x;
			selection_end_x = temp;
		}
		if (selection_end_y < selection_start_y) {
			long temp = selection_start_y;
			selection_start_y = selection_end_y;
			selection_end_y = temp;
		}

		//update drawing_rectangle_shape
		selection_rect.setPosition((selection_start_x * zoom_factor + (float(SCREEN_WIDTH) / 2 - board_offset_x * zoom_factor)),
									(selection_start_y * zoom_factor + (float(SCREEN_HEIGHT) / 2 - board_offset_y * zoom_factor)));
		selection_rect.setSize(sf::Vector2f((selection_end_x + 1 - selection_start_x) * zoom_factor, (selection_end_y + 1 - selection_start_y) * zoom_factor));

	}
	else {
		//drawing
		if (!mouse_over_gui) {

			if (edit_mode) {

				if (start_drawing_line) {
					drawing_line = true;
					start_drawing_line = false;
					drawing_start_x = floor(board_mouse.x);
					drawing_start_y = floor(board_mouse.y);
					drawing_start_x = drawing_start_x < 0 ? 0 : drawing_start_x > board_width - 1 ? board_width - 1 : drawing_start_x;
					drawing_start_y = drawing_start_y < 0 ? 0 : drawing_start_y > board_height - 1 ? board_height - 1 : drawing_start_y;
				}

				if (start_drawing_rectangle) {
					drawing_rectangle = true;
					start_drawing_rectangle = false;
					drawing_start_x = floor(board_mouse.x);
					drawing_start_y = floor(board_mouse.y);
					drawing_start_x = drawing_start_x < 0 ? 0 : drawing_start_x > board_width - 1 ? board_width - 1 : drawing_start_x;
					drawing_start_y = drawing_start_y < 0 ? 0 : drawing_start_y > board_height - 1 ? board_height - 1 : drawing_start_y;
				}

				//create drawinstruction list
				if (drawing_line) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
							drawing_end_x = floor(board_mouse.x);
							drawing_end_y = floor(board_mouse.y);
							drawing_end_x = drawing_end_x < 0 ? 0 : drawing_end_x > board_width - 1 ? board_width - 1 : drawing_end_x;
							drawing_end_y = drawing_end_y < 0 ? 0 : drawing_end_y > board_height - 1 ? board_height - 1 : drawing_end_y;

							float x1 = (drawing_start_x + 0.5f) * zoom_factor + (float(SCREEN_WIDTH) / 2 - board_offset_x * zoom_factor);
							float y1 = (drawing_start_y + 0.5f) * zoom_factor + (float(SCREEN_HEIGHT) / 2 - board_offset_y * zoom_factor);
							float x2 = (drawing_end_x + 0.5f) * zoom_factor + (float(SCREEN_WIDTH) / 2 - board_offset_x * zoom_factor);
							float y2 = (drawing_end_y + 0.5f) * zoom_factor + (float(SCREEN_HEIGHT) / 2 - board_offset_y * zoom_factor);
							drawing_line_shape.setPosition(x1, y1);
							drawing_line_shape.setSize(sf::Vector2f(sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)), 4));
							drawing_line_shape.setRotation(atan2(y2 - y1, x2 - x1) * 180.0f / PI);

						}
						else {
							drawing_line = false;

							Drawinstruction instruction;
							instruction.data[0] = LINE;
							instruction.data[1] = brush_size;
							instruction.data[2] = selected_item;
							instruction.data[3] = drawing_start_x;
							instruction.data[4] = drawing_start_y;
							instruction.data[5] = drawing_end_x;
							instruction.data[6] = drawing_end_y;
							drawinstruction_list.push_back(instruction);
						}
					}
					else {
						drawing_line = false;
					}
				}
				else if (drawing_rectangle) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
							drawing_end_x = floor(board_mouse.x);
							drawing_end_y = floor(board_mouse.y);
							drawing_end_x = drawing_end_x < 0 ? 0 : drawing_end_x > board_width - 1 ? board_width - 1 : drawing_end_x;
							drawing_end_y = drawing_end_y < 0 ? 0 : drawing_end_y > board_height - 1 ? board_height - 1 : drawing_end_y;

							//update drawing_rectangle_shape
							float x1 = drawing_end_x < drawing_start_x ? floor(drawing_end_x) : floor(drawing_start_x);
							float y1 = drawing_end_y < drawing_start_y ? floor(drawing_end_y) : floor(drawing_start_y);
							float x2 = drawing_end_x < drawing_start_x ? floor(drawing_start_x) + 1 : floor(drawing_end_x) + 1;
							float y2 = drawing_end_y < drawing_start_y ? floor(drawing_start_y) + 1 : floor(drawing_end_y) + 1;
							drawing_rect_shape.setPosition((x1 * zoom_factor + (float(SCREEN_WIDTH) / 2 - board_offset_x * zoom_factor)),
								(y1 * zoom_factor + (float(SCREEN_HEIGHT) / 2 - board_offset_y * zoom_factor)));
							drawing_rect_shape.setSize(sf::Vector2f((x2 - x1) * zoom_factor, (y2 - y1) * zoom_factor));

						}
						else {
							drawing_rectangle = false;

							Drawinstruction instruction;
							instruction.data[0] = RECT;
							instruction.data[1] = 1;
							instruction.data[2] = selected_item;
							instruction.data[3] = drawing_start_x;
							instruction.data[4] = drawing_start_y;
							instruction.data[5] = drawing_end_x;
							instruction.data[6] = drawing_end_y;
							drawinstruction_list.push_back(instruction);
						}
					}
					else {
						drawing_rectangle = false;
					}
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					if (mouse_over_board && last_mouse_over_board) {
						std::lock_guard<std::mutex> draw_lock(draw_mutex);
						Drawinstruction instruction;
						instruction.data[0] = fill_mode ? FILL : LINE;
						instruction.data[1] = brush_size;
						instruction.data[2] = selected_item;
						instruction.data[3] = floor(last_board_mouse.x);
						instruction.data[4] = floor(last_board_mouse.y);
						instruction.data[5] = floor(board_mouse.x);
						instruction.data[6] = floor(board_mouse.y);
						drawinstruction_list.push_back(instruction);

						if (fill_mode)
							gui.fill_button.func();
					}
				}
			}
			else {
				start_drawing_line = false;
				start_drawing_rectangle = false;
				drawing_rectangle = false;
				drawing_line = false;
			}
		}
	}

	//update shader_data
	board_shader.setUniform("offset_x", board_offset_x);
	board_shader.setUniform("offset_y", board_offset_y);
	board_shader.setUniform("zoom_factor", zoom_factor);

	//debug stuff
	upload_to_gpu_time_text.setString("upload board to GPU (ms):" + std::to_string(upload_texture_to_gpu_time_taken));
	update_board_time_text.setString("update board (ms):" + std::to_string(update_time_taken) + " (" + std::to_string(1000.0f / update_time_taken) + " tps)");
	updates_number_text.setString("pixels to update:" + std::to_string(update_list.size()));
}

void Simulationscreen::render(sf::RenderTarget& window) {
	window.draw(render_rect, &board_shader);

	//GUI
	gui.render(window);

	if (show_inventory) {
		inventory.render(window);
	}

	if (drawing_rectangle) {
		window.draw(drawing_rect_shape);
	}
	else if (drawing_line) {
		window.draw(drawing_line_shape);
	}

	if (selection_mode && selection_set) {
		window.draw(selection_rect);
	}


	//debug texts
	if (show_debug_info) {
		window.draw(upload_to_gpu_time_text);
		window.draw(update_board_time_text);
		window.draw(updates_number_text);
	}

	//help menu
	if (show_help_menu) {
		helpmenu.render(window);
	}
}