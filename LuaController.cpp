#include "stdafx.h"
#include "LuaController.hpp"
#include "Game.hpp"

Game* caller;

int setTitleText(lua_State *L) {
	
	if (!lua_isstring(L, -1)) {
		throw "Expected: Context";
	}
	
	std::string aName = "field";
	std::string fontName = "minster.ttf";
	Textfield* field = new Textfield(aName, fontName, sf::Vector2f(caller->getStage()->getWidth(), caller->getStage()->getHeight() / 3 ) );
	caller->getStage()->addObject(field);
	return 1;
}
int CLS(lua_State *L){
	if (caller) {
		caller->getStage()->clearScreen();
	}
	return 1;
}
int setLocation(lua_State *L) {
	if (!lua_isstring(L, -1)) {
		throw "Expected: String aName";
	}if (!lua_isnumber(L, -2)) {
		throw "Expected: Number anX";
	}if (!lua_isnumber(L, -3)) {
		throw "Expected: Number anY";
	}
	for (Button* obj : caller->getStage()->getObjects()) {
		if (obj->getName() == lua_tostring(L, -1)) {
			obj->setPosition(sf::Vector2f(lua_tonumber(L, -2), lua_tonumber(L, -3)));
		}
	}
	return 1;
}
int createButton(lua_State *L) {
	std::string givenName;
	std::string fontName;
	float givenX, givenY;
		
	if (!lua_isstring(L, -1)) {
		throw "Expected: String aName";
	}if (!lua_isstring(L, -2)) {
		throw "Expected: String fontName";
	}if (!lua_isnumber(L, -3)) {
		throw "Expected: Number anX";
	}if (!lua_isnumber(L, -4)) {
		throw "Expected: Number anY";
	}
	givenName = lua_tostring(L, -1);
	fontName = lua_tostring(L, -2);
	givenX = lua_tonumber(L, -3);
	givenY = lua_tonumber(L, -4);

	Button* aButton = new Button(givenName, fontName, sf::Vector2f(givenX, givenY));
	caller->getStage()->addObject(aButton);
	return 1;
}
int setButtonText(lua_State *L) {
	if (!lua_isstring(L, -1)) {
		throw "Expected: String aName";
	}
	if (!lua_isstring(L, -2)) {
		throw "Expected: String context";
	}
	for (Button* button : caller->getStage()->getObjects()) {
		if (button->getName() == lua_tostring(L, -1)) {
			button->setString(lua_tostring(L, -2));
		}
	}
	return 1;
}

int gameFunctions(lua_State *L) {
	
	static const luaL_Reg functions[] = {
		{"setTitleText", setTitleText},
		{"CLS", CLS},
		{"setLocation", setLocation},
		{"createButton", createButton},
		{"setButtonText", setButtonText}
	};
	luaL_newlib(L, functions);
	
	return 1;
}


LuaController::LuaController(Game* aGame, std::string aPath):
game(aGame){
	caller = game;
	lua = luaL_newstate();
	luaL_openlibs(lua);
	luaL_loadfile(lua, aPath.c_str());
	//exposeFunctions();
	luaL_requiref(lua, "Game", &gameFunctions, 1);
	//lua_pop(lua, 1);


	if (int errorcode = lua_pcall(lua, 0, LUA_MULTRET, 0)) {
		std::cout << "Error code: " << errorcode << std::endl;
		std::cout << lua_tostring(lua, -1);
	}
	
	lua_getglobal(lua, "story");
	lua_pushnumber(lua, caller->getState());
	if (int errorcode = lua_pcall(lua, 1, LUA_MULTRET, 0)) {
		std::cout << "Error code: " << errorcode << std::endl;
		std::cout << lua_tostring(lua, -1);
	}
	
	lua_close(lua);
}


LuaController::~LuaController() {
}
void LuaController::exposeFunctions() {

	lua_pushcfunction(lua, CLS);
	lua_setglobal(lua, "CLS");
	
	lua_pushcfunction(lua, createButton);
	lua_setglobal(lua, "createButton");

	lua_pushcfunction(lua, setLocation);
	lua_setglobal(lua, "setLocation");

	lua_pushcfunction(lua, setButtonText);
	lua_setglobal(lua, "setButtonText");
	
	lua_pushcfunction(lua, setTitleText);
	lua_setglobal(lua, "setTitleText");
}