#include "stdafx.h"
#include "Game.hpp"

Game* pointer = nullptr;
void buttonHandler(std::string buttonName) {
	if (pointer) {
		if (buttonName == "exit") {
			pointer->endGame();
		} else if (buttonName == "start") {
			pointer->startCampaign();
		} 
	}
}
Game::Game(Stage* aStage)
:stage(aStage), gameState(-1), running(true){
	pointer = this;
	luaController = new LuaController(this);

	sceneState = sceneStates::BUILD;
	stage->setBackground("Textures/evilMansion.JPG");
	
	
}

Stage* Game::getStage() {
	return stage;
}

Game::~Game() {
}

int Game::getState() {
	return gameState;
}
void Game::update() {
	switch (gameState) {
	case -1:
		if (sceneState == sceneStates::BUILD) {
			//clearScene();
			textField = new Textfield("textfield", "minster.ttf", { stage->getWidth(), stage->getHeight() / 3 });
			textField->setPosition(1, 1);
			textField->setString("Welcome to the house of Lord Vamperi!\nIt has been infected by a trojan horse.\nIn this sure as hell entisening story\n you will question your very existence!");
			setStandardParams(textField);
			stage->addObject(textField);
			
			
			Button* startButton = new Button("start", "minster.ttf", { 400.0f, 80.0f });
			startButton->setString("Start");
			startButton->setPosition({ stage->getWidth() / 2 - startButton->getSize().x / 2, stage->getHeight() / 2 - 80 });
			startButton->setTriggerFunction(buttonHandler);
			setStandardParams(startButton);
			stage->addObject(startButton);

			Button* exitButton = new Button("exit", "minster.ttf", { 400.0f, 80.0f });
			exitButton->setString("Exit");
			exitButton->setPosition({ stage->getWidth() / 2 - startButton->getSize().x / 2, stage->getHeight() / 2 + 80 });
			exitButton->setTriggerFunction(buttonHandler);

			setStandardParams(exitButton);
			stage->addObject(exitButton);


			sceneState = sceneStates::RUN;
		} else {
			//runtime for movement etc.
		}
		break;
	case 0: //we enter the scripting state
		if (sceneState == sceneStates::BUILD) {
			//clearScene();
			
		} else {

		}
		break;
	default:
		if (sceneState == sceneStates::BUILD) {
			clearScene();
		} else {

		}
		break;
	}
}
void Game::clearScene() {
	for (Button* obj : stage->getObjects()) {
		stage->removeObject(obj);
	}
}
bool Game::isRunning() {
	return running;
}
void Game::endGame() {
	running = false;
}
void Game::startCampaign() {
	gameState = 0;
	sceneState = sceneStates::BUILD;
}
void Game::setStandardParams(Button * aButton) {
	aButton->setBackgroundColor(sf::Color(255, 250, 250, 150));
	aButton->setTextColor(sf::Color::Red);
	aButton->setOverBackgroundColor(sf::Color::White);
	aButton->setOverTextColor(sf::Color::Red);
}
