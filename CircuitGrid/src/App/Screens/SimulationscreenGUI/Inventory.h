#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../../../GUI/Button.h"

class Simulationscreen;


class Inventory
{
public:
	Simulationscreen* sim;

	sf::RectangleShape inventory_bg_rect;
	sf::Text inventory_text;
	sf::Text inv_air_text;
	Button inv_air_button;
	sf::Text inv_wire_text;
	Button inv_wire_button;
	sf::Text inv_out_text;
	Button inv_out_button;
	sf::Text inv_battery_text;
	Button inv_battery_button;
	sf::Text inv_delay_text;
	Button inv_delay_button;
	sf::Text inv_bridge_text;
	Button inv_bridge_button;
	sf::Text inv_lamp_text;
	Button inv_lamp_button;
	sf::Text inv_button_text;
	Button inv_button_button;
	sf::Text inv_switch_text;
	Button inv_switch_button;

	sf::Text inv_logic_gates_text;

	sf::Text inv_not_text;
	Button inv_not_button;
	sf::Text inv_or_text;
	Button inv_or_button;
	sf::Text inv_xor_text;
	Button inv_xor_button;
	sf::Text inv_nor_text;
	Button inv_nor_button;
	sf::Text inv_xnor_text;
	Button inv_xnor_button;
	sf::Text inv_and_text;
	Button inv_and_button;
	sf::Text inv_nand_text;
	Button inv_nand_button;

	sf::Text inv_clock_text;
	Button inv_clock_button;

	//structure gui
	sf::RectangleShape structure_bg_rect;
	sf::Text structure_text;
	Button save_structure_button;
	Button load_structure_button;

	void init();
	void resize();
	void update();
	void render(sf::RenderTarget& window);

};

