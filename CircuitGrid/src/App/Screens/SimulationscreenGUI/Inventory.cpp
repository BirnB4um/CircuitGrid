#include "../Simulationscreen.h"

void Inventory::init() {

	inventory_bg_rect.setFillColor(sf::Color(10, 10, 10, 255));
	inventory_bg_rect.setOutlineColor(sf::Color(100, 100, 100, 255));

	//texts
	inventory_text.setFont(*font);
	inventory_text.setString("Inventory");
	inventory_text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	inventory_text.setFillColor(sf::Color(255, 255, 255, 255));
	inventory_text.setOutlineThickness(0);

	inv_logic_gates_text.setFont(*font);
	inv_logic_gates_text.setString("Logic Gates");
	inv_logic_gates_text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	inv_logic_gates_text.setFillColor(sf::Color(255, 255, 255, 255));
	inv_logic_gates_text.setOutlineThickness(0);

	inv_air_text.setFont(*font);
	inv_air_text.setString("Air");
	inv_air_text.setFillColor(sf::Color(255, 255, 255, 255));
	inv_air_text.setOutlineThickness(0);

	inv_wire_text.setFont(*font);
	inv_wire_text.setString("Wire");
	inv_wire_text.setFillColor(sf::Color(255, 255, 255, 255));
	inv_wire_text.setOutlineThickness(0);

	inv_out_text.setFont(*font);
	inv_out_text.setString("Output");
	inv_out_text.setFillColor(sf::Color(255, 255, 255, 255));
	inv_out_text.setOutlineThickness(0);

	inv_battery_text.setFont(*font);
	inv_battery_text.setString("Battery");
	inv_battery_text.setFillColor(sf::Color(255, 255, 255, 255));
	inv_battery_text.setOutlineThickness(0);

	inv_delay_text.setFont(*font);
	inv_delay_text.setString("Delay");
	inv_delay_text.setFillColor(sf::Color(255, 255, 255, 255));
	inv_delay_text.setOutlineThickness(0);

	inv_bridge_text.setFont(*font);
	inv_bridge_text.setString("Bridge");
	inv_bridge_text.setFillColor(sf::Color(255, 255, 255, 255));
	inv_bridge_text.setOutlineThickness(0);

	inv_lamp_text.setFont(*font);
	inv_lamp_text.setString("Lamp");
	inv_lamp_text.setFillColor(sf::Color(255, 255, 255, 255));
	inv_lamp_text.setOutlineThickness(0);

	inv_button_text.setFont(*font);
	inv_button_text.setString("Button");
	inv_button_text.setFillColor(sf::Color(255, 255, 255, 255));
	inv_button_text.setOutlineThickness(0);

	inv_switch_text.setFont(*font);
	inv_switch_text.setString("Switch");
	inv_switch_text.setFillColor(sf::Color(255, 255, 255, 255));
	inv_switch_text.setOutlineThickness(0);

	inv_not_text.setFont(*font);
	inv_not_text.setString("NOT");
	inv_not_text.setFillColor(sf::Color(255, 255, 255, 255));
	inv_not_text.setOutlineThickness(0);

	inv_or_text.setFont(*font);
	inv_or_text.setString("OR");
	inv_or_text.setFillColor(sf::Color(255, 255, 255, 255));
	inv_or_text.setOutlineThickness(0);

	inv_nor_text.setFont(*font);
	inv_nor_text.setString("NOR");
	inv_nor_text.setFillColor(sf::Color(255, 255, 255, 255));
	inv_nor_text.setOutlineThickness(0);

	inv_xor_text.setFont(*font);
	inv_xor_text.setString("XOR");
	inv_xor_text.setFillColor(sf::Color(255, 255, 255, 255));
	inv_xor_text.setOutlineThickness(0);

	inv_xnor_text.setFont(*font);
	inv_xnor_text.setString("XNOR");
	inv_xnor_text.setFillColor(sf::Color(255, 255, 255, 255));
	inv_xnor_text.setOutlineThickness(0);

	inv_and_text.setFont(*font);
	inv_and_text.setString("AND");
	inv_and_text.setFillColor(sf::Color(255, 255, 255, 255));
	inv_and_text.setOutlineThickness(0);

	inv_nand_text.setFont(*font);
	inv_nand_text.setString("NAND");
	inv_nand_text.setFillColor(sf::Color(255, 255, 255, 255));
	inv_nand_text.setOutlineThickness(0);

	inv_clock_text.setFont(*font);
	inv_clock_text.setString("Clock");
	inv_clock_text.setFillColor(sf::Color(255, 255, 255, 255));
	inv_clock_text.setOutlineThickness(0);


	//buttons
	inv_air_button.init();
	inv_air_button.set_texture_inrect(240, 0, 16, 16);
	inv_air_button.set_hoverover_texture_inrect(240, 0, 16, 16);
	inv_air_button.set_pressed_texture_inrect(240, 0, 16, 16);
	inv_air_button.set_function([&]() {
		selected_item = item_list[AIR];
		sim->gui.update_item_button_texture();
		});

	inv_wire_button.init();
	inv_wire_button.set_texture_inrect(240, 16, 16, 16);
	inv_wire_button.set_hoverover_texture_inrect(240, 16, 16, 16);
	inv_wire_button.set_pressed_texture_inrect(240, 16, 16, 16);
	inv_wire_button.set_function([&]() {
		selected_item = item_list[WIRE];
		sim->gui.update_item_button_texture();
		});

	inv_out_button.init();
	inv_out_button.set_texture_inrect(240, 32, 16, 16);
	inv_out_button.set_hoverover_texture_inrect(240, 32, 16, 16);
	inv_out_button.set_pressed_texture_inrect(240, 32, 16, 16);
	inv_out_button.set_function([&]() {
		selected_item = item_list[OUTPUT];
		sim->gui.update_item_button_texture();
		});

	inv_battery_button.init();
	inv_battery_button.set_texture_inrect(240, 48, 16, 16);
	inv_battery_button.set_hoverover_texture_inrect(240, 48, 16, 16);
	inv_battery_button.set_pressed_texture_inrect(240, 48, 16, 16);
	inv_battery_button.set_function([&]() {
		selected_item = item_list[BATTERY];
		sim->gui.update_item_button_texture();
		});

	inv_delay_button.init();
	inv_delay_button.set_texture_inrect(240, 64, 16, 16);
	inv_delay_button.set_hoverover_texture_inrect(240, 64, 16, 16);
	inv_delay_button.set_pressed_texture_inrect(240, 64, 16, 16);
	inv_delay_button.set_function([&]() {
		selected_item = item_list[DELAY];
		sim->gui.update_item_button_texture();
		});

	inv_bridge_button.init();
	inv_bridge_button.set_texture_inrect(240, 80, 16, 16);
	inv_bridge_button.set_hoverover_texture_inrect(240, 80, 16, 16);
	inv_bridge_button.set_pressed_texture_inrect(240, 80, 16, 16);
	inv_bridge_button.set_function([&]() {
		selected_item = item_list[BRIDGE];
		sim->gui.update_item_button_texture();
		});

	inv_lamp_button.init();
	inv_lamp_button.set_texture_inrect(240, 96, 16, 16);
	inv_lamp_button.set_hoverover_texture_inrect(240, 96, 16, 16);
	inv_lamp_button.set_pressed_texture_inrect(240, 96, 16, 16);
	inv_lamp_button.set_function([&]() {
		selected_item = item_list[LAMP];
		sim->gui.update_item_button_texture();
		});

	inv_button_button.init();
	inv_button_button.set_texture_inrect(240, 112, 16, 16);
	inv_button_button.set_hoverover_texture_inrect(240, 112, 16, 16);
	inv_button_button.set_pressed_texture_inrect(240, 112, 16, 16);
	inv_button_button.set_function([&]() {
		selected_item = item_list[BUTTON];
		sim->gui.update_item_button_texture();
		});

	inv_switch_button.init();
	inv_switch_button.set_texture_inrect(240, 128, 16, 16);
	inv_switch_button.set_hoverover_texture_inrect(240, 128, 16, 16);
	inv_switch_button.set_pressed_texture_inrect(240, 128, 16, 16);
	inv_switch_button.set_function([&]() {
		selected_item = item_list[SWITCH];
		sim->gui.update_item_button_texture();
		});


	inv_not_button.init();
	inv_not_button.set_texture_inrect(240, 144, 16, 16);
	inv_not_button.set_hoverover_texture_inrect(240, 144, 16, 16);
	inv_not_button.set_pressed_texture_inrect(240, 144, 16, 16);
	inv_not_button.set_function([&]() {
		selected_item = item_list[NOT];
		sim->gui.update_item_button_texture();
		});

	inv_or_button.init();
	inv_or_button.set_texture_inrect(240, 160, 16, 16);
	inv_or_button.set_hoverover_texture_inrect(240, 160, 16, 16);
	inv_or_button.set_pressed_texture_inrect(240, 160, 16, 16);
	inv_or_button.set_function([&]() {
		selected_item = item_list[OR];
		sim->gui.update_item_button_texture();
		});

	inv_nor_button.init();
	inv_nor_button.set_texture_inrect(240, 176, 16, 16);
	inv_nor_button.set_hoverover_texture_inrect(240, 176, 16, 16);
	inv_nor_button.set_pressed_texture_inrect(240, 176, 16, 16);
	inv_nor_button.set_function([&]() {
		selected_item = item_list[NOR];
		sim->gui.update_item_button_texture();
		});

	inv_xor_button.init();
	inv_xor_button.set_texture_inrect(240, 192, 16, 16);
	inv_xor_button.set_hoverover_texture_inrect(240, 192, 16, 16);
	inv_xor_button.set_pressed_texture_inrect(240, 192, 16, 16);
	inv_xor_button.set_function([&]() {
		selected_item = item_list[XOR];
		sim->gui.update_item_button_texture();
		});

	inv_xnor_button.init();
	inv_xnor_button.set_texture_inrect(240, 208, 16, 16);
	inv_xnor_button.set_hoverover_texture_inrect(240, 208, 16, 16);
	inv_xnor_button.set_pressed_texture_inrect(240, 208, 16, 16);
	inv_xnor_button.set_function([&]() {
		selected_item = item_list[XNOR];
		sim->gui.update_item_button_texture();
		});

	inv_and_button.init();
	inv_and_button.set_texture_inrect(240, 224, 16, 16);
	inv_and_button.set_hoverover_texture_inrect(240, 224, 16, 16);
	inv_and_button.set_pressed_texture_inrect(240, 224, 16, 16);
	inv_and_button.set_function([&]() {
		selected_item = item_list[AND];
		sim->gui.update_item_button_texture();
		});

	inv_nand_button.init();
	inv_nand_button.set_texture_inrect(240, 240, 16, 16);
	inv_nand_button.set_hoverover_texture_inrect(240, 240, 16, 16);
	inv_nand_button.set_pressed_texture_inrect(240, 240, 16, 16);
	inv_nand_button.set_function([&]() {
		selected_item = item_list[NAND];
		sim->gui.update_item_button_texture();
		});

	inv_clock_button.init();
	inv_clock_button.set_texture_inrect(224, 0, 16, 16);
	inv_clock_button.set_hoverover_texture_inrect(224, 0, 16, 16);
	inv_clock_button.set_pressed_texture_inrect(224, 0, 16, 16);
	inv_clock_button.set_function([&]() {
		selected_item = item_list[CLOCK];
		sim->gui.update_item_button_texture();
		});



	//structure gui
	structure_bg_rect.setFillColor(sf::Color(10, 10, 10, 255));
	structure_bg_rect.setOutlineColor(sf::Color(100, 100, 100, 255));

	structure_text.setFont(*font);
	structure_text.setString("Structure");
	structure_text.setFillColor(sf::Color(255, 255, 255, 255));
	structure_text.setOutlineThickness(0);

	save_structure_button.init();
	save_structure_button.set_texture_inrect(200, 0, 20, 9);
	save_structure_button.set_hoverover_texture_inrect(200, 9, 20, 9);
	save_structure_button.set_pressed_texture_inrect(200, 18, 20, 9);
	save_structure_button.set_function([&]() {

		if (sim->selection_mode && sim->selection_set) {
			std::lock_guard<std::mutex> lock(sim->draw_mutex);

			std::string file_name = io_data.choose_save_file(2);
			if (file_name == "") {
				return;
			}

			uint32_t width = sim->selection_end_x - sim->selection_start_x + 1;
			uint32_t height = sim->selection_end_y - sim->selection_start_y + 1;
			uint64_t size = 9 + width * height * 4;
			uint8_t* data = new uint8_t[size];
			data[0] = structure_version;
			*(uint32_t*)&data[1] = width;
			*(uint32_t*)&data[5] = height;

			uint32_t i = 0;
			for (uint32_t y = sim->selection_start_y; y <= sim->selection_end_y; y++) {
				for (uint32_t x = sim->selection_start_x; x <= sim->selection_end_x; x++) {
					memcpy(&data[9 + i * 4], &this_board[(y * board_width + x) * 4], 4);
					i++;
				}
			}

			io_data.save_to_file(file_name, (char*)data, size, false);

			delete[] data;
		}

		});

	load_structure_button.init();
	load_structure_button.set_texture_inrect(178, 0, 22, 9);
	load_structure_button.set_hoverover_texture_inrect(178, 9, 22, 9);
	load_structure_button.set_pressed_texture_inrect(178, 18, 22, 9);
	load_structure_button.set_function([&]() {

		std::string file_name = io_data.choose_open_file(2);

		std::vector<char> data;
		data.reserve(1000000);
		if (!io_data.read_from_file(file_name, data)) {
			std::cout << "ERROR: couldnt read structure_file!" << std::endl;
			return;
		}
		if (*(uint8_t*)&data[0] != structure_version) {
			std::cout << "ERROR: structure_file version too old!" << std::endl;
			return;
		}

		uint64_t size = (*(uint32_t*)&data[1]) * (*(uint32_t*)&data[5]);

		if (sim->loaded_structure != nullptr) {
			delete[] sim->loaded_structure;
			sim->loaded_structure = nullptr;
		}
		sim->loaded_structure = new uint8_t[8 + size * 4];
		memcpy(&(sim->loaded_structure[0]), &data[1], 8 + size * 4);

		sim->paste_structure = sim->loaded_structure;

		});
}

void Inventory::resize() {
	int x, y, w, h;
	int stroke_width;

	stroke_width = 2;
	y = sim->gui.item_button.rect.getPosition().y + sim->gui.item_button.rect.getSize().y + 10;
	h = SCREEN_HEIGHT - y - stroke_width;
	w = h * 0.3f;
	x = SCREEN_WIDTH - w - stroke_width;
	inventory_bg_rect.setPosition(x, y);
	inventory_bg_rect.setSize(sf::Vector2f(w, h));
	inventory_bg_rect.setOutlineThickness(stroke_width);

	x = inventory_bg_rect.getPosition().x + 15;
	y = inventory_bg_rect.getPosition().y + 10;
	w = 0;
	h = inventory_bg_rect.getSize().y * 0.038f;
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
		inv_delay_button.set_position(x, y);
		inv_delay_button.set_size(w, h);

		x = inventory_bg_rect.getPosition().x + inventory_bg_rect.getSize().x * ((1 - perc_w * 3) * 0.25f * 3 + perc_w * 2);
		inv_bridge_button.set_position(x, y);
		inv_bridge_button.set_size(w, h);

		x = inventory_bg_rect.getPosition().x + inventory_bg_rect.getSize().x * (1 - perc_w * 3) * 0.25f;
		y = inventory_bg_rect.getPosition().y + inventory_bg_rect.getSize().y * offset_from_top + inventory_bg_rect.getSize().x * ((1 - perc_w * 3) * 0.5f + perc_w) * 2;
		inv_lamp_button.set_position(x, y);
		inv_lamp_button.set_size(w, h);

		x = inventory_bg_rect.getPosition().x + inventory_bg_rect.getSize().x * ((1 - perc_w * 3) * 0.25f * 2 + perc_w);
		inv_button_button.set_position(x, y);
		inv_button_button.set_size(w, h);

		x = inventory_bg_rect.getPosition().x + inventory_bg_rect.getSize().x * ((1 - perc_w * 3) * 0.25f * 3 + perc_w * 2);
		inv_switch_button.set_position(x, y);
		inv_switch_button.set_size(w, h);



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

		x = inventory_bg_rect.getPosition().x + inventory_bg_rect.getSize().x * ((1 - perc_w * 3) * 0.25f * 2 + perc_w);
		inv_clock_button.set_position(x, y);
		inv_clock_button.set_size(w, h);
	}

	//logic_gates text
	x = inventory_bg_rect.getPosition().x + inventory_bg_rect.getSize().x * (1 - perc_w * 3) * 0.25f;
	y = inventory_bg_rect.getPosition().y + inventory_bg_rect.getSize().y * offset_from_top + inventory_bg_rect.getSize().x * ((1 - perc_w * 3) * 0.5f + perc_w) * 3.2f;
	h = inventory_bg_rect.getSize().x * 0.1f;
	inv_logic_gates_text.setPosition(x, y);
	inv_logic_gates_text.setCharacterSize(h);

	//items texts
	{
		h = inv_air_button.rect.getSize().x * 0.3f;
		x = inv_air_button.rect.getPosition().x;
		y = inv_air_button.rect.getPosition().y - h * 1.3f;
		inv_air_text.setPosition(x, y);
		inv_air_text.setCharacterSize(h);

		h = inv_wire_button.rect.getSize().x * 0.3f;
		x = inv_wire_button.rect.getPosition().x;
		y = inv_wire_button.rect.getPosition().y - h * 1.3f;
		inv_wire_text.setPosition(x, y);
		inv_wire_text.setCharacterSize(h);

		h = inv_out_button.rect.getSize().x * 0.2f;
		x = inv_out_button.rect.getPosition().x;
		y = inv_out_button.rect.getPosition().y - h * 1.3f;
		inv_out_text.setPosition(x, y);
		inv_out_text.setCharacterSize(h);

		h = inv_battery_button.rect.getSize().x * 0.2f;
		x = inv_battery_button.rect.getPosition().x;
		y = inv_battery_button.rect.getPosition().y - h * 1.3f;
		inv_battery_text.setPosition(x, y);
		inv_battery_text.setCharacterSize(h);

		h = inv_delay_button.rect.getSize().x * 0.18f;
		x = inv_delay_button.rect.getPosition().x;
		y = inv_delay_button.rect.getPosition().y - h * 1.3f;
		inv_delay_text.setPosition(x, y);
		inv_delay_text.setCharacterSize(h);

		h = inv_bridge_button.rect.getSize().x * 0.2f;
		x = inv_bridge_button.rect.getPosition().x;
		y = inv_bridge_button.rect.getPosition().y - h * 1.3f;
		inv_bridge_text.setPosition(x, y);
		inv_bridge_text.setCharacterSize(h);

		h = inv_lamp_button.rect.getSize().x * 0.25f;
		x = inv_lamp_button.rect.getPosition().x;
		y = inv_lamp_button.rect.getPosition().y - h * 1.3f;
		inv_lamp_text.setPosition(x, y);
		inv_lamp_text.setCharacterSize(h);

		h = inv_button_button.rect.getSize().x * 0.24f;
		x = inv_button_button.rect.getPosition().x;
		y = inv_button_button.rect.getPosition().y - h * 1.3f;
		inv_button_text.setPosition(x, y);
		inv_button_text.setCharacterSize(h);

		h = inv_switch_button.rect.getSize().x * 0.25f;
		x = inv_switch_button.rect.getPosition().x;
		y = inv_switch_button.rect.getPosition().y - h * 1.3f;
		inv_switch_text.setPosition(x, y);
		inv_switch_text.setCharacterSize(h);

		h = inv_not_button.rect.getSize().x * 0.3f;
		x = inv_not_button.rect.getPosition().x;
		y = inv_not_button.rect.getPosition().y - h * 1.3f;
		inv_not_text.setPosition(x, y);
		inv_not_text.setCharacterSize(h);

		h = inv_or_button.rect.getSize().x * 0.3f;
		x = inv_or_button.rect.getPosition().x;
		y = inv_or_button.rect.getPosition().y - h * 1.3f;
		inv_or_text.setPosition(x, y);
		inv_or_text.setCharacterSize(h);

		h = inv_nor_button.rect.getSize().x * 0.3f;
		x = inv_nor_button.rect.getPosition().x;
		y = inv_nor_button.rect.getPosition().y - h * 1.3f;
		inv_nor_text.setPosition(x, y);
		inv_nor_text.setCharacterSize(h);

		h = inv_xor_button.rect.getSize().x * 0.3f;
		x = inv_xor_button.rect.getPosition().x;
		y = inv_xor_button.rect.getPosition().y - h * 1.3f;
		inv_xor_text.setPosition(x, y);
		inv_xor_text.setCharacterSize(h);

		h = inv_xnor_button.rect.getSize().x * 0.25f;
		x = inv_xnor_button.rect.getPosition().x;
		y = inv_xnor_button.rect.getPosition().y - h * 1.3f;
		inv_xnor_text.setPosition(x, y);
		inv_xnor_text.setCharacterSize(h);

		h = inv_and_button.rect.getSize().x * 0.3f;
		x = inv_and_button.rect.getPosition().x;
		y = inv_and_button.rect.getPosition().y - h * 1.3f;
		inv_and_text.setPosition(x, y);
		inv_and_text.setCharacterSize(h);

		h = inv_nand_button.rect.getSize().x * 0.25f;
		x = inv_nand_button.rect.getPosition().x;
		y = inv_nand_button.rect.getPosition().y - h * 1.3f;
		inv_nand_text.setPosition(x, y);
		inv_nand_text.setCharacterSize(h);

		h = inv_clock_button.rect.getSize().x * 0.25f;
		x = inv_clock_button.rect.getPosition().x;
		y = inv_clock_button.rect.getPosition().y - h * 1.3f;
		inv_clock_text.setPosition(x, y);
		inv_clock_text.setCharacterSize(h);
	}


	//structure gui
	stroke_width = 2;
	h = SCREEN_HEIGHT * 0.12f;
	w = h * 1.5f;
	y = SCREEN_HEIGHT - h - stroke_width;
	x = SCREEN_WIDTH - w - stroke_width * 2 - inventory_bg_rect.getSize().x;
	structure_bg_rect.setPosition(x, y);
	structure_bg_rect.setSize(sf::Vector2f(w, h));
	structure_bg_rect.setOutlineThickness(stroke_width);

	h = structure_bg_rect.getSize().y * 0.2f;
	x = structure_bg_rect.getPosition().x + structure_bg_rect.getSize().x * 0.1f;
	y = structure_bg_rect.getPosition().y + h * 0.2f;
	structure_text.setPosition(x, y);
	structure_text.setCharacterSize(h);

	h = structure_bg_rect.getSize().y * 0.3;
	w = h * (float(save_structure_button.texture_width) / save_structure_button.texture_height);
	x = structure_bg_rect.getPosition().x + structure_bg_rect.getSize().x / 2 - w * 1.01f;
	y = structure_bg_rect.getPosition().y + structure_bg_rect.getSize().y * 0.5;
	save_structure_button.set_position(x, y);
	save_structure_button.set_size(w, h);

	h = structure_bg_rect.getSize().y * 0.3;
	w = h * (float(load_structure_button.texture_width) / load_structure_button.texture_height);
	x = structure_bg_rect.getPosition().x + structure_bg_rect.getSize().x / 2 + w * 0.01f;
	y = structure_bg_rect.getPosition().y + structure_bg_rect.getSize().y * 0.5;
	load_structure_button.set_position(x, y);
	load_structure_button.set_size(w, h);


}

void Inventory::update() {
	if (Utils::point_vs_rect(window_mouse.x, window_mouse.y, inventory_bg_rect.getPosition().x, inventory_bg_rect.getPosition().y,
		inventory_bg_rect.getSize().x, inventory_bg_rect.getSize().y)  ||
		Utils::point_vs_rect(window_mouse.x, window_mouse.y, structure_bg_rect.getPosition().x, structure_bg_rect.getPosition().y,
			structure_bg_rect.getSize().x, structure_bg_rect.getSize().y)) {
		sim->mouse_over_gui = true;

		inv_air_button.update(window_mouse.x, window_mouse.y);
		inv_wire_button.update(window_mouse.x, window_mouse.y);
		inv_out_button.update(window_mouse.x, window_mouse.y);
		inv_battery_button.update(window_mouse.x, window_mouse.y);
		inv_delay_button.update(window_mouse.x, window_mouse.y);
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

		inv_clock_button.update(window_mouse.x, window_mouse.y);


		save_structure_button.update(window_mouse.x, window_mouse.y);
		load_structure_button.update(window_mouse.x, window_mouse.y);
	}
}

void Inventory::render(sf::RenderTarget& window) {
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

	inv_delay_button.render(window);
	window.draw(inv_delay_text);

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

	inv_clock_button.render(window);
	window.draw(inv_clock_text);

	window.draw(inv_logic_gates_text);


	//structure gui
	window.draw(structure_bg_rect);
	window.draw(structure_text);
	save_structure_button.render(window);
	load_structure_button.render(window);

}
