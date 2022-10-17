#include "Simulationscreen.h"

Simulationscreen::Simulationscreen() {
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

void Simulationscreen::load_shader() {
	std::cout << "loading shader..." << std::endl;

	//board shader
	if (!board_shader.loadFromFile("res/shader/board_shader.frag", sf::Shader::Fragment)) {
		std::cout << "ERROR: failed to load 'board_shader.frag'!" << std::endl;
	}
	board_shader.setUniform("pixel_color_texture", pixel_color_texture);
	board_shader.setUniform("offset_x", board_offset_x);
	board_shader.setUniform("offset_y", board_offset_y);
	board_shader.setUniform("zoom_factor", zoom_factor);
	board_shader.setUniform("board_data_texture", board_data_texture);
	board_shader.setUniform("board_width", board_width);
	board_shader.setUniform("board_height", board_height);
	board_shader.setUniform("screen_width", SCREEN_WIDTH);
	board_shader.setUniform("screen_height", SCREEN_HEIGHT);
}

void Simulationscreen::init_update_functions() {
	item_count = 16;

	item_list = new uint32_t[item_count];
	item_names = new std::string[item_count];

	update_functions.push_back(&Simulationscreen::update_air);
	item_list[0] = 0x00000000;
	item_names[0] = "Air";

	update_functions.push_back(&Simulationscreen::update_wire);
	item_list[1] = 0x00000001;
	item_names[1] = "Wire";

	update_functions.push_back(&Simulationscreen::update_battery);
	item_list[2] = 0x00000102;
	item_names[2] = "Battery";

	update_functions.push_back(&Simulationscreen::update_in);
	item_list[3] = 0x00000103;
	item_names[3] = "In";

	update_functions.push_back(&Simulationscreen::update_out);
	item_list[4] = 0x00000104;
	item_names[4] = "Out";

	update_functions.push_back(&Simulationscreen::update_not);
	item_list[5] = 0x00000105;
	item_names[5] = "NOT";

	update_functions.push_back(&Simulationscreen::update_or);
	item_list[6] = 0x00000106;
	item_names[6] = "OR";

	update_functions.push_back(&Simulationscreen::update_xor);
	item_list[7] = 0x00000107;
	item_names[7] = "XOR";

	update_functions.push_back(&Simulationscreen::update_nor);
	item_list[8] = 0x00000108;
	item_names[8] = "NOR";

	update_functions.push_back(&Simulationscreen::update_xnor);
	item_list[9] = 0x00000109;
	item_names[9] = "XNOR";

	update_functions.push_back(&Simulationscreen::update_and);
	item_list[10] = 0x0000010A;
	item_names[10] = "AND";

	update_functions.push_back(&Simulationscreen::update_nand);
	item_list[11] = 0x0000010B;
	item_names[11] = "NAND";

	update_functions.push_back(&Simulationscreen::update_button);
	item_list[12] = 0x0000000C;
	item_names[12] = "Button";

	update_functions.push_back(&Simulationscreen::update_switch);
	item_list[13] = 0x0000000D;
	item_names[13] = "Switch";

	update_functions.push_back(&Simulationscreen::update_lamp);
	item_list[14] = 0x0000000E;
	item_names[14] = "Lamp";

	update_functions.push_back(&Simulationscreen::update_repeater);
	item_list[15] = 0x0001010F;//light, repeatervalue, electricity, id
	item_names[15] = "Repeater";
}

void Simulationscreen::init() {
	item_gui_texture_width = 16;

	init_update_functions();

	selected_item = item_list[WIRE];
	simulation_paused = true;
	board_tps = 10;
	show_inventory = false;

	render_texture.create(1, 1);
	render_rect.setPosition(0, 0);
	render_rect.setTexture(&render_texture);

	if (!pixel_color_texture.loadFromFile("res/images/pixel_color_texture.png")) {
		std::cout << "ERROR: failed to load 'pixel_color_texture.png'!" << std::endl;
	}

	create_board(500, 500);

	//load shader
	load_shader();

	//init threads
	update_board_thread = std::thread(&Simulationscreen::th_update_board, this);

	//init GUI
	pause_button.init();
	pause_button.set_texture_inrect(26, 0, 9, 9);
	pause_button.set_hoverover_texture_inrect(26, 9, 9, 9);
	pause_button.set_pressed_texture_inrect(26, 18, 9, 9);
	pause_button.set_function([&]() {
		simulation_paused = !simulation_paused;
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
		});
	update_item_button_texture();

	resize();
}

void Simulationscreen::update_item_button_texture() {
	item_button.set_texture_inrect(240, (selected_item & 0xFF) * item_gui_texture_width, item_gui_texture_width, item_gui_texture_width);
	item_button.set_hoverover_texture_inrect(240, (selected_item & 0xFF) * item_gui_texture_width, item_gui_texture_width, item_gui_texture_width);
	item_button.set_pressed_texture_inrect(240, (selected_item & 0xFF) * item_gui_texture_width, item_gui_texture_width, item_gui_texture_width);
}

void Simulationscreen::resize() {
	board_shader.setUniform("screen_width", SCREEN_WIDTH);
	board_shader.setUniform("screen_height", SCREEN_HEIGHT);

	render_rect.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));

	//GUI
	int x, y, w, h;
	w = gui_scale * SCREEN_WIDTH * 0.03f;
	h = w;
	x = 8;
	y = 8;
	pause_button.set_position(x, y);
	pause_button.set_size(w, h);

	w = gui_scale * SCREEN_WIDTH * 0.03f;
	h = w;
	x = SCREEN_WIDTH - w - 8;
	y = 8;
	item_button.set_position(x, y);
	item_button.set_size(w, h);

	//inventory GUI
	//inventory_gui.resize();
}

