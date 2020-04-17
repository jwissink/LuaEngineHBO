#pragma once
#include "Stage.hpp"
#include "Button.hpp"
#include "Game.hpp"

class Core
{
public:
	Core();
	virtual ~Core();
	bool run();
	void build();
private:
	void update();
	void draw();
private:
	sf::RenderWindow* window;
	sf::Event event;
	Stage* stage;
	Game* game;

};

