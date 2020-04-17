#include "stdafx.h"
#include "Core.hpp"


Core::Core() {
}


Core::~Core() {
}

void Core::build() {
	stage = new Stage(sf::Color::Red);
	game = new Game(stage);
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Trojan.horse/keylogger ;)");
}

void Core::update() {
	game->update();
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window->close();
			game->endGame();
		}
		for (Button* obj : stage->getObjects()) {
			obj->events(event);
		}	
	}
}
void Core::draw() {
	window->clear();
	
	window->draw(stage->draw());
	for (Button* buttons : stage->getObjects()) {
		buttons->handler(*window);
		window->draw(*buttons);
	}
	window->display();
}
bool Core::run() {
	update();
	draw();
	return game->isRunning();
}

