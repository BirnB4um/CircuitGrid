#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

//========== APPLICATION DATA ==========

//window stuff
extern int WINDOWED_WIDTH, WINDOWED_HEIGHT;
extern int FULLSCREEN_WIDTH, FULLSCREEN_HEIGHT;
extern int SCREEN_WIDTH, SCREEN_HEIGHT;
extern float SCREEN_RATIO;
extern std::string TITLE;
extern bool FULLSCREEN;
extern int FPS;
extern bool closing;
extern sf::Vector2i window_mouse;
extern float gui_scale;
extern int screen_id;
extern enum SCREEN_ID {
	HOMESCREEN, SIMULATION
};
extern sf::Font* font;

//========== SIMULATION SCREEN ==========

//navigation
extern float move_speed;
extern float zoom_speed;
extern float board_offset_x, board_offset_y;
extern float target_board_offset_x, target_board_offset_y;
extern float zoom_factor, target_zoom_factor;

//board data
extern int board_width, board_height, board_size;
extern uint8_t* this_board;
extern uint8_t* next_board;
extern sf::Vector2f board_mouse;
extern sf::Vector2f last_board_mouse;
extern float board_tps;
extern bool simulation_paused;
extern uint32_t selected_item;
extern std::vector<uint32_t> item_list;
extern uint8_t item_count;
extern enum ITEM {
	AIR, WIRE, OUT, BATTERY, AMPLIFIER, BUTTON, SWITCH, BRIDGE, NOT, OR, XOR, NOR, XNOR, AND, NAND, LAMP
};
extern std::vector<std::string> item_names;

extern std::vector<uint32_t> update_list;
extern bool* update_checklist;
extern uint32_t* update_list_copy;
