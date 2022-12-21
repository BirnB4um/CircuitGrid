#define CONSOLE_APP 1

#if CONSOLE_APP 1
#pragma comment(linker,"/SUBSYSTEM:CONSOLE")
#else
#pragma comment(linker,"/SUBSYSTEM:WINDOWS")
#endif

#include <iostream>
#include "App/Application.h"
using namespace std;

bool is_number(char* str)
{
	std::cout << str << std::endl;
	int pos = 0;
	
	while (str[pos] != 0) {
		if (!isdigit(str[pos])) {
			return false;
		}
		pos++;
	}
	return true;
}

int main(int argc, char** argv) {


	board_width = 2000;
	board_height = 2000;

	//for (int i = 0; i < argc; i++) {
	//	if (argv[i][0] == "-"[0]) {//command
	//		int len = strlen(argv[i]);
	//		if (len > 1) {
	//			std::cout << argv[i] << std::endl;
	//			if (argv[i][1] == "w"[0]) {//set width
	//				if (is_number(&(argv[i][1]))) {
	//					int x = stoi(&(argv[i][1]));
	//					std::cout << "width: " << x << std::endl;
	//					board_width = x;
	//				}
	//			}
	//			else if (argv[i][1] == "h"[0]) {//set height
	//				if (is_number(&(argv[i][1]))) {
	//					int x = stoi(&(argv[i][1]));
	//					std::cout << "height: " << x << std::endl;
	//					board_height = x;
	//				}
	//			}
	//		}
	//	}
	//}

	if (argc == 3) {
		if (is_number(argv[1])) {
			board_width = std::stoi(argv[1]);
		}
		if (is_number(argv[2])) {
			board_height = std::stoi(argv[2]);
		}
	}


	Application *app = new Application();
	app->init();
	app->run();

	return 0;
}