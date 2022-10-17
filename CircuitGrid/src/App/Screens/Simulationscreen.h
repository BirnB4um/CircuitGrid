#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include <mutex>
#include <chrono>
#include <functional>
#include "../AppData.h"
#include "../../GUI/Button.h"
#include "../../Tools/Utils.h"
#include "../../Tools/Timer.h"

class Simulationscreen
{
private:

	//GUI
	Button pause_button;

	Button item_button;
	int item_gui_texture_width;

	//Inventory gui
	bool show_inventory;
	sf::RectangleShape inventory_bg_rect;
	//TODO: buttons for all the items + text

	//stuff to render board
	sf::Shader board_shader;
	sf::Texture board_data_texture;
	sf::RectangleShape render_rect;
	sf::Texture render_texture;
	sf::Texture pixel_color_texture;

	//update stuff
	std::thread update_board_thread;

	struct Drawinstruction {
		uint32_t data[7];//drawtype, brushsize, element to draw, pos1x, pos1y, pos2x, pos2y
	};
	enum DRAWTYPE { POINT, LINE, RECT };
	std::vector<Drawinstruction> drawinstruction_list;
	std::mutex draw_mutex;

	std::vector <bool(Simulationscreen::*)(uint32_t& i)> update_functions;

	void add_to_update_list(uint32_t i);
	bool draw_to_board();
	void update_board();
	void th_update_board();
	void create_board(unsigned int width, unsigned int height);
	void load_shader();
	void init_update_functions();

public:
	Simulationscreen();
	~Simulationscreen();
	void update_item_button_texture();
	void init();
	void resize();
	void on_closing();
	void handle_events(sf::Event& ev);
	void update();
	void render(sf::RenderTarget& window);

private:
	//update functions
	bool update_air(uint32_t& i);
	bool update_wire(uint32_t& i);
	bool update_battery(uint32_t& i);
	bool update_in(uint32_t& i);
	bool update_out(uint32_t& i);
	bool update_not(uint32_t& i);
	bool update_or(uint32_t& i);
	bool update_xor(uint32_t& i);
	bool update_nor(uint32_t& i);
	bool update_xnor(uint32_t& i);
	bool update_and(uint32_t& i);
	bool update_nand(uint32_t& i);
	bool update_button(uint32_t& i);
	bool update_switch(uint32_t& i);
	bool update_lamp(uint32_t& i);
	bool update_repeater(uint32_t& i);
};
