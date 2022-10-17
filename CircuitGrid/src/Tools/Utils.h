#pragma once

struct Utils {
	//template<class T>

	static float constrain(float number, float min, float max) {
		return number < min ? min : number > max ? max : number;
	}

	//returns true if intersects
	static bool point_vs_rect(float px, float py, float r_x, float r_y, float r_w, float r_h) {
		return px > r_x && px < r_x + r_w && py>r_y && py < r_y + r_h;
	}
};