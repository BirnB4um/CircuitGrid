#include "AppData.h"

//========== APPLICATION DATA ==========

//window stuff
int WINDOWED_WIDTH = 0, WINDOWED_HEIGHT = 0;
int FULLSCREEN_WIDTH = 0, FULLSCREEN_HEIGHT = 0;
int SCREEN_WIDTH = 0, SCREEN_HEIGHT = 0;
float SCREEN_RATIO = 0;
std::string TITLE;
bool FULLSCREEN = false;
int FPS = 0;
bool closing = false;
sf::Vector2i window_mouse;
float gui_scale = 1.0f;
int screen_id = 0;
enum SCREEN_ID;
sf::Font font;

//========== SIMULATION SCREEN ==========

//navigation
float move_speed = 8;
float zoom_speed = 0.1f;
float board_offset_x = 0, board_offset_y = 0;
float target_board_offset_x = 0, target_board_offset_y = 0;
float zoom_factor = 1, target_zoom_factor = 1;

//board data
int board_width = 0, board_height = 0, board_size = 0;
uint8_t* this_board = nullptr;
uint8_t* next_board = nullptr;
sf::Vector2f board_mouse;
sf::Vector2f last_board_mouse;
float board_tps = 10;
bool simulation_paused;
uint32_t selected_item = 0;
uint32_t* item_list = nullptr;
uint8_t item_count = 0;
enum ITEM;
std::string* item_names;

std::vector<uint32_t> update_list;
bool* update_checklist = nullptr;
uint32_t* update_list_copy = nullptr;