#include "Application.h"

Application::Application() {
}

Application::~Application() {
	delete GUI_Item::gui_texture;
	delete font;
}

void Application::init() {
	//load textures
	GUI_Item::gui_texture = new sf::Texture;
	GUI_Item::gui_texture->loadFromFile("res/images/gui_texture.png");

	//load Font
	font = new sf::Font();
	if (!font->loadFromFile("res/fonts/arial.ttf")) {
		std::cout << "ERROR: couldnt load font 'arial.ttf'" << std::endl;
	}

	screen_id = HOMESCREEN;
	closing = false;
	TITLE = "Circuit-Grid";
	WINDOWED_WIDTH = 800;
	WINDOWED_HEIGHT = 600;
	FPS = 40;
	FOCUS = true;
	update_all = true;
	FULLSCREEN_WIDTH = sf::VideoMode::getFullscreenModes()[0].width;
	FULLSCREEN_HEIGHT = sf::VideoMode::getFullscreenModes()[0].height;
	create_window(WINDOWED_WIDTH, WINDOWED_HEIGHT, false, FPS, TITLE);

	//init screens
	homescreen.init();
	simulationscreen.init();
	settingsscreen.init();

	on_resize();
}

void Application::create_window(unsigned int width, unsigned int height, bool fullscreen, int fps, std::string title)
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 0;

	TITLE = title;
	FPS = fps;
	FULLSCREEN = fullscreen;
	if (FULLSCREEN) {
		window.create(sf::VideoMode::getFullscreenModes()[0], TITLE, sf::Style::Fullscreen, settings);
	}
	else {
		window.create(sf::VideoMode(width, height), TITLE, sf::Style::Close | sf::Style::Resize, settings);
	}
	window.setFramerateLimit(fps);
	window.setVerticalSyncEnabled(true);

	on_resize();
}

void Application::on_closing() {
	closing = true;

	homescreen.on_closing();
	simulationscreen.on_closing();
	settingsscreen.on_closing();

	window.close();
}

void Application::on_resize() {
	SCREEN_WIDTH = window.getSize().x;
	SCREEN_HEIGHT = window.getSize().y;
	SCREEN_RATIO = float(SCREEN_WIDTH) / float(SCREEN_HEIGHT);

	normal_view.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	normal_view.setCenter(float(SCREEN_WIDTH) / 2, float(SCREEN_HEIGHT) / 2);

	homescreen.resize();
	simulationscreen.resize();
	settingsscreen.resize();
}

void Application::handle_events() {
	while (window.pollEvent(sf_event)) {

		//gained focus
		if (sf_event.type == sf::Event::GainedFocus	) {
			FOCUS = true;
		}
		//lost focus
		else if (sf_event.type == sf::Event::LostFocus) {
			FOCUS = false;
			update_all = false;
		}
		//close window
		else if (sf_event.type == sf::Event::Closed) {
			on_closing();
			break;
		}
		//resize window event
		else if (sf_event.type == sf::Event::Resized) {
			on_resize();
		}
		else if (sf_event.type == sf::Event::KeyReleased) {
			//fullscreen toggle
			if (sf_event.key.code == sf::Keyboard::F11) {
				create_window(WINDOWED_WIDTH, WINDOWED_HEIGHT, !FULLSCREEN, FPS, TITLE);
			}
		}
		else if (sf_event.type == sf::Event::MouseMoved) {
		}


		if (!update_all) {
			if (sf_event.type == sf::Event::MouseButtonReleased) {
				update_all = true;
			}
			continue;
		}

		// ===== SCREENS =====
		if (screen_id == HOMESCREEN) {
			homescreen.handle_events(sf_event);
		}
		else if (screen_id == SIMULATION) {
			simulationscreen.handle_events(sf_event);
		}
		else if (screen_id == SETTINGS) {
			settingsscreen.handle_events(sf_event);
		}
	}
}

void Application::update() {
	window_mouse = sf::Mouse::getPosition(window);//update mouse position

	if (screen_id == HOMESCREEN) {
		homescreen.update();
	}
	else if (screen_id == SIMULATION) {
		simulationscreen.update();
	}
	else if (screen_id == SETTINGS) {
		settingsscreen.update();
	}
}

void Application::draw() {
	window.clear();
	window.setView(normal_view);

	if (screen_id == HOMESCREEN) {
		homescreen.render(window);
	}
	else if (screen_id == SIMULATION) {
		simulationscreen.render(window);
	}
	else if (screen_id == SETTINGS) {
		settingsscreen.render(window);
	}

	window.display();
}

void Application::run() {
	while (window.isOpen())
	{
		handle_events();

		if (update_all) {
			update();
		}

		draw();
	}
}