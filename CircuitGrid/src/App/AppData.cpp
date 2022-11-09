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
bool FOCUS = true;
bool closing = false;
sf::Vector2i window_mouse;
float gui_scale = 1.0f;
int screen_id = 0;
enum SCREEN_ID;
sf::Font* font;
IO_DATA io_data;

//========== SIMULATION SCREEN ==========

bool show_debug_info;

//navigation
float move_speed;
float zoom_speed = 0.1f;
float board_offset_x = 0, board_offset_y = 0;
float target_board_offset_x = 0, target_board_offset_y = 0;
float zoom_factor, target_zoom_factor;

//board data
uint8_t board_version;
uint8_t structure_version;

sf::Shader* board_shader;
sf::Texture* board_data_texture;
sf::RectangleShape render_rect;
sf::Texture* render_texture;
sf::Texture* pixel_color_texture;
sf::Texture* large_pixel_texture;

int board_width = 0, board_height = 0, board_size = 0;
uint8_t* this_board = nullptr;
uint8_t* next_board = nullptr;
sf::Vector2f board_mouse;
sf::Vector2f last_board_mouse;
float board_tps = 10;
long long clock_time_last;
uint32_t clock_time_difference;
bool simulation_paused;
uint32_t selected_item = 0;
std::vector<uint32_t> item_list;
uint8_t item_count = 0;
enum ITEM;
std::vector<std::string> item_names;
bool one_simulations_step;
double update_time_taken;
double upload_texture_to_gpu_time_taken;
uint32_t number_of_pixels_to_update;

std::vector<uint32_t> update_list;
bool* update_checklist = nullptr;
uint32_t* update_list_copy = nullptr;