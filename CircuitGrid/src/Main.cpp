#define CONSOLE_APP 1

#if CONSOLE_APP 1
#pragma comment(linker,"/SUBSYSTEM:CONSOLE")
#else
#pragma comment(linker,"/SUBSYSTEM:WINDOWS")
#endif

#include <SFML/Graphics.hpp>
#include <iostream>
#include "App/Application.h"
#include "Tools/Timer.h"
using namespace std;

int main() {

	//Timer timer;
	//int w = 4096;
	//int h = 4096;
	//sf::Texture texture;
	//texture.create(w, h);
	//uint8_t* data = new uint8_t[w * h * 4];
	//while (true) {
	//	cin.get();
	//	memset(data, rand() % 255, w * h * 4);
	//	timer.start();
	//	texture.update(data);
	//	timer.stop();
	//	cout << timer.get_duration() << endl;
	//}
	//cout << "end" << endl;
	//cin.get();
	//return 0;

	Application app;
	app.init();
	app.run();

	return 0;
}