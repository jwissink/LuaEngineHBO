#include "stdafx.h"
#include "Stage.hpp"


Stage::Stage(sf::Color backgroundColor, float aWidth, float aHeight) 
:width(aWidth), height(aHeight){
	texture.create((int)width, (int)height);
	texture.clear(backgroundColor);
	texture.display();
}


Stage::~Stage() {
}


std::list<Button*> Stage::getObjects() {
	return gameObjects;
}

void Stage::clearScreen() {
	for (Button* obj : gameObjects) {
		gameObjects.remove(obj);
		delete obj;
	}
}
void Stage::addObject(Button* aButton) {
	gameObjects.push_back(aButton);
}

void Stage::removeObject(Button* aButton) {
	gameObjects.remove(aButton);
	delete aButton;
}

void Stage::setBackground(std::string aPath) {
	sf::Texture tex;
	tex.loadFromFile(aPath);
	sf::Sprite imageHolder(tex);
	texture.clear();
	texture.draw(imageHolder);
	texture.display();
}

float Stage::getHeight() {
	return height;
}

float Stage::getWidth() {
	return width;
}

sf::Sprite Stage::draw() {
	sf::Sprite sprite(texture.getTexture());
	return sprite;
}
