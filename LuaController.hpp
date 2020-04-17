#pragma once
#include "Button.hpp"
#include "Textfield.hpp"
#include "Stage.hpp"

class Game;

typedef void(*function)(std::string aName);
class LuaController
{
public:
	LuaController(Game* aGame, std::string aPath = "script.lua");
	virtual ~LuaController();
	//swig.exposeFunctions();

private:
	lua_State* lua;
	void exposeFunctions();
	Game* game;
};

