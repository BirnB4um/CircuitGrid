#define CONSOLE_APP 1

#if CONSOLE_APP 1
#pragma comment(linker,"/SUBSYSTEM:CONSOLE")
#else
#pragma comment(linker,"/SUBSYSTEM:WINDOWS")
#endif

#define VERSION 0.1

#include <SFML/Graphics.hpp>
#include <iostream>
#include "App/Application.h"
#include "Tools/Timer.h"
using namespace std;

int main() {

	Application app;
	app.init();
	app.run();

	return 0;
}