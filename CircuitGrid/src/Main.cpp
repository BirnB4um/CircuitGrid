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

bool is_number(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

int main(int argc, char** argv) {

	//for (int i = 0; i < argc; i++) {
	//	if (argv[i][0] == "-"[0]) {//command
	//		int len = strlen(argv[i]);
	//		if (len > 1) {
	//			if (argv[i][1] == "w"[0]) {
	//				if (is_number(&argv[i][1])) {
	//					int x = stoi(&argv[i][1]);
	//					board_width = x;
	//				}
	//			}else if (argv[i][1] == "h"[0]) {
	//				if (is_number(&argv[i][1])) {
	//					int x = stoi(&argv[i][1]);
	//					board_height = x;
	//				}
	//			}
	//		}
	//	}
	//}


	board_width = 500;
	board_height = 500;

	Application *app = new Application();
	app->init();
	app->run();

	return 0;
}