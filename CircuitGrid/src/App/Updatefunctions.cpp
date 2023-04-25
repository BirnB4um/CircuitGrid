#include "Screens/Simulationscreen.h"
/*
	0  -  Air
	1  -  Wire
	2  -  Out
	3  -  Battery
	4  -  Delay
	5  -  Bridge

	6  -  Lamp
	7  -  Button
	8  -  Switch

	9  -  Not
	10  -  Or
	11 -  Nor
	12 -  Xor
	13 -  Xnor
	14 -  And
	15 -  Nand

	16 - Clock
	17 - Debug

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

	uint8_t surrounding_data = 0;//0b1:nachbar ist 0; 0x10:nachbar ist 2

	//up
	if (this_board[i_up] > AIR && this_board[i_up] <= BRIDGE) {
		if (this_board[i_up + (this_board[i_up] == BRIDGE ? 2 : 1)] == 0) {
			surrounding_data = surrounding_data | 0b1;
		}
		else if (this_board[i_up + (this_board[i_up] == BRIDGE ? 2 : 1)] == 2) {
			surrounding_data = surrounding_data | 0b10;
		}
	}

	//down
	if (this_board[i_down] > AIR && this_board[i_down] <= BRIDGE) {
		if (this_board[i_down + (this_board[i_down] == BRIDGE ? 2 : 1)] == 0) {
			surrounding_data = surrounding_data | 0b1;
		}
		else if (this_board[i_down + (this_board[i_down] == BRIDGE ? 2 : 1)] == 2) {
			surrounding_data = surrounding_data | 0b10;
		}
	}

	//left
	if (this_board[i_left] > AIR && this_board[i_left] <= BRIDGE) {
		if (this_board[i_left + 1] == 0) {
			surrounding_data = surrounding_data | 0b1;
		}
		else if (this_board[i_left + 1] == 2) {
			surrounding_data = surrounding_data | 0b10;
		}
	}

	//right
	if (this_board[i_right] > AIR && this_board[i_right] <= BRIDGE) {
		if (this_board[i_right + 1] == 0) {
			surrounding_data = surrounding_data | 0b1;
		}
		else if (this_board[i_right + 1] == 2) {
			surrounding_data = surrounding_data | 0b10;
		}
	}


	if (this_board[this_i + 1] == 0) {//if off -> normal
		next_board[this_i + 1] = 1;
	}
	else if (this_board[this_i + 1] == 2 && surrounding_data & 0b1) {//if on && surrounding off -> off
		next_board[this_i + 1] = 0;
	}
	else if (this_board[this_i + 1] == 1 && surrounding_data & 0b10) {//if normal && surrounding on -> on
		next_board[this_i + 1] = 2;
	}
	

	return *(uint32_t*)&this_board[this_i] != *(uint32_t*)&next_board[this_i];
}

bool Simulationscreen::update_out(uint32_t& i) {
	uint32_t this_i = i * 4;
	uint32_t i_up = (i - board_width) * 4;
	uint32_t i_down = (i + board_width) * 4;
	uint32_t i_left = (i - 1) * 4;
	uint32_t i_right = (i + 1) * 4;

	//set off
	next_board[this_i + 1] = 0;

	//up
	if (this_board[i_up] >= BUTTON) {
		if (this_board[i_up + 1] > 1) {
			next_board[this_i + 1] = 2;
		}
	}
	//left
	if (this_board[i_left] >= BUTTON) {
		if (this_board[i_left + 1] > 1) {
			next_board[this_i + 1] = 2;
		}
	}
	//right
	if (this_board[i_right] >= BUTTON) {
		if (this_board[i_right + 1] > 1) {
			next_board[this_i + 1] = 2;
		}
	}
	//down
	if (this_board[i_down] >= BUTTON) {
		if (this_board[i_down + 1] > 1) {
			next_board[this_i + 1] = 2;
		}
	}


	return *(uint32_t*)&this_board[this_i] != *(uint32_t*)&next_board[this_i];
}

bool Simulationscreen::update_battery(uint32_t& i) {
	return false;
}

bool Simulationscreen::update_delay(uint32_t& i) {
	uint32_t this_i = i * 4;
	uint32_t i_up = (i - board_width) * 4;
	uint32_t i_down = (i + board_width) * 4;
	uint32_t i_left = (i - 1) * 4;
	uint32_t i_right = (i + 1) * 4;

	uint8_t surrounding_data = 0;//0b1:nachbar ist 0; 0x10:nachbar ist 2

	//up
	if (this_board[i_up] > AIR && this_board[i_up] <= BRIDGE) {
		if (this_board[i_up + (this_board[i_up] == BRIDGE ? 2 : 1)] == 0) {
			surrounding_data = surrounding_data | 0b1;
		}
		else if (this_board[i_up + (this_board[i_up] == BRIDGE ? 2 : 1)] == 2) {
			surrounding_data = surrounding_data | 0b10;
		}
	}

	//down
	if (this_board[i_down] > AIR && this_board[i_down] <= BRIDGE) {
		if (this_board[i_down + (this_board[i_down] == BRIDGE ? 2 : 1)] == 0) {
			surrounding_data = surrounding_data | 0b1;
		}
		else if (this_board[i_down + (this_board[i_down] == BRIDGE ? 2 : 1)] == 2) {
			surrounding_data = surrounding_data | 0b10;
		}
	}

	//left
	if (this_board[i_left] > AIR && this_board[i_left] <= BRIDGE) {
		if (this_board[i_left + 1] == 0) {
			surrounding_data = surrounding_data | 0b1;
		}
		else if (this_board[i_left + 1] == 2) {
			surrounding_data = surrounding_data | 0b10;
		}
	}

	//right
	if (this_board[i_right] > AIR && this_board[i_right] <= BRIDGE) {
		if (this_board[i_right + 1] == 0) {
			surrounding_data = surrounding_data | 0b1;
		}
		else if (this_board[i_right + 1] == 2) {
			surrounding_data = surrounding_data | 0b10;
		}
	}


	if (this_board[this_i + 1] == 0) {//if off -> normal
		next_board[this_i + 1] = 1;
	}
	else if (this_board[this_i + 1] > 1) {
		if(surrounding_data & 0b1){//if on && surrounding off -> off
			next_board[this_i + 1] = 0;
		}
		else if(this_board[this_i + 1] > 2) {//if over activ -> --
			next_board[this_i + 1] = this_board[this_i + 1] - 1;
		}
	}
	else if (this_board[this_i + 1] == 1 && surrounding_data & 0b10) {//if normal && surrounding on -> on
		next_board[this_i + 1] = this_board[this_i + 2];
	}


	return *(uint32_t*)&this_board[this_i] != *(uint32_t*)&next_board[this_i];
}

bool Simulationscreen::update_bridge(uint32_t& i) {
	uint32_t this_i = i * 4;
	uint32_t i_up = (i - board_width) * 4;
	uint32_t i_down = (i + board_width) * 4;
	uint32_t i_left = (i - 1) * 4;
	uint32_t i_right = (i + 1) * 4;

	uint8_t surrounding_data_vertical = 0;//0b1:nachbar ist 0; 0x10:nachbar ist 2
	uint8_t surrounding_data_horizonatal = 0;//0b1:nachbar ist 0; 0x10:nachbar ist 2

	//up
	if (this_board[i_up] > AIR && this_board[i_up] <= BRIDGE) {
		if (this_board[i_up + (this_board[i_up] == BRIDGE ? 2 : 1)] == 0) {
			surrounding_data_vertical = surrounding_data_vertical | 0b1;
		}
		else if (this_board[i_up + (this_board[i_up] == BRIDGE ? 2 : 1)] == 2) {
			surrounding_data_vertical = surrounding_data_vertical | 0b10;
		}
	}

	//down
	if (this_board[i_down] > AIR && this_board[i_down] <= BRIDGE) {
		if (this_board[i_down + (this_board[i_down] == BRIDGE ? 2 : 1)] == 0) {
			surrounding_data_vertical = surrounding_data_vertical | 0b1;
		}
		else if (this_board[i_down + (this_board[i_down] == BRIDGE ? 2 : 1)] == 2) {
			surrounding_data_vertical = surrounding_data_vertical | 0b10;
		}
	}

	//left
	if (this_board[i_left] > AIR && this_board[i_left] <= BRIDGE) {
		if (this_board[i_left + 1] == 0) {
			surrounding_data_horizonatal = surrounding_data_horizonatal | 0b1;
		}
		else if (this_board[i_left + 1] == 2) {
			surrounding_data_horizonatal = surrounding_data_horizonatal | 0b10;
		}
	}

	//right
	if (this_board[i_right] > AIR && this_board[i_right] <= BRIDGE) {
		if (this_board[i_right + 1] == 0) {
			surrounding_data_horizonatal = surrounding_data_horizonatal | 0b1;
		}
		else if (this_board[i_right + 1] == 2) {
			surrounding_data_horizonatal = surrounding_data_horizonatal | 0b10;
		}
	}





	//vertical
	if (this_board[this_i + 2] == 0) {//if off -> normal
		next_board[this_i + 2] = 1;
	}
	else if (this_board[this_i + 2] == 2 && surrounding_data_vertical & 0b1) {//if on && surrounding off -> off
		next_board[this_i + 2] = 0;
	}
	else if (this_board[this_i + 2] == 1 && surrounding_data_vertical & 0b10) {//if normal && surrounding on -> on
		next_board[this_i + 2] = 2;
	}

	//horizontal
	if (this_board[this_i + 1] == 0) {//if off -> normal
		next_board[this_i + 1] = 1;
	}
	else if (this_board[this_i + 1] == 2 && surrounding_data_horizonatal & 0b1) {//if on && surrounding off -> off
		next_board[this_i + 1] = 0;
	}
	else if (this_board[this_i + 1] == 1 && surrounding_data_horizonatal & 0b10) {//if normal && surrounding on -> on
		next_board[this_i + 1] = 2;
	}


	return *(uint32_t*)&this_board[this_i] != *(uint32_t*)&next_board[this_i];
}

bool Simulationscreen::update_lamp(uint32_t& i) {
	uint32_t this_i = i * 4;
	uint32_t i_up = (i - board_width) * 4;
	uint32_t i_down = (i + board_width) * 4;
	uint32_t i_left = (i - 1) * 4;
	uint32_t i_right = (i + 1) * 4;

	uint8_t surrounding_data = 0;//0b1:nachbar ist 0; 0x10:nachbar ist 2

	//up
	if (this_board[i_up] > AIR && this_board[i_up] <= BRIDGE) {
		if (this_board[i_up + (this_board[i_up] == BRIDGE ? 2 : 1)] == 0) {
			surrounding_data = surrounding_data | 0b1;
		}
		else if (this_board[i_up + (this_board[i_up] == BRIDGE ? 2 : 1)] == 2) {
			surrounding_data = surrounding_data | 0b10;
		}
	}
	else if (this_board[i_up] == LAMP) {
		if (this_board[i_up + 1] == 0) {
			surrounding_data = surrounding_data | 0b1;
		}
		else if (this_board[i_up + 1] == 2) {
			surrounding_data = surrounding_data | 0b10;
		}
	}

	//down
	if (this_board[i_down] > AIR && this_board[i_down] <= BRIDGE) {
		if (this_board[i_down + (this_board[i_down] == BRIDGE ? 2 : 1)] == 0) {
			surrounding_data = surrounding_data | 0b1;
		}
		else if (this_board[i_down + (this_board[i_down] == BRIDGE ? 2 : 1)] == 2) {
			surrounding_data = surrounding_data | 0b10;
		}
	}
	else if (this_board[i_down] == LAMP) {
		if (this_board[i_down + 1] == 0) {
			surrounding_data = surrounding_data | 0b1;
		}
		else if (this_board[i_down + 1] == 2) {
			surrounding_data = surrounding_data | 0b10;
		}
	}

	//left
	if (this_board[i_left] > AIR && this_board[i_left] <= BRIDGE) {
		if (this_board[i_left + 1] == 0) {
			surrounding_data = surrounding_data | 0b1;
		}
		else if (this_board[i_left + 1] == 2) {
			surrounding_data = surrounding_data | 0b10;
		}
	}
	else if (this_board[i_left] == LAMP) {
		if (this_board[i_left + 1] == 0) {
			surrounding_data = surrounding_data | 0b1;
		}
		else if (this_board[i_left + 1] == 2) {
			surrounding_data = surrounding_data | 0b10;
		}
	}

	//right
	if (this_board[i_right] > AIR && this_board[i_right] <= BRIDGE) {
		if (this_board[i_right + 1] == 0) {
			surrounding_data = surrounding_data | 0b1;
		}
		else if (this_board[i_right + 1] == 2) {
			surrounding_data = surrounding_data | 0b10;
		}
	}
	else if (this_board[i_right] == LAMP) {
		if (this_board[i_right + 1] == 0) {
			surrounding_data = surrounding_data | 0b1;
		}
		else if (this_board[i_right + 1] == 2) {
			surrounding_data = surrounding_data | 0b10;
		}
	}


	if (this_board[this_i + 1] == 0) {//if off -> normal
		next_board[this_i + 1] = 1;
	}
	else if (this_board[this_i + 1] == 2 && surrounding_data & 0b1) {//if on && surrounding off -> off
		next_board[this_i + 1] = 0;
	}
	else if (this_board[this_i + 1] == 1 && surrounding_data & 0b10) {//if normal && surrounding on -> on
		next_board[this_i + 1] = 2;
	}


	return *(uint32_t*)&this_board[this_i] != *(uint32_t*)&next_board[this_i];
}

bool Simulationscreen::update_button(uint32_t& i) {
	uint32_t this_i = i * 4;
	uint32_t i_up = (i - board_width) * 4;
	uint32_t i_down = (i + board_width) * 4;
	uint32_t i_left = (i - 1) * 4;
	uint32_t i_right = (i + 1) * 4;

	bool surrounding_on = false;

	//up
	if (this_board[i_up] == BUTTON) {
		if (this_board[i_up + 1] > 1) {
			surrounding_on = true;
		}
	}
	//left
	if (this_board[i_left] == BUTTON) {
		if (this_board[i_left + 1] > 1) {
			surrounding_on = true;
		}
	}
	//right
	if (this_board[i_right] == BUTTON) {
		if (this_board[i_right + 1] > 1) {
			surrounding_on = true;
		}
	}
	//down
	if (this_board[i_down] == BUTTON) {
		if (this_board[i_down + 1] > 1) {
			surrounding_on = true;
		}
	}

	if (this_board[this_i + 1] == 0) {//if off -> neutral
		next_board[this_i + 1] = 1;
	}
	else if (this_board[this_i + 1] == 2) {//if on -> off
		next_board[this_i + 1] = 0;
	}
	else if (surrounding_on) {//if other on -> on
		next_board[this_i + 1] = 2;
	}


	return *(uint32_t*)&this_board[this_i] != *(uint32_t*)&next_board[this_i];
}

bool Simulationscreen::update_switch(uint32_t& i) {
	uint32_t this_i = i * 4;
	uint32_t i_up = (i - board_width) * 4;
	uint32_t i_down = (i + board_width) * 4;
	uint32_t i_left = (i - 1) * 4;
	uint32_t i_right = (i + 1) * 4;

	bool surrounding_on = false;
	bool surrounding_off = false;

	//up
	if (this_board[i_up] == SWITCH) {
		if (this_board[i_up + 1] > 1) {
			surrounding_on = true;
		}else if (this_board[i_up + 1] == 0) {
			surrounding_off = true;
		}
	}
	//left
	if (this_board[i_left] == SWITCH) {
		if (this_board[i_left + 1] > 1) {
			surrounding_on = true;
		}
		else if (this_board[i_left + 1] == 0) {
			surrounding_off = true;
		}
	}
	//right
	if (this_board[i_right] == SWITCH) {
		if (this_board[i_right + 1] > 1) {
			surrounding_on = true;
		}
		else if (this_board[i_right + 1] == 0) {
			surrounding_off = true;
		}
	}
	//down
	if (this_board[i_down] == SWITCH) {
		if (this_board[i_down + 1] > 1) {
			surrounding_on = true;
		}
		else if (this_board[i_down + 1] == 0) {
			surrounding_off = true;
		}
	}

	if (this_board[this_i + 1] == 0) {//if off -> neutral
		next_board[this_i + 1] = 1;
	}
	else if (this_board[this_i + 1] == 2 && surrounding_off) {//if on -> off
		next_board[this_i + 1] = 0;
	}
	else if (surrounding_on) {//if other on -> on
		next_board[this_i + 1] = 2;
	}


	return *(uint32_t*)&this_board[this_i] != *(uint32_t*)&next_board[this_i];
}

bool Simulationscreen::update_not(uint32_t& i) {
	uint32_t this_i = i * 4;
	uint32_t i_up = (i - board_width) * 4;
	uint32_t i_down = (i + board_width) * 4;
	uint32_t i_left = (i - 1) * 4;
	uint32_t i_right = (i + 1) * 4;

	uint8_t surrounding_electricity_count = 0;

	//up
	if (this_board[i_up] > AIR && this_board[i_up] <= BRIDGE && this_board[i_up] != OUTPUT) {
		if (this_board[i_up + (this_board[i_up] == BRIDGE ? 2 : 1)] == 2) {
			surrounding_electricity_count++;
		}
	}

	//down
	if (this_board[i_down] > AIR && this_board[i_down] <= BRIDGE && this_board[i_down] != OUTPUT) {
		if (this_board[i_down + (this_board[i_down] == BRIDGE ? 2 : 1)] == 2) {
			surrounding_electricity_count++;
		}
	}

	//left
	if (this_board[i_left] > AIR && this_board[i_left] <= BRIDGE && this_board[i_left] != OUTPUT) {
		if (this_board[i_left + 1] == 2) {
			surrounding_electricity_count++;

		}
	}

	//right
	if (this_board[i_right] > AIR && this_board[i_right] <= BRIDGE && this_board[i_right] != OUTPUT) {
		if (this_board[i_right + 1] == 2) {
			surrounding_electricity_count++;
		}
	}


	if (surrounding_electricity_count > 0) {
		next_board[this_i + 1] = 0;
	}
	else {
		next_board[this_i + 1] = 2;
	}

	return *(uint32_t*)&this_board[this_i] != *(uint32_t*)&next_board[this_i];
}

bool Simulationscreen::update_or(uint32_t& i) {
	uint32_t this_i = i * 4;
	uint32_t i_up = (i - board_width) * 4;
	uint32_t i_down = (i + board_width) * 4;
	uint32_t i_left = (i - 1) * 4;
	uint32_t i_right = (i + 1) * 4;

	uint8_t surrounding_electricity_count = 0;

	//up
	if (this_board[i_up] > AIR && this_board[i_up] <= BRIDGE && this_board[i_up] != OUTPUT) {
		if (this_board[i_up + (this_board[i_up] == BRIDGE ? 2 : 1)] == 2) {
			surrounding_electricity_count++;
		}
	}

	//down
	if (this_board[i_down] > AIR && this_board[i_down] <= BRIDGE && this_board[i_down] != OUTPUT) {
		if (this_board[i_down + (this_board[i_down] == BRIDGE ? 2 : 1)] == 2) {
			surrounding_electricity_count++;
		}
	}

	//left
	if (this_board[i_left] > AIR && this_board[i_left] <= BRIDGE && this_board[i_left] != OUTPUT) {
		if (this_board[i_left + 1] == 2) {
			surrounding_electricity_count++;

		}
	}

	//right
	if (this_board[i_right] > AIR && this_board[i_right] <= BRIDGE && this_board[i_right] != OUTPUT) {
		if (this_board[i_right + 1] == 2) {
			surrounding_electricity_count++;
		}
	}


	if (surrounding_electricity_count > 0) {
		next_board[this_i + 1] = 2;
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

	uint8_t surrounding_electricity_count = 0;

	//up
	if (this_board[i_up] > AIR && this_board[i_up] <= BRIDGE && this_board[i_up] != OUTPUT) {
		if (this_board[i_up + (this_board[i_up] == BRIDGE ? 2 : 1)] == 2) {
			surrounding_electricity_count++;
		}
	}

	//down
	if (this_board[i_down] > AIR && this_board[i_down] <= BRIDGE && this_board[i_down] != OUTPUT) {
		if (this_board[i_down + (this_board[i_down] == BRIDGE ? 2 : 1)] == 2) {
			surrounding_electricity_count++;
		}
	}

	//left
	if (this_board[i_left] > AIR && this_board[i_left] <= BRIDGE && this_board[i_left] != OUTPUT) {
		if (this_board[i_left + 1] == 2) {
			surrounding_electricity_count++;

		}
	}

	//right
	if (this_board[i_right] > AIR && this_board[i_right] <= BRIDGE && this_board[i_right] != OUTPUT) {
		if (this_board[i_right + 1] == 2) {
			surrounding_electricity_count++;
		}
	}


	if (surrounding_electricity_count == 0) {
		next_board[this_i + 1] = 2;
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

	uint8_t surrounding_electricity_count = 0;

	//up
	if (this_board[i_up] > AIR && this_board[i_up] <= BRIDGE && this_board[i_up] != OUTPUT) {
		if (this_board[i_up + (this_board[i_up] == BRIDGE ? 2 : 1)] == 2) {
			surrounding_electricity_count++;
		}
	}

	//down
	if (this_board[i_down] > AIR && this_board[i_down] <= BRIDGE && this_board[i_down] != OUTPUT) {
		if (this_board[i_down + (this_board[i_down] == BRIDGE ? 2 : 1)] == 2) {
			surrounding_electricity_count++;
		}
	}

	//left
	if (this_board[i_left] > AIR && this_board[i_left] <= BRIDGE && this_board[i_left] != OUTPUT) {
		if (this_board[i_left + 1] == 2) {
			surrounding_electricity_count++;

		}
	}

	//right
	if (this_board[i_right] > AIR && this_board[i_right] <= BRIDGE && this_board[i_right] != OUTPUT) {
		if (this_board[i_right + 1] == 2) {
			surrounding_electricity_count++;
		}
	}


	if (surrounding_electricity_count == 1) {
		next_board[this_i + 1] = 2;
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

	uint8_t surrounding_electricity_count = 0;

	//up
	if (this_board[i_up] > AIR && this_board[i_up] <= BRIDGE && this_board[i_up] != OUTPUT) {
		if (this_board[i_up + (this_board[i_up] == BRIDGE ? 2 : 1)] == 2) {
			surrounding_electricity_count++;
		}
	}

	//down
	if (this_board[i_down] > AIR && this_board[i_down] <= BRIDGE && this_board[i_down] != OUTPUT) {
		if (this_board[i_down + (this_board[i_down] == BRIDGE ? 2 : 1)] == 2) {
			surrounding_electricity_count++;
		}
	}

	//left
	if (this_board[i_left] > AIR && this_board[i_left] <= BRIDGE && this_board[i_left] != OUTPUT) {
		if (this_board[i_left + 1] == 2) {
			surrounding_electricity_count++;

		}
	}

	//right
	if (this_board[i_right] > AIR && this_board[i_right] <= BRIDGE && this_board[i_right] != OUTPUT) {
		if (this_board[i_right + 1] == 2) {
			surrounding_electricity_count++;
		}
	}


	if (surrounding_electricity_count != 1) {
		next_board[this_i + 1] = 2;
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

	uint8_t surrounding_electricity_count = 0;
	uint8_t surrounding_count = 0;

	//up
	if (this_board[i_up] > AIR && this_board[i_up] <= BRIDGE && this_board[i_up] != OUTPUT) {
		if (this_board[i_up + (this_board[i_up] == BRIDGE ? 2 : 1)] == 2) {
			surrounding_electricity_count++;
		}
		surrounding_count++;
	}

	//down
	if (this_board[i_down] > AIR && this_board[i_down] <= BRIDGE && this_board[i_down] != OUTPUT) {
		if (this_board[i_down + (this_board[i_down] == BRIDGE ? 2 : 1)] == 2) {
			surrounding_electricity_count++;
		}
		surrounding_count++;
	}

	//left
	if (this_board[i_left] > AIR && this_board[i_left] <= BRIDGE && this_board[i_left] != OUTPUT) {
		if (this_board[i_left + 1] == 2) {
			surrounding_electricity_count++;
		}
		surrounding_count++;
	}

	//right
	if (this_board[i_right] > AIR && this_board[i_right] <= BRIDGE && this_board[i_right] != OUTPUT) {
		if (this_board[i_right + 1] == 2) {
			surrounding_electricity_count++;
		}
		surrounding_count++;
	}


	if (surrounding_electricity_count == surrounding_count) {
		next_board[this_i + 1] = 2;
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

	uint8_t surrounding_electricity_count = 0;
	uint8_t surrounding_count = 0;

	//up
	if (this_board[i_up] > AIR && this_board[i_up] <= BRIDGE && this_board[i_up] != OUTPUT) {
		if (this_board[i_up + (this_board[i_up] == BRIDGE ? 2 : 1)] == 2) {
			surrounding_electricity_count++;
		}
		surrounding_count++;
	}

	//down
	if (this_board[i_down] > AIR && this_board[i_down] <= BRIDGE && this_board[i_down] != OUTPUT) {
		if (this_board[i_down + (this_board[i_down] == BRIDGE ? 2 : 1)] == 2) {
			surrounding_electricity_count++;
		}
		surrounding_count++;
	}

	//left
	if (this_board[i_left] > AIR && this_board[i_left] <= BRIDGE && this_board[i_left] != OUTPUT) {
		if (this_board[i_left + 1] == 2) {
			surrounding_electricity_count++;
		}
		surrounding_count++;
	}

	//right
	if (this_board[i_right] > AIR && this_board[i_right] <= BRIDGE && this_board[i_right] != OUTPUT) {
		if (this_board[i_right + 1] == 2) {
			surrounding_electricity_count++;
		}
		surrounding_count++;
	}


	if (surrounding_electricity_count != surrounding_count) {
		next_board[this_i + 1] = 2;
	}
	else {
		next_board[this_i + 1] = 0;
	}

	return *(uint32_t*)&this_board[this_i] != *(uint32_t*)&next_board[this_i];
}

bool Simulationscreen::update_clock(uint32_t& i) {
	uint32_t this_i = i * 4;

	int next_value = this_board[this_i + 3];
	next_value -= clock_time_difference;
	next_value = next_value < 0 ? 0 : next_value > 255 ? 255 : next_value;
	if (next_value == 0) {
		next_board[this_i + 1] = 2;
		next_value = this_board[this_i + 2];
	}
	else {
		next_board[this_i + 1] = 0;
	}
	next_board[this_i + 3] = next_value;

	return true;
}

bool Simulationscreen::update_debug(uint32_t& i) {
	uint32_t this_i = i * 4;
	uint32_t i_up = (i - board_width) * 4;
	uint32_t i_down = (i + board_width) * 4;
	uint32_t i_left = (i - 1) * 4;
	uint32_t i_right = (i + 1) * 4;

	uint8_t surrounding_electricity_count = 0;

	//up
	if (this_board[i_up] > AIR && this_board[i_up] <= BRIDGE && this_board[i_up] != OUTPUT) {
		if (this_board[i_up + (this_board[i_up] == BRIDGE ? 2 : 1)] == 2) {
			surrounding_electricity_count++;
		}
	}

	//down
	if (this_board[i_down] > AIR && this_board[i_down] <= BRIDGE && this_board[i_down] != OUTPUT) {
		if (this_board[i_down + (this_board[i_down] == BRIDGE ? 2 : 1)] == 2) {
			surrounding_electricity_count++;
		}
	}

	//left
	if (this_board[i_left] > AIR && this_board[i_left] <= BRIDGE && this_board[i_left] != OUTPUT) {
		if (this_board[i_left + 1] == 2) {
			surrounding_electricity_count++;
		}
	}

	//right
	if (this_board[i_right] > AIR && this_board[i_right] <= BRIDGE && this_board[i_right] != OUTPUT) {
		if (this_board[i_right + 1] == 2) {
			surrounding_electricity_count++;
		}
	}


	if (surrounding_electricity_count > 0) {
		if(!simulation_paused)
			gui.pause_button.func();
		return true;
	}

	return false;
}

