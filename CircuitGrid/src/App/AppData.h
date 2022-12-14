#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Tools/IO_DATA.h"

#define PI 3.1415926535

//========== APPLICATION DATA ==========

//window stuff
extern int WINDOWED_WIDTH, WINDOWED_HEIGHT;
extern int FULLSCREEN_WIDTH, FULLSCREEN_HEIGHT;
extern int SCREEN_WIDTH, SCREEN_HEIGHT;
extern float SCREEN_RATIO;
extern std::string TITLE;
extern bool FULLSCREEN;
extern int FPS;
extern bool FOCUS;
extern bool closing;
extern sf::Vector2i window_mouse;
extern float gui_scale;
extern int screen_id;
extern enum SCREEN_ID {
	HOMESCREEN, SIMULATION, SETTINGS, CREDITS
};
extern sf::Font* font;
extern IO_DATA io_data;
extern std::string version_str;

//========== SIMULATION SCREEN ==========

extern bool show_debug_info;

//navigation
extern float move_speed;
extern float zoom_speed;
extern float board_offset_x, board_offset_y;
extern float target_board_offset_x, target_board_offset_y;
extern float zoom_factor, target_zoom_factor;

//board data
extern uint8_t board_version;
extern uint8_t structure_version;

extern sf::Shader* board_shader;
extern sf::Texture* board_data_texture;
extern sf::RectangleShape render_rect;
extern sf::Texture* render_texture;
extern sf::Texture* pixel_color_texture;
extern sf::Texture* large_pixel_texture;

extern int board_width, board_height, board_size;
extern uint8_t* this_board;
extern uint8_t* next_board;
extern sf::Vector2f board_mouse;
extern sf::Vector2f last_board_mouse;
extern float board_tps;
extern long long clock_time_last;
extern uint32_t clock_time_difference;
extern bool simulation_paused;
extern uint32_t selected_item;
extern std::vector<uint32_t> item_list;
extern uint8_t item_count;
extern enum ITEM {
	AIR, WIRE, OUTPUT, BATTERY, DELAY, BRIDGE, LAMP, BUTTON, SWITCH, NOT, OR, NOR, XOR, XNOR, AND, NAND, CLOCK
};
extern std::vector<std::string> item_names;
extern bool one_simulations_step;
extern double update_time_taken;//millis
extern double upload_texture_to_gpu_time_taken;//millis
extern uint32_t number_of_pixels_to_update;

extern std::vector<uint32_t> update_list;
extern bool* update_checklist;
extern uint32_t* update_list_copy;

extern float board_texture_update_time;
