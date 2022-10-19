#include "Screens/Simulationscreen.h"
/*
	0  -  Air
	1  -  Wire
	2  -  Out
	3  -  Battery
	4  -  Amplifier
	5  -  Bridge
	6  -  Not
	7  -  Or
	8  -  Xor
	9  -  Nor
	10 -  Xnor
	11 -  And
	12 -  Nand
	13 -  Button
	14 -  Switch
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

	//if electricity 0 -> turn normal (1)
	if (this_board[this_i + 1] == 0) {
		next_board[this_i + 1] = 1;
		return true;
	}

	//up
	if (this_board[i_up] == WIRE) {
		if (this_board[this_i + 1] > 1 && this_board[i_up + 1] == 0) {
			next_board[this_i + 1] = 0;
			return true;
		}
		if (this_board[this_i + 1] == 1 && this_board[i_up + 1] == 2) {
			next_board[this_i + 1] = 2;
		}
	}
	else if (this_board[i_up] == BATTERY) {
		next_board[this_i + 1] = 2;
	}

	//left
	if (this_board[i_left] == WIRE) {
		if (this_board[this_i + 1] > 1 && this_board[i_left + 1] == 0) {
			next_board[this_i + 1] = 0;
			return true;
		}
		if (this_board[this_i + 1] == 1 && this_board[i_left + 1] == 2) {
			next_board[this_i + 1] = 2;
		}
	}
	else if (this_board[i_left] == BATTERY) {
		next_board[this_i + 1] = 2;
	}

	//right
	if (this_board[i_right] == WIRE) {
		if (this_board[this_i + 1] > 1 && this_board[i_right + 1] == 0) {
			next_board[this_i + 1] = 0;
			return true;
		}
		if (this_board[this_i + 1] == 1 && this_board[i_right + 1] == 2) {
			next_board[this_i + 1] = 2;
		}
	}
	else if (this_board[i_right] == BATTERY) {
		next_board[this_i + 1] = 2;
	}

	//down
	if (this_board[i_down] == WIRE) {
		if (this_board[this_i + 1] > 1 && this_board[i_down + 1] == 0) {
			next_board[this_i + 1] = 0;
			return true;
		}
		if (this_board[this_i + 1] == 1 && this_board[i_down + 1] == 2) {
			next_board[this_i + 1] = 2;
		}
	}
	else if (this_board[i_down] == BATTERY) {
		next_board[this_i + 1] = 2;
	}

	return true;
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

bool Simulationscreen::update_button(uint32_t& i) {
	return false;
}

bool Simulationscreen::update_switch(uint32_t& i) {
	return false;
}

bool Simulationscreen::update_lamp(uint32_t& i) {
	return false;
}
