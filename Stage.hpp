#pragma once
#include "Button.hpp"
#include <list>

class Stage
{
public:
	Stage(sf::Color backgroundColor = sf::Color::Black, float aWidth = 800.0f, float aHeight = 600.0f);
	virtual ~Stage();
	std::list<Button*> getObjects();
	void addObject(Button* aButton);
	void removeObject(Button* aButton);
	void setBackground(std::string aPath);
	float getHeight();
	float getWidth();
	sf::Sprite draw();
	void clearScreen();
private:
	std::list<Button*> gameObjects;
	sf::RenderTexture texture;
	float width;
	float height;
};

