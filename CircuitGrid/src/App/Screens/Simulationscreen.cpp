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

	update_functions.push_back(&Simulationscreen::update_air);
	item_list.push_back(0x00000000);
	item_names.push_back("Air");

	update_functions.push_back(&Simulationscreen::update_wire);
	item_list.push_back(0x00000001);
	item_names.push_back("Wire");

	update_functions.push_back(&Simulationscreen::update_out);
	item_list.push_back(0x00000002);
	item_names.push_back("Out");

	update_functions.push_back(&Simulationscreen::update_battery);
	item_list.push_back(0x0000FF03);
	item_names.push_back("Battery");

	update_functions.push_back(&Simulationscreen::update_amplifier);
	item_list.push_back(0x00000004);
	item_names.push_back("Amplifier");

	update_functions.push_back(&Simulationscreen::update_button);
	item_list.push_back(0x00000005);
	item_names.push_back("Button");

	update_functions.push_back(&Simulationscreen::update_switch);
	item_list.push_back(0x00000006);
	item_names.push_back("Switch");

	update_functions.push_back(&Simulationscreen::update_bridge);
	item_list.push_back(0x00000007);
	item_names.push_back("Bridge");

	update_functions.push_back(&Simulationscreen::update_not);
	item_list.push_back(0x00000008);
	item_names.push_back("NOT");

	update_functions.push_back(&Simulationscreen::update_or);
	item_list.push_back(0x00000009);
	item_names.push_back("OR");

	update_functions.push_back(&Simulationscreen::update_xor);
	item_list.push_back(0x0000000A);
	item_names.push_back("XOR");

	update_functions.push_back(&Simulationscreen::update_nor);
	item_list.push_back(0x0000000B);
	item_names.push_back("NOR");

	update_functions.push_back(&Simulationscreen::update_xnor);
	item_list.push_back(0x0000000C);
	item_names.push_back("XNOR");

	update_functions.push_back(&Simulationscreen::update_and);
	item_list.push_back(0x0000000D);
	item_names.push_back("AND");

	update_functions.push_back(&Simulationscreen::update_nand);
	item_list.push_back(0x0000000E);
	item_names.push_back("NAND");

	update_functions.push_back(&Simulationscreen::update_lamp);
	item_list.push_back(0x0000000F);
	item_names.push_back("Lamp");

}

