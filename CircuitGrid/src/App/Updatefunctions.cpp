#include "Screens/Simulationscreen.h"
/*
	0  -  Air
	1  -  Wire
	2  -  Out
	3  -  Battery
	4  -  Bridge

	5  -  Lamp
	6  -  Button
	7  -  Switch

	8  -  Not
	9  -  Or
	10 -  Nor
	11 -  Xor
	12 -  Xnor
	13 -  And
	14 -  Nand

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
	if (this_board[i_up] <= BRIDGE) {
		if (this_board[i_up + (this_board[i_up] == BRIDGE ? 2 : 1)] > max_surrounding_electricity) {
			max_surrounding_electricity = this_board[i_up + (this_board[i_up] == BRIDGE ? 2 : 1)];
		}
	}

	//down
	if (this_board[i_down] <= BRIDGE) {
		if (this_board[i_down + (this_board[i_down] == BRIDGE ? 2 : 1)] > max_surrounding_electricity) {
			max_surrounding_electricity = this_board[i_down + (this_board[i_down] == BRIDGE ? 2 : 1)];
		}
	}

	//left
	if (this_board[i_left] <= BRIDGE) {
		if (this_board[i_left + 1] > max_surrounding_electricity) {
			max_surrounding_electricity = this_board[i_left + 1];
		}
	}

	//right
	if (this_board[i_right] <= BRIDGE) {
		if (this_board[i_right + 1] > max_surrounding_electricity) {
			max_surrounding_electricity = this_board[i_right + 1];
		}
	}


	if (this_board[this_i + 1] > max_surrounding_electricity) {
		next_board[this_i + 1] = 0;
		return true;
	}
	else if(max_surrounding_electricity > 0) {
		next_board[this_i + 1] = max_surrounding_electricity - 1;
	}

	return *(uint32_t*)&this_board[this_i] != *(uint32_t*)&next_board[this_i];
}

bool Simulationscreen::update_out(uint32_t& i) {
	uint32_t this_i = i * 4;
	uint32_t i_up = (i - board_width) * 4;
	uint32_t i_down = (i + board_width) * 4;
	uint32_t i_left = (i - 1) * 4;
	uint32_t i_right = (i + 1) * 4;

	uint32_t max_surrounding_electricity = 0;

	//up
	if (this_board[i_up] >= BUTTON) {
		if (this_board[i_up + 1] > max_surrounding_electricity) {
			max_surrounding_electricity = this_board[i_up + 1];
		}
	}
	//left
	if (this_board[i_left] >= BUTTON) {
		if (this_board[i_left + 1] > max_surrounding_electricity) {
			max_surrounding_electricity = this_board[i_left + 1];
		}
	}
	//right
	if (this_board[i_right] >= BUTTON) {
		if (this_board[i_right + 1] > max_surrounding_electricity) {
			max_surrounding_electricity = this_board[i_right + 1];
		}
	}
	//down
	if (this_board[i_down] >= BUTTON) {
		if (this_board[i_down + 1] > max_surrounding_electricity) {
			max_surrounding_electricity = this_board[i_down + 1];
		}
	}
	
	next_board[this_i + 1] = max_surrounding_electricity;

	return *(uint32_t*)&this_board[this_i] != *(uint32_t*)&next_board[this_i];
}

bool Simulationscreen::update_battery(uint32_t& i) {
	return false;
}

bool Simulationscreen::update_bridge(uint32_t& i) {
	uint32_t this_i = i * 4;
	uint32_t i_up = (i - board_width) * 4;
	uint32_t i_down = (i + board_width) * 4;
	uint32_t i_left = (i - 1) * 4;
	uint32_t i_right = (i + 1) * 4;

	uint32_t max_surrounding_electricity_horizontal = 0;//---
	uint32_t max_surrounding_electricity_vertical = 0;//|||

	//left
	if (this_board[i_left] <= BRIDGE) {
		if (this_board[i_left + 1] > max_surrounding_electricity_horizontal) {
			max_surrounding_electricity_horizontal = this_board[i_left + 1];
		}
	}

	//right
	if (this_board[i_right] <= BRIDGE) {
		if (this_board[i_right + 1] > max_surrounding_electricity_horizontal) {
			max_surrounding_electricity_horizontal = this_board[i_right + 1];
		}
	}

	//up
	if (this_board[i_up] <= BRIDGE) {
		if (this_board[i_up + (this_board[i_up] == BRIDGE ? 2 : 1)] > max_surrounding_electricity_vertical) {
			max_surrounding_electricity_vertical = this_board[i_up + (this_board[i_up] == BRIDGE ? 2 : 1)];
		}
	}

	//down
	if (this_board[i_down] <= BRIDGE) {
		if (this_board[i_down + (this_board[i_down] == BRIDGE ? 2 : 1)] > max_surrounding_electricity_vertical) {
			max_surrounding_electricity_vertical = this_board[i_down + (this_board[i_down] == BRIDGE ? 2 : 1)];
		}
	}


	//horizontal check
	if (this_board[this_i + 1] > max_surrounding_electricity_horizontal) {
		next_board[this_i + 1] = 0;
	}
	else if(max_surrounding_electricity_horizontal > 0) {
		next_board[this_i + 1] = max_surrounding_electricity_horizontal - 1;
	}

	//vertical check
	if (this_board[this_i + 2] > max_surrounding_electricity_vertical) {
		next_board[this_i + 2] = 0;
	}
	else if(max_surrounding_electricity_vertical > 0) {
		next_board[this_i + 2] = max_surrounding_electricity_vertical - 1;
	}

	return *(uint32_t*)&this_board[this_i] != *(uint32_t*)&next_board[this_i];
}

bool Simulationscreen::update_lamp(uint32_t& i) {
	return false;
}

bool Simulationscreen::update_button(uint32_t& i) {
	return false;
}

bool Simulationscreen::update_switch(uint32_t& i) {
	return false;
}

bool Simulationscreen::update_not(uint32_t& i) {
	uint32_t this_i = i * 4;
	uint32_t i_up = (i - board_width) * 4;
	uint32_t i_down = (i + board_width) * 4;
	uint32_t i_left = (i - 1) * 4;
	uint32_t i_right = (i + 1) * 4;

	char surrounding_electricity_count = 0;

	//up
	if (this_board[i_up] <= BRIDGE && this_board[i_up] != OUT) {
		if (this_board[i_up + (this_board[i_up] == BRIDGE ? 2 : 1)] > 0) {
			surrounding_electricity_count++;
		}
	}

	//down
	if (this_board[i_down] <= BRIDGE && this_board[i_down] != OUT) {
		if (this_board[i_down + (this_board[i_down] == BRIDGE ? 2 : 1)] > 0) {
			surrounding_electricity_count++;
		}
	}

	//left
	if (this_board[i_left] <= BRIDGE && this_board[i_left] != OUT) {
		if (this_board[i_left + 1] > 0) {
			surrounding_electricity_count++;

		}
	}

	//right
	if (this_board[i_right] <= BRIDGE && this_board[i_right] != OUT) {
		if (this_board[i_right + 1] > 0) {
			surrounding_electricity_count++;
		}
	}


	if (surrounding_electricity_count > 0) {
		next_board[this_i + 1] = 0;
	}
	else {
		next_board[this_i + 1] = 0xFF;
	}

	return *(uint32_t*)&this_board[this_i] != *(uint32_t*)&next_board[this_i];
}

bool Simulationscreen::update_or(uint32_t& i) {
	uint32_t this_i = i * 4;
	uint32_t i_up = (i - board_width) * 4;
	uint32_t i_down = (i + board_width) * 4;
	uint32_t i_left = (i - 1) * 4;
	uint32_t i_right = (i + 1) * 4;

	char surrounding_electricity_count = 0;

	//up
	if (this_board[i_up] <= BRIDGE && this_board[i_up] != OUT) {
		if (this_board[i_up + (this_board[i_up] == BRIDGE ? 2 : 1)] > 0) {
			surrounding_electricity_count++;
		}
	}

	//down
	if (this_board[i_down] <= BRIDGE && this_board[i_down] != OUT) {
		if (this_board[i_down + (this_board[i_down] == BRIDGE ? 2 : 1)] > 0) {
			surrounding_electricity_count++;
		}
	}

	//left
	if (this_board[i_left] <= BRIDGE && this_board[i_left] != OUT) {
		if (this_board[i_left + 1] > 0) {
			surrounding_electricity_count++;

		}
	}

	//right
	if (this_board[i_right] <= BRIDGE && this_board[i_right] != OUT) {
		if (this_board[i_right + 1] > 0) {
			surrounding_electricity_count++;
		}
	}


	if (surrounding_electricity_count > 0) {
		next_board[this_i + 1] = 0xFF;
	}
	else {
		next_board[this_i + 1] = 0;
	}

	return *(uint32_t*)&this_board[this_i] != *(uint32_t*)&next_board[this_i];
}

bool Simulationscreen::update_nor(uint32_t& i) {
	uint32_t this_i = i * 4;
	uint32_t i_up = (i - board_width) * 4;
	uint32_t i_down = (i + board_width) * 4;
	uint32_t i_left = (i - 1) * 4;
	uint32_t i_right = (i + 1) * 4;

	char surrounding_electricity_count = 0;

	//up
	if (this_board[i_up] <= BRIDGE && this_board[i_up] != OUT) {
		if (this_board[i_up + (this_board[i_up] == BRIDGE ? 2 : 1)] > 0) {
			surrounding_electricity_count++;
		}
	}

	//down
	if (this_board[i_down] <= BRIDGE && this_board[i_down] != OUT) {
		if (this_board[i_down + (this_board[i_down] == BRIDGE ? 2 : 1)] > 0) {
			surrounding_electricity_count++;
		}
	}

	//left
	if (this_board[i_left] <= BRIDGE && this_board[i_left] != OUT) {
		if (this_board[i_left + 1] > 0) {
			surrounding_electricity_count++;

		}
	}

	//right
	if (this_board[i_right] <= BRIDGE && this_board[i_right] != OUT) {
		if (this_board[i_right + 1] > 0) {
			surrounding_electricity_count++;
		}
	}


	if (surrounding_electricity_count == 0) {
		next_board[this_i + 1] = 0xFF;
	}
	else {
		next_board[this_i + 1] = 0;
	}

	return *(uint32_t*)&this_board[this_i] != *(uint32_t*)&next_board[this_i];
}

bool Simulationscreen::update_xor(uint32_t& i) {
	uint32_t this_i = i * 4;
	uint32_t i_up = (i - board_width) * 4;
	uint32_t i_down = (i + board_width) * 4;
	uint32_t i_left = (i - 1) * 4;
	uint32_t i_right = (i + 1) * 4;

	char surrounding_electricity_count = 0;

	//up
	if (this_board[i_up] <= BRIDGE && this_board[i_up] != OUT) {
		if (this_board[i_up + (this_board[i_up] == BRIDGE ? 2 : 1)] > 0) {
			surrounding_electricity_count++;
		}
	}

	//down
	if (this_board[i_down] <= BRIDGE && this_board[i_down] != OUT) {
		if (this_board[i_down + (this_board[i_down] == BRIDGE ? 2 : 1)] > 0) {
			surrounding_electricity_count++;
		}
	}

	//left
	if (this_board[i_left] <= BRIDGE && this_board[i_left] != OUT) {
		if (this_board[i_left + 1] > 0) {
			surrounding_electricity_count++;

		}
	}

	//right
	if (this_board[i_right] <= BRIDGE && this_board[i_right] != OUT) {
		if (this_board[i_right + 1] > 0) {
			surrounding_electricity_count++;
		}
	}


	if (surrounding_electricity_count == 1) {
		next_board[this_i + 1] = 0xFF;
	}
	else {
		next_board[this_i + 1] = 0;
	}

	return *(uint32_t*)&this_board[this_i] != *(uint32_t*)&next_board[this_i];
}

bool Simulationscreen::update_xnor(uint32_t& i) {
	uint32_t this_i = i * 4;
	uint32_t i_up = (i - board_width) * 4;
	uint32_t i_down = (i + board_width) * 4;
	uint32_t i_left = (i - 1) * 4;
	uint32_t i_right = (i + 1) * 4;

	char surrounding_electricity_count = 0;

	//up
	if (this_board[i_up] <= BRIDGE && this_board[i_up] != OUT) {
		if (this_board[i_up + (this_board[i_up] == BRIDGE ? 2 : 1)] > 0) {
			surrounding_electricity_count++;
		}
	}

	//down
	if (this_board[i_down] <= BRIDGE && this_board[i_down] != OUT) {
		if (this_board[i_down + (this_board[i_down] == BRIDGE ? 2 : 1)] > 0) {
			surrounding_electricity_count++;
		}
	}

	//left
	if (this_board[i_left] <= BRIDGE && this_board[i_left] != OUT) {
		if (this_board[i_left + 1] > 0) {
			surrounding_electricity_count++;

		}
	}

	//right
	if (this_board[i_right] <= BRIDGE && this_board[i_right] != OUT) {
		if (this_board[i_right + 1] > 0) {
			surrounding_electricity_count++;
		}
	}


	if (surrounding_electricity_count != 1) {
		next_board[this_i + 1] = 0xFF;
	}
	else {
		next_board[this_i + 1] = 0;
	}

	return *(uint32_t*)&this_board[this_i] != *(uint32_t*)&next_board[this_i];
}

bool Simulationscreen::update_and(uint32_t& i) {
	uint32_t this_i = i * 4;
	uint32_t i_up = (i - board_width) * 4;
	uint32_t i_down = (i + board_width) * 4;
	uint32_t i_left = (i - 1) * 4;
	uint32_t i_right = (i + 1) * 4;

	char surrounding_electricity_count = 0;

	//up
	if (this_board[i_up] <= BRIDGE && this_board[i_up] != OUT) {
		if (this_board[i_up + (this_board[i_up] == BRIDGE ? 2 : 1)] > 0) {
			surrounding_electricity_count++;
		}
	}

	//down
	if (this_board[i_down] <= BRIDGE && this_board[i_down] != OUT) {
		if (this_board[i_down + (this_board[i_down] == BRIDGE ? 2 : 1)] > 0) {
			surrounding_electricity_count++;
		}
	}

	//left
	if (this_board[i_left] <= BRIDGE && this_board[i_left] != OUT) {
		if (this_board[i_left + 1] > 0) {
			surrounding_electricity_count++;

		}
	}

	//right
	if (this_board[i_right] <= BRIDGE && this_board[i_right] != OUT) {
		if (this_board[i_right + 1] > 0) {
			surrounding_electricity_count++;
		}
	}


	if (surrounding_electricity_count > 1) {
		next_board[this_i + 1] = 0xFF;
	}
	else {
		next_board[this_i + 1] = 0;
	}

	return *(uint32_t*)&this_board[this_i] != *(uint32_t*)&next_board[this_i];
}

bool Simulationscreen::update_nand(uint32_t& i) {
	uint32_t this_i = i * 4;
	uint32_t i_up = (i - board_width) * 4;
	uint32_t i_down = (i + board_width) * 4;
	uint32_t i_left = (i - 1) * 4;
	uint32_t i_right = (i + 1) * 4;

	char surrounding_electricity_count = 0;

	//up
	if (this_board[i_up] <= BRIDGE && this_board[i_up] != OUT) {
		if (this_board[i_up + (this_board[i_up] == BRIDGE ? 2 : 1)] > 0) {
			surrounding_electricity_count++;
		}
	}

	//down
	if (this_board[i_down] <= BRIDGE && this_board[i_down] != OUT) {
		if (this_board[i_down + (this_board[i_down] == BRIDGE ? 2 : 1)] > 0) {
			surrounding_electricity_count++;
		}
	}

	//left
	if (this_board[i_left] <= BRIDGE && this_board[i_left] != OUT) {
		if (this_board[i_left + 1] > 0) {
			surrounding_electricity_count++;

		}
	}

	//right
	if (this_board[i_right] <= BRIDGE && this_board[i_right] != OUT) {
		if (this_board[i_right + 1] > 0) {
			surrounding_electricity_count++;
		}
	}


	if (surrounding_electricity_count < 2) {
		next_board[this_i + 1] = 0xFF;
	}
	else {
		next_board[this_i + 1] = 0;
	}

	return *(uint32_t*)&this_board[this_i] != *(uint32_t*)&next_board[this_i];
}

