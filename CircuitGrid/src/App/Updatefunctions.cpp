#include "Screens/Simulationscreen.h"
/*
	0  -  Air
	1  -  Wire
	2  -  Battery
	3  -  In
	4  -  Out
	5  -  Not
	6  -  Or
	7  -  Xor
	8  -  Nor
	9  -  Xnor
	10 -  And
	11 -  Nand
	12 -  Button
	13 -  Switch
	14 -  Lamp
	15 -  Repeater

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

bool Simulationscreen::update_battery(uint32_t& i) {
	return false;
}

bool Simulationscreen::update_in(uint32_t& i) {
	return false;
}

bool Simulationscreen::update_out(uint32_t& i) {
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

bool Simulationscreen::update_repeater(uint32_t& i) {
	return false;
}