void Simulationscreen::on_closing() {
	update_board_thread.join();
}

void Simulationscreen::create_board(unsigned int width, unsigned int height) {
	board_width = width;
	board_height = height;
	board_size = board_width * board_height;

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
	if (i < board_width || i > board_size - board_width)
		return;

	if (update_checklist[i] == 0) {
		update_checklist[i] = 1;
		update_list.push_back(i);
	}
}

bool Simulationscreen::draw_to_board() {
	if (drawinstruction_list.size() == 0)return false;

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

				*(uint32_t*)&this_board[(x + y * board_width) * 4] = instruction_list[instruction_index].data[2];
				add_to_update_list(x + y * board_width);
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
					add_to_update_list(x + y * board_width);
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

		if (simulation_paused) {
			if (!drawn_to_board) {
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
				int wait_time = int(1000.0f / board_tps - timer.get_duration());
				std::this_thread::sleep_for(std::chrono::milliseconds(wait_time));
			}
		}

		if (drawn_to_board || !simulation_paused) {
			board_data_texture.update(this_board);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(int(1000.0f / FPS - (timer.get_time() - start_frame_time))));
	}
}

void Simulationscreen::update_board() {
	uint32_t update_count = update_list.size();
	if (update_count == 0)return;

	memcpy(next_board, this_board, board_size * 4);//copy board

	memcpy(update_list_copy, &update_list[0], update_count * 4);//copy update_list
	update_list.clear();
	memset(update_checklist, 0, board_size);//clear checklist marks

	uint32_t index = 0;
	for (uint32_t i = 0; i < update_count; i++) {
		index = update_list_copy[i];
		if ((this->*update_functions[this_board[index * 4]])(index)) {
			add_to_update_list(index);
			add_to_update_list(index - board_width);
			add_to_update_list(index + board_width);
			add_to_update_list(index - 1);
			add_to_update_list(index + 1);
		}
	}

	memset(update_list_copy, 0, update_count * 4);

	//switch boards
	uint8_t* temp = this_board;
	this_board = next_board;
	next_board = temp;
}

