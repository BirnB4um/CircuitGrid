#include "Screens/Simulationscreen.h"
/*
	0  -  Air
	1  -  Wire
	2  -  Out
	3  -  Battery
	4  -  Amplifier
	5  -  Button
	6  -  Switch
	7  -  Bridge

	8  -  Not
	9  -  Or
	10 -  Xor
	11 -  Nor
	12 -  Xnor
	13 -  And
	14 -  Nand

	15 -  Lamp
*/

bool Simulationscreen::update_air(uint32_t& i) {
	return false;
}

bool Simulationscreen::update_wire(uint32_t& i) {
	uint32_t this_i = i * 4;
	uint32_t i_up = (i - board_width) * 4;
	uint32_t i_down = (i + board_width) * 4;
	uint32_t i_left = (i - 1) * 4;
	uint32_t i_right = (i + 1) * 4;

	uint32_t max_surrounding_electricity = 0;

	//up
	if (this_board[i_up] < BRIDGE) {
		if (this_board[i_up+1] > max_surrounding_electricity) {
			max_surrounding_electricity = this_board[i_up + 1];
		}
	}
	//left
	if (this_board[i_left] < BRIDGE) {
		if (this_board[i_left+1] > max_surrounding_electricity) {
			max_surrounding_electricity = this_board[i_left + 1];
		}
	}
	//right
	if (this_board[i_right] < BRIDGE) {
		if (this_board[i_right+1] > max_surrounding_electricity) {
			max_surrounding_electricity = this_board[i_right + 1];
		}
	}
	//down
	if (this_board[i_down] < BRIDGE) {
		if (this_board[i_down+1] > max_surrounding_electricity) {
			max_surrounding_electricity = this_board[i_down + 1];
		}
	}

	if (max_surrounding_electricity == 0)
		return false;

	next_board[i + 1] = max_surrounding_electricity - 1;
	return true;

	if (this_board[i+1] > max_surrounding_electricity) {
		next_board[i + 1] = 0;
		return true;
	}
	else {
		next_board[i + 1] = max_surrounding_electricity - 1;
		return true;
	}

	return false;
}

bool Simulationscreen::update_out(uint32_t& i) {
	return false;
}

bool Simulationscreen::update_battery(uint32_t& i) {
	return false;
}

bool Simulationscreen::update_amplifier(uint32_t& i) {
	return false;
}

bool Simulationscreen::update_button(uint32_t& i) {
	return false;
}

bool Simulationscreen::update_switch(uint32_t& i) {
	return false;
}

bool Simulationscreen::update_bridge(uint32_t& i) {
	return false;
}

bool Simulationscreen::update_not(uint32_t& i) {
	return false;
}

bool Simulationscreen::update_or(uint32_t& i) {
	return false;
}

bool Simulationscreen::update_xor(uint32_t& i) {
	return false;
}

bool Simulationscreen::update_nor(uint32_t& i) {
	return false;
}

bool Simulationscreen::update_xnor(uint32_t& i) {
	return false;
}

bool Simulationscreen::update_and(uint32_t& i) {
	return false;
}

bool Simulationscreen::update_nand(uint32_t& i) {
	return false;
}


bool Simulationscreen::update_lamp(uint32_t& i) {
	return false;
}