void Simulationscreen::init() {
	item_gui_texture_width = 16;

	init_update_functions();

	selected_item = item_list[WIRE];
	simulation_paused = true;
	board_tps = 10;
	show_inventory = false;
	one_simulations_step = false;

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
		show_inventory = !show_inventory;
		});
	update_item_button_texture();

	//init inventory GUI
	inventory_bg_rect.setFillColor(sf::Color(10,10,10,255));
	inventory_bg_rect.setOutlineColor(sf::Color(100,100,100,255));

	//texts
	inventory_text.setFont(*font);
	inventory_text.setString("Inventory");
	inventory_text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	inventory_text.setFillColor(sf::Color(255,255,255,255));
	inventory_text.setOutlineThickness(0);

	inv_logic_gates_text.setFont(*font);
	inv_logic_gates_text.setString("Logic Gates");
	inv_logic_gates_text.setStyle(sf::Text::Bold);
	inv_logic_gates_text.setFillColor(sf::Color(255,255,255,255));
	inv_logic_gates_text.setOutlineThickness(0);

	inv_air_text.setFont(*font);
	inv_air_text.setString("Air");
	inv_air_text.setFillColor(sf::Color(255,255,255,255));
	inv_air_text.setOutlineThickness(0);

	inv_wire_text.setFont(*font);
	inv_wire_text.setString("Wire");
	inv_wire_text.setFillColor(sf::Color(255,255,255,255));
	inv_wire_text.setOutlineThickness(0);

	inv_out_text.setFont(*font);
	inv_out_text.setString("Output");
	inv_out_text.setFillColor(sf::Color(255,255,255,255));
	inv_out_text.setOutlineThickness(0);

	inv_battery_text.setFont(*font);
	inv_battery_text.setString("Battery");
	inv_battery_text.setFillColor(sf::Color(255,255,255,255));
	inv_battery_text.setOutlineThickness(0);

	inv_amplifier_text.setFont(*font);
	inv_amplifier_text.setString("Amplifier");
	inv_amplifier_text.setFillColor(sf::Color(255,255,255,255));
	inv_amplifier_text.setOutlineThickness(0);

	inv_bridge_text.setFont(*font);
	inv_bridge_text.setString("Bridge");
	inv_bridge_text.setFillColor(sf::Color(255,255,255,255));
	inv_bridge_text.setOutlineThickness(0);

	inv_not_text.setFont(*font);
	inv_not_text.setString("NOT");
	inv_not_text.setFillColor(sf::Color(255,255,255,255));
	inv_not_text.setOutlineThickness(0);

	inv_or_text.setFont(*font);
	inv_or_text.setString("OR");
	inv_or_text.setFillColor(sf::Color(255,255,255,255));
	inv_or_text.setOutlineThickness(0);

	inv_xor_text.setFont(*font);
	inv_xor_text.setString("XOR");
	inv_xor_text.setFillColor(sf::Color(255,255,255,255));
	inv_xor_text.setOutlineThickness(0);

	inv_nor_text.setFont(*font);
	inv_nor_text.setString("NOR");
	inv_nor_text.setFillColor(sf::Color(255,255,255,255));
	inv_nor_text.setOutlineThickness(0);

	inv_xnor_text.setFont(*font);
	inv_xnor_text.setString("XNOR");
	inv_xnor_text.setFillColor(sf::Color(255,255,255,255));
	inv_xnor_text.setOutlineThickness(0);

	inv_and_text.setFont(*font);
	inv_and_text.setString("AND");
	inv_and_text.setFillColor(sf::Color(255,255,255,255));
	inv_and_text.setOutlineThickness(0);

	inv_nand_text.setFont(*font);
	inv_nand_text.setString("NAND");
	inv_nand_text.setFillColor(sf::Color(255,255,255,255));
	inv_nand_text.setOutlineThickness(0);

	inv_button_text.setFont(*font);
	inv_button_text.setString("Button");
	inv_button_text.setFillColor(sf::Color(255,255,255,255));
	inv_button_text.setOutlineThickness(0);

	inv_switch_text.setFont(*font);
	inv_switch_text.setString("Switch");
	inv_switch_text.setFillColor(sf::Color(255,255,255,255));
	inv_switch_text.setOutlineThickness(0);

	inv_lamp_text.setFont(*font);
	inv_lamp_text.setString("Lamp");
	inv_lamp_text.setFillColor(sf::Color(255,255,255,255));
	inv_lamp_text.setOutlineThickness(0);

	//buttons
	inv_air_button.init();
	inv_air_button.set_texture_inrect(240, 0, 16, 16);
	inv_air_button.set_hoverover_texture_inrect(240, 0, 16, 16);
	inv_air_button.set_pressed_texture_inrect(240, 0, 16, 16);
	inv_air_button.set_function([&]() {
		selected_item = item_list[AIR];
		update_item_button_texture();
		});

	inv_wire_button.init();
	inv_wire_button.set_texture_inrect(240, 16, 16, 16);
	inv_wire_button.set_hoverover_texture_inrect(240, 16, 16, 16);
	inv_wire_button.set_pressed_texture_inrect(240, 16, 16, 16);
	inv_wire_button.set_function([&]() {
		selected_item = item_list[WIRE];
		update_item_button_texture();
		});

	inv_out_button.init();
	inv_out_button.set_texture_inrect(240, 32, 16, 16);
	inv_out_button.set_hoverover_texture_inrect(240, 32, 16, 16);
	inv_out_button.set_pressed_texture_inrect(240, 32, 16, 16);
	inv_out_button.set_function([&]() {
		selected_item = item_list[OUT];
		update_item_button_texture();
		});

	inv_battery_button.init();
	inv_battery_button.set_texture_inrect(240, 48, 16, 16);
	inv_battery_button.set_hoverover_texture_inrect(240, 48, 16, 16);
	inv_battery_button.set_pressed_texture_inrect(240, 48, 16, 16);
	inv_battery_button.set_function([&]() {
		selected_item = item_list[BATTERY];
		update_item_button_texture();
		});

	inv_amplifier_button.init();
	inv_amplifier_button.set_texture_inrect(240, 64, 16, 16);
	inv_amplifier_button.set_hoverover_texture_inrect(240, 64, 16, 16);
	inv_amplifier_button.set_pressed_texture_inrect(240, 64, 16, 16);
	inv_amplifier_button.set_function([&]() {
		selected_item = item_list[AMPLIFIER];
		update_item_button_texture();
		});

	inv_bridge_button.init();
	inv_bridge_button.set_texture_inrect(240, 80, 16, 16);
	inv_bridge_button.set_hoverover_texture_inrect(240, 80, 16, 16);
	inv_bridge_button.set_pressed_texture_inrect(240, 80, 16, 16);
	inv_bridge_button.set_function([&]() {
		selected_item = item_list[BRIDGE];
		update_item_button_texture();
		});

	inv_not_button.init();
	inv_not_button.set_texture_inrect(240, 96, 16, 16);
	inv_not_button.set_hoverover_texture_inrect(240, 96, 16, 16);
	inv_not_button.set_pressed_texture_inrect(240, 96, 16, 16);
	inv_not_button.set_function([&]() {
		selected_item = item_list[NOT];
		update_item_button_texture();
		});

	inv_or_button.init();
	inv_or_button.set_texture_inrect(240, 112, 16, 16);
	inv_or_button.set_hoverover_texture_inrect(240, 112, 16, 16);
	inv_or_button.set_pressed_texture_inrect(240, 112, 16, 16);
	inv_or_button.set_function([&]() {
		selected_item = item_list[OR];
		update_item_button_texture();
		});

	inv_xor_button.init();
	inv_xor_button.set_texture_inrect(240, 128, 16, 16);
	inv_xor_button.set_hoverover_texture_inrect(240, 128, 16, 16);
	inv_xor_button.set_pressed_texture_inrect(240, 128, 16, 16);
	inv_xor_button.set_function([&]() {
		selected_item = item_list[XOR];
		update_item_button_texture();
		});

	inv_nor_button.init();
	inv_nor_button.set_texture_inrect(240, 144, 16, 16);
	inv_nor_button.set_hoverover_texture_inrect(240, 144, 16, 16);
	inv_nor_button.set_pressed_texture_inrect(240, 144, 16, 16);
	inv_nor_button.set_function([&]() {
		selected_item = item_list[NOR];
		update_item_button_texture();
		});

	inv_xnor_button.init();
	inv_xnor_button.set_texture_inrect(240, 160, 16, 16);
	inv_xnor_button.set_hoverover_texture_inrect(240, 160, 16, 16);
	inv_xnor_button.set_pressed_texture_inrect(240, 160, 16, 16);
	inv_xnor_button.set_function([&]() {
		selected_item = item_list[XNOR];
		update_item_button_texture();
		});

	inv_and_button.init();
	inv_and_button.set_texture_inrect(240, 176, 16, 16);
	inv_and_button.set_hoverover_texture_inrect(240, 176, 16, 16);
	inv_and_button.set_pressed_texture_inrect(240, 176, 16, 16);
	inv_and_button.set_function([&]() {
		selected_item = item_list[AND];
		update_item_button_texture();
		});

	inv_nand_button.init();
	inv_nand_button.set_texture_inrect(240, 192, 16, 16);
	inv_nand_button.set_hoverover_texture_inrect(240, 192, 16, 16);
	inv_nand_button.set_pressed_texture_inrect(240, 192, 16, 16);
	inv_nand_button.set_function([&]() {
		selected_item = item_list[NAND];
		update_item_button_texture();
		});

	inv_button_button.init();
	inv_button_button.set_texture_inrect(240, 208, 16, 16);
	inv_button_button.set_hoverover_texture_inrect(240, 208, 16, 16);
	inv_button_button.set_pressed_texture_inrect(240, 208, 16, 16);
	inv_button_button.set_function([&]() {
		selected_item = item_list[BUTTON];
		update_item_button_texture();
		});

	inv_switch_button.init();
	inv_switch_button.set_texture_inrect(240, 224, 16, 16);
	inv_switch_button.set_hoverover_texture_inrect(240, 224, 16, 16);
	inv_switch_button.set_pressed_texture_inrect(240, 224, 16, 16);
	inv_switch_button.set_function([&]() {
		selected_item = item_list[SWITCH];
		update_item_button_texture();
		});

	inv_lamp_button.init();
	inv_lamp_button.set_texture_inrect(240, 240, 16, 16);
	inv_lamp_button.set_hoverover_texture_inrect(240, 240, 16, 16);
	inv_lamp_button.set_pressed_texture_inrect(240, 240, 16, 16);
	inv_lamp_button.set_function([&]() {
		selected_item = item_list[LAMP];
		update_item_button_texture();
		});


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
	int stroke_width;
	w = gui_scale * SCREEN_WIDTH * 0.03f;
	h = w;
	x = 8;
	y = 8;
	pause_button.set_position(x, y);
	pause_button.set_size(w, h);

	w = gui_scale * SCREEN_WIDTH * 0.03f;
	h = w;
	x = SCREEN_WIDTH - w - 10;
	y = 10;
	item_button.set_position(x, y);
	item_button.set_size(w, h);

	//inventory GUI
	stroke_width = 2;
	y = item_button.rect.getPosition().y + item_button.rect.getSize().y + 10;
	h = SCREEN_HEIGHT - y - stroke_width;
	w = h * 0.3f;
	x = SCREEN_WIDTH - w - stroke_width;
	inventory_bg_rect.setPosition(x, y);
	inventory_bg_rect.setSize(sf::Vector2f(w, h));
	inventory_bg_rect.setOutlineThickness(stroke_width);

	x = inventory_bg_rect.getPosition().x + 15;
	y = inventory_bg_rect.getPosition().y + 10;
	w = 0;
	h = inventory_bg_rect.getSize().y * 0.045f;
	inventory_text.setPosition(x, y);
	inventory_text.setCharacterSize(h);

	//item buttons
	float perc_w = 0.25f;
	float offset_from_top = 0.11f;
	{
		w = inventory_bg_rect.getSize().x * perc_w;
		h = w;
		x = inventory_bg_rect.getPosition().x + inventory_bg_rect.getSize().x * (1 - perc_w * 3) * 0.25f;
		y = inventory_bg_rect.getPosition().y + inventory_bg_rect.getSize().y * offset_from_top;
		inv_air_button.set_position(x, y);
		inv_air_button.set_size(w, h);

		x = inventory_bg_rect.getPosition().x + inventory_bg_rect.getSize().x * ((1 - perc_w * 3) * 0.25f * 2 + perc_w);
		inv_wire_button.set_position(x, y);
		inv_wire_button.set_size(w, h);

		x = inventory_bg_rect.getPosition().x + inventory_bg_rect.getSize().x * ((1 - perc_w * 3) * 0.25f * 3 + perc_w * 2);
		inv_out_button.set_position(x, y);
		inv_out_button.set_size(w, h);

		x = inventory_bg_rect.getPosition().x + inventory_bg_rect.getSize().x * (1 - perc_w * 3) * 0.25f;
		y = inventory_bg_rect.getPosition().y + inventory_bg_rect.getSize().y * offset_from_top + inventory_bg_rect.getSize().x * ((1 - perc_w * 3) * 0.5f + perc_w);
		inv_battery_button.set_position(x, y);
		inv_battery_button.set_size(w, h);

		x = inventory_bg_rect.getPosition().x + inventory_bg_rect.getSize().x * ((1 - perc_w * 3) * 0.25f * 2 + perc_w);
		inv_amplifier_button.set_position(x, y);
		inv_amplifier_button.set_size(w, h);

		x = inventory_bg_rect.getPosition().x + inventory_bg_rect.getSize().x * ((1 - perc_w * 3) * 0.25f * 3 + perc_w * 2);
		inv_bridge_button.set_position(x, y);
		inv_bridge_button.set_size(w, h);

		x = inventory_bg_rect.getPosition().x + inventory_bg_rect.getSize().x * (1 - perc_w * 3) * 0.25f;
		y = inventory_bg_rect.getPosition().y + inventory_bg_rect.getSize().y * offset_from_top + inventory_bg_rect.getSize().x * ((1 - perc_w * 3) * 0.5f + perc_w) * 2;
		inv_button_button.set_position(x, y);
		inv_button_button.set_size(w, h);

		x = inventory_bg_rect.getPosition().x + inventory_bg_rect.getSize().x * ((1 - perc_w * 3) * 0.25f * 2 + perc_w);
		inv_switch_button.set_position(x, y);
		inv_switch_button.set_size(w, h);

		x = inventory_bg_rect.getPosition().x + inventory_bg_rect.getSize().x * ((1 - perc_w * 3) * 0.25f * 3 + perc_w * 2);
		inv_lamp_button.set_position(x, y);
		inv_lamp_button.set_size(w, h);



		x = inventory_bg_rect.getPosition().x + inventory_bg_rect.getSize().x * (1 - perc_w * 3) * 0.25f;
		y = inventory_bg_rect.getPosition().y + inventory_bg_rect.getSize().y * offset_from_top + inventory_bg_rect.getSize().x * ((1 - perc_w * 3) * 0.5f + perc_w) * 4;
		inv_not_button.set_position(x, y);
		inv_not_button.set_size(w, h);

		x = inventory_bg_rect.getPosition().x + inventory_bg_rect.getSize().x * ((1 - perc_w * 3) * 0.25f * 2 + perc_w);
		inv_or_button.set_position(x, y);
		inv_or_button.set_size(w, h);

		x = inventory_bg_rect.getPosition().x + inventory_bg_rect.getSize().x * ((1 - perc_w * 3) * 0.25f * 3 + perc_w * 2);
		inv_nor_button.set_position(x, y);
		inv_nor_button.set_size(w, h);

		x = inventory_bg_rect.getPosition().x + inventory_bg_rect.getSize().x * (1 - perc_w * 3) * 0.25f;
		y = inventory_bg_rect.getPosition().y + inventory_bg_rect.getSize().y * offset_from_top + inventory_bg_rect.getSize().x * ((1 - perc_w * 3) * 0.5f + perc_w) * 5;
		inv_xor_button.set_position(x, y);
		inv_xor_button.set_size(w, h);

		x = inventory_bg_rect.getPosition().x + inventory_bg_rect.getSize().x * ((1 - perc_w * 3) * 0.25f * 2 + perc_w);
		inv_xnor_button.set_position(x, y);
		inv_xnor_button.set_size(w, h);

		x = inventory_bg_rect.getPosition().x + inventory_bg_rect.getSize().x * ((1 - perc_w * 3) * 0.25f * 3 + perc_w * 2);
		inv_and_button.set_position(x, y);
		inv_and_button.set_size(w, h);

		x = inventory_bg_rect.getPosition().x + inventory_bg_rect.getSize().x * (1 - perc_w * 3) * 0.25f;
		y = inventory_bg_rect.getPosition().y + inventory_bg_rect.getSize().y * offset_from_top + inventory_bg_rect.getSize().x * ((1 - perc_w * 3) * 0.5f + perc_w) * 6;
		inv_nand_button.set_position(x, y);
		inv_nand_button.set_size(w, h);
	}

	//logic_gates text
	x = inventory_bg_rect.getPosition().x + inventory_bg_rect.getSize().x * (1 - perc_w * 3) * 0.25f;
	y = inventory_bg_rect.getPosition().y + inventory_bg_rect.getSize().y * offset_from_top + inventory_bg_rect.getSize().x * ((1 - perc_w * 3) * 0.5f + perc_w) * 3.1f;
	h = inventory_bg_rect.getSize().x * 0.13f;
	inv_logic_gates_text.setPosition(x, y);
	inv_logic_gates_text.setCharacterSize(h);
	
	//items texts
	{
		h = inv_air_button.rect.getSize().x * 0.4f;
		x = inv_air_button.rect.getPosition().x;
		y = inv_air_button.rect.getPosition().y - h * 1.3f;
		inv_air_text.setPosition(x, y);
		inv_air_text.setCharacterSize(h);

		h = inv_wire_button.rect.getSize().x * 0.4f;
		x = inv_wire_button.rect.getPosition().x;
		y = inv_wire_button.rect.getPosition().y - h * 1.3f;
		inv_wire_text.setPosition(x, y);
		inv_wire_text.setCharacterSize(h);

		h = inv_out_button.rect.getSize().x * 0.3f;
		x = inv_out_button.rect.getPosition().x;
		y = inv_out_button.rect.getPosition().y - h * 1.3f;
		inv_out_text.setPosition(x, y);
		inv_out_text.setCharacterSize(h);

		h = inv_battery_button.rect.getSize().x * 0.3f;
		x = inv_battery_button.rect.getPosition().x;
		y = inv_battery_button.rect.getPosition().y - h * 1.3f;
		inv_battery_text.setPosition(x, y);
		inv_battery_text.setCharacterSize(h);

		h = inv_amplifier_button.rect.getSize().x * 0.3f;
		x = inv_amplifier_button.rect.getPosition().x;
		y = inv_amplifier_button.rect.getPosition().y - h * 1.3f;
		inv_amplifier_text.setPosition(x, y);
		inv_amplifier_text.setCharacterSize(h);

		h = inv_bridge_button.rect.getSize().x * 0.3f;
		x = inv_bridge_button.rect.getPosition().x;
		y = inv_bridge_button.rect.getPosition().y - h * 1.3f;
		inv_bridge_text.setPosition(x, y);
		inv_bridge_text.setCharacterSize(h);

		h = inv_button_button.rect.getSize().x * 0.35f;
		x = inv_button_button.rect.getPosition().x;
		y = inv_button_button.rect.getPosition().y - h * 1.3f;
		inv_button_text.setPosition(x, y);
		inv_button_text.setCharacterSize(h);

		h = inv_switch_button.rect.getSize().x * 0.35f;
		x = inv_switch_button.rect.getPosition().x;
		y = inv_switch_button.rect.getPosition().y - h * 1.3f;
		inv_switch_text.setPosition(x, y);
		inv_switch_text.setCharacterSize(h);

		h = inv_lamp_button.rect.getSize().x * 0.35f;
		x = inv_lamp_button.rect.getPosition().x;
		y = inv_lamp_button.rect.getPosition().y - h * 1.3f;
		inv_lamp_text.setPosition(x, y);
		inv_lamp_text.setCharacterSize(h);

		h = inv_not_button.rect.getSize().x * 0.4f;
		x = inv_not_button.rect.getPosition().x;
		y = inv_not_button.rect.getPosition().y - h * 1.3f;
		inv_not_text.setPosition(x, y);
		inv_not_text.setCharacterSize(h);

		h = inv_or_button.rect.getSize().x * 0.4f;
		x = inv_or_button.rect.getPosition().x;
		y = inv_or_button.rect.getPosition().y - h * 1.3f;
		inv_or_text.setPosition(x, y);
		inv_or_text.setCharacterSize(h);

		h = inv_nor_button.rect.getSize().x * 0.4f;
		x = inv_nor_button.rect.getPosition().x;
		y = inv_nor_button.rect.getPosition().y - h * 1.3f;
		inv_nor_text.setPosition(x, y);
		inv_nor_text.setCharacterSize(h);

		h = inv_xor_button.rect.getSize().x * 0.4f;
		x = inv_xor_button.rect.getPosition().x;
		y = inv_xor_button.rect.getPosition().y - h * 1.3f;
		inv_xor_text.setPosition(x, y);
		inv_xor_text.setCharacterSize(h);

		h = inv_xnor_button.rect.getSize().x * 0.35f;
		x = inv_xnor_button.rect.getPosition().x;
		y = inv_xnor_button.rect.getPosition().y - h * 1.3f;
		inv_xnor_text.setPosition(x, y);
		inv_xnor_text.setCharacterSize(h);

		h = inv_and_button.rect.getSize().x * 0.4f;
		x = inv_and_button.rect.getPosition().x;
		y = inv_and_button.rect.getPosition().y - h * 1.3f;
		inv_and_text.setPosition(x, y);
		inv_and_text.setCharacterSize(h);

		h = inv_nand_button.rect.getSize().x * 0.35f;
		x = inv_nand_button.rect.getPosition().x;
		y = inv_nand_button.rect.getPosition().y - h * 1.3f;
		inv_nand_text.setPosition(x, y);
		inv_nand_text.setCharacterSize(h);
	}


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
	if (i < board_width || i > board_size - board_width || this_board[i*4]==0)
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

	memset(update_list_copy, 0, update_count * 4);
	memcpy(update_list_copy, &update_list[0], update_count * 4);//copy update_list
	update_list.clear();
	memset(update_checklist, 0, board_size * sizeof(bool));//clear checklist marks

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
		else if (ev.key.code == sf::Keyboard::E) {//open/close inventory
			item_button.func();
		}
		else if (ev.key.code == sf::Keyboard::Right) {//one step
			one_simulations_step = true;
		}
		else if (ev.key.code == sf::Keyboard::I) {//print info about pixel
			uint32_t i = (int(board_mouse.x) + int(board_mouse.y) * board_width)*4;
			std::cout << "id:" << int(this_board[i]) << ", elec:" << int(this_board[i + 1]) << ", 3rd:" << int(this_board[i + 2]) << ", light:" << int(this_board[i + 3]) << std::endl;
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
		inv_air_button.update(window_mouse.x, window_mouse.y);
		inv_wire_button.update(window_mouse.x, window_mouse.y);
		inv_out_button.update(window_mouse.x, window_mouse.y);
		inv_battery_button.update(window_mouse.x, window_mouse.y);
		inv_amplifier_button.update(window_mouse.x, window_mouse.y);
		inv_bridge_button.update(window_mouse.x, window_mouse.y);
		inv_button_button.update(window_mouse.x, window_mouse.y);
		inv_switch_button.update(window_mouse.x, window_mouse.y);
		inv_lamp_button.update(window_mouse.x, window_mouse.y);
		inv_not_button.update(window_mouse.x, window_mouse.y);
		inv_or_button.update(window_mouse.x, window_mouse.y);
		inv_nor_button.update(window_mouse.x, window_mouse.y);
		inv_xor_button.update(window_mouse.x, window_mouse.y);
		inv_xnor_button.update(window_mouse.x, window_mouse.y);
		inv_and_button.update(window_mouse.x, window_mouse.y);
		inv_nand_button.update(window_mouse.x, window_mouse.y);
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
		window.draw(inventory_bg_rect);
		window.draw(inventory_text);

		inv_air_button.render(window);
		window.draw(inv_air_text);

		inv_wire_button.render(window);
		window.draw(inv_wire_text);

		inv_out_button.render(window);
		window.draw(inv_out_text);

		inv_battery_button.render(window);
		window.draw(inv_battery_text);

		inv_amplifier_button.render(window);
		window.draw(inv_amplifier_text);

		inv_bridge_button.render(window);
		window.draw(inv_bridge_text);

		inv_button_button.render(window);
		window.draw(inv_button_text);

		inv_switch_button.render(window);
		window.draw(inv_switch_text);

		inv_lamp_button.render(window);
		window.draw(inv_lamp_text);

		inv_not_button.render(window);
		window.draw(inv_not_text);

		inv_or_button.render(window);
		window.draw(inv_or_text);

		inv_nor_button.render(window);
		window.draw(inv_nor_text);

		inv_xor_button.render(window);
		window.draw(inv_xor_text);

		inv_xnor_button.render(window);
		window.draw(inv_xnor_text);

		inv_and_button.render(window);
		window.draw(inv_and_text);

		inv_nand_button.render(window);
		window.draw(inv_nand_text);

		window.draw(inv_logic_gates_text);
	}
}