void Simulationscreen::handle_events(sf::Event& ev) {
	///// KEY /////
	//Pressed
	if (ev.type == sf::Event::KeyPressed) {
	}

	//Released
	else if (ev.type == sf::Event::KeyReleased) {
		if (ev.key.code == sf::Keyboard::R) {
			load_shader();
		}
		else if (ev.key.code == sf::Keyboard::Num0) {//center screen
			target_board_offset_x = float(board_width) / 2;
			target_board_offset_y = float(board_height) / 2;
			target_zoom_factor = 1;
		}
		else if (ev.key.code == sf::Keyboard::Space) {//(un-)pause simulation
			pause_button.func();
		}
		else if (ev.key.code == sf::Keyboard::Up) {
			int i = (selected_item & 0xFF) + 1;
			i = i >= item_count ? 0 : i < 0 ? item_count - 1 : i;
			selected_item = item_list[i];
			std::cout << i << std::endl;
		}
		else if (ev.key.code == sf::Keyboard::Down) {
			int i = (selected_item & 0xFF) - 1;
			i = i >= item_count ? 0 : i < 0 ? item_count - 1 : i;
			selected_item = item_list[i];
			std::cout << i << std::endl;
		}
	}

	////Mouse////
	//wheel
	else if (ev.type == sf::Event::MouseWheelMoved) {
		target_zoom_factor += zoom_factor * (ev.mouseWheel.delta) * zoom_speed;
	}

	//Pressed
	else if (ev.type == sf::Event::MouseButtonPressed) {
	}

	//Released
	else if (ev.type == sf::Event::MouseButtonReleased) {
		if (ev.key.code == sf::Mouse::Right) {
			if (Utils::point_vs_rect(board_mouse.x, board_mouse.y, 0, 0, board_width, board_height)) {
				selected_item = *(uint32_t*)&this_board[int(floor(board_mouse.y) * board_width + floor(board_mouse.x)) * 4];
			}
		}
	}

	//Moved
	else if (ev.type == sf::Event::MouseMoved) {
	}
}

void Simulationscreen::update() {
	//update board_mouse
	last_board_mouse = board_mouse;
	board_mouse.x = (window_mouse.x - (float(SCREEN_WIDTH) / 2 - board_offset_x * zoom_factor)) / zoom_factor;
	board_mouse.y = (window_mouse.y - (float(SCREEN_HEIGHT) / 2 - board_offset_y * zoom_factor)) / zoom_factor;

	//update GUI
	pause_button.update(window_mouse.x, window_mouse.y);
	item_button.update(window_mouse.x, window_mouse.y);

	if (show_inventory) {
		//inventory_gui.update();
	}

	//create drawinstruction list
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (Utils::point_vs_rect(board_mouse.x, board_mouse.y, 0, 0, board_width, board_height) && Utils::point_vs_rect(last_board_mouse.x, last_board_mouse.y, 0, 0, board_width, board_height)) {
			std::lock_guard<std::mutex> draw_lock(draw_mutex);
			Drawinstruction instruction;
			instruction.data[0] = RECT;
			instruction.data[1] = 1;
			instruction.data[2] = selected_item;
			instruction.data[3] = floor(last_board_mouse.x);
			instruction.data[4] = floor(last_board_mouse.y);
			instruction.data[5] = floor(board_mouse.x);
			instruction.data[6] = floor(board_mouse.y);
			drawinstruction_list.push_back(instruction);
		}
	}

	//update board_offset
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

	//update shader_data
	board_shader.setUniform("offset_x", board_offset_x);
	board_shader.setUniform("offset_y", board_offset_y);
	board_shader.setUniform("zoom_factor", zoom_factor);
}

void Simulationscreen::render(sf::RenderTarget& window) {
	window.draw(render_rect, &board_shader);

	//GUI
	pause_button.render(window);
	item_button.render(window);

	if (show_inventory) {
		//inventory_gui.render(window);
	}
}