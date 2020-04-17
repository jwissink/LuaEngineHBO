#pragma once
#include "Stage.hpp"
#include "Button.hpp"
#include "Textfield.hpp"
#include "LuaController.hpp"

class Game
{
public:
	Game(Stage* aStage);
	virtual ~Game();
	void update();
	bool isRunning();
	void endGame();
	void clearScene();
	void startCampaign();
	Stage* getStage();
	int getState();
private:
	Stage* stage;
	int sceneState;
	int gameState;
	void setStandardParams(Button* aButton);
	Textfield* textField;
	bool running;
	LuaController* luaController;
	enum sceneStates {
		BUILD,
		RUN
	};
};

