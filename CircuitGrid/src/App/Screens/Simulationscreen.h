#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include <mutex>
#include <chrono>
#include <functional>
#include "../AppData.h"
#include "../../GUI/Button.h"
#include "../../GUI/Slider.h"
#include "../../Tools/Utils.h"
#include "../../Tools/Timer.h"
#include "SimulationscreenGUI/Inventory.h"
#include "SimulationscreenGUI/HelpMenu.h"
#include "SimulationscreenGUI/TopGUI.h"
#include "SimulationscreenGUI/InfoBox.h"


class Simulationscreen
{

public:

	//GUI
	bool show_gui;

	TopGUI gui;

	Inventory inventory;
	bool show_inventory;

	HelpMenu helpmenu;

	InfoBox infobox;

	//debug stuff
	sf::Text upload_to_gpu_time_text;
	sf::Text update_board_time_text;
	sf::Text updates_number_text;



	//update stuff
	std::thread update_board_thread;

	bool pasting;
	sf::RectangleShape paste_rect;
	uint8_t* paste_structure;
	uint32_t paste_x, paste_y;

	uint8_t* loaded_structure;

	uint8_t* copy_structure;
	struct Drawinstruction {
		uint32_t data[7];//drawtype, brushsize, element to draw, pos1x, pos1y, pos2x, pos2y
		uint8_t* structure_pointer;
	};
	enum DRAWTYPE { POINT, LINE, RECT, FILL, STRUCTURE };
	std::vector<Drawinstruction> drawinstruction_list;
	std::mutex draw_mutex;
	uint32_t brush_size;
	bool start_drawing_rectangle;
	bool drawing_rectangle;
	bool start_drawing_line;
	bool drawing_line;
	int drawing_start_x;
	int drawing_start_y;
	int drawing_end_x;
	int drawing_end_y;
	sf::RectangleShape drawing_rect_shape;
	sf::RectangleShape drawing_line_shape;
	bool edit_mode;
	bool fill_mode;
	bool draw_grid;
	bool draw_details;
	bool show_help_menu;

	bool mouse_over_gui;
	bool mouse_over_board;
	bool last_mouse_over_board;

	bool dragging_board;
	float drag_start_x;
	float drag_start_y;
	float drag_start_offset_x;
	float drag_start_offset_y;
	bool can_drag_with_keyboard;

	bool clear_board_bool;
	bool reset_simulation_bool;
	bool selection_mode;

	bool selection_set;
	uint8_t selection_part;//0:nothing; 1:top_left; 2:top_right; 3:bottom_left; 4:bottom_right; 5:top; 6:left; 7:right; 8:bottom; 9:all
	long selection_mouse_offset_x;
	long selection_mouse_offset_y;
	long selection_start_x;
	long selection_start_y;
	long selection_end_x;
	long selection_end_y;
	sf::RectangleShape selection_rect;

	std::vector <bool(Simulationscreen::*)(uint32_t& i)> update_functions;

	void reset_simulation();
	void clear_board();
	void add_to_update_list(uint32_t i);
	void add_surroundings_to_update_list(uint32_t i);
	bool draw_to_board();
	void update_board();
	void th_update_board();
	void create_board(unsigned int width, unsigned int height);
	void load_resources();
	void init_update_functions();

public:
	Simulationscreen();
	~Simulationscreen();
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
	bool update_out(uint32_t& i);
	bool update_battery(uint32_t& i);
	bool update_repeater(uint32_t& i);
	bool update_bridge(uint32_t& i);
	bool update_button(uint32_t& i);
	bool update_switch(uint32_t& i);
	bool update_lamp(uint32_t& i);
	bool update_not(uint32_t& i);
	bool update_or(uint32_t& i);
	bool update_xor(uint32_t& i);
	bool update_nor(uint32_t& i);
	bool update_xnor(uint32_t& i);
	bool update_and(uint32_t& i);
	bool update_nand(uint32_t& i);
};
