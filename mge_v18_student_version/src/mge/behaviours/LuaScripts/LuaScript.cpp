#include "mge\behaviours\LuaScripts\LuaScript.hpp"
#include <LuaJIT-2.0.5\src\lua.hpp>
#include <string>
#include <cmath>
#include <iostream>
#include "mge\config.hpp"

using namespace std;

LuaScript::LuaScript(string fileName): _file(fileName)
{

}

LuaScript::~LuaScript()
{

}

void LuaScript::start() 
{
	state = luaL_newstate();
	luaL_openlibs(state);
	openFile(_file);
	luaStart();
}

void LuaScript::openFile(string fileName) 
{
	_file = fileName;
	if (luaL_dofile(state, (config::MGE_SCRIPTS_PATH+_file).c_str()) != 0) {
		std::string error = lua_tostring(state, -1);
		printf("Could not do file: %s\n", error.c_str());
	}

	settupFunction("start");
	callFunction();
}

void LuaScript::settupFunction(string funcName)
{
	lua_getglobal(state, funcName.c_str());
	if (!lua_isfunction(state, -1)) {
		printf(("Error: [" + funcName + "] is not a function.").c_str());
	}
}

void LuaScript::callLuaUpdate(string pName, float pStep)
{
	settupFunction(pName);
	pushNumber(pStep);
	callFunction(1, 0);
}

void LuaScript::callFunction(int args, int results)
{
	if (lua_pcall(state, args, results, 0) != 0) { // call init()
		printf("Lua call error %s\n", lua_tostring(state, -1));
	}
}

void LuaScript::pushInt(int num) {
	lua_pushinteger(state, num);
}

void LuaScript::pushNumber(float num) {
	lua_pushnumber(state, num);
}

void LuaScript::pushString(string str) {
	lua_pushstring(state, str.c_str());
}

void LuaScript::pushBool(bool b) {
	lua_pushboolean(state, b);
}

void LuaScript::pushObject(void* obj) {
	lua_pushlightuserdata(state, obj);
}


int LuaScript::getInt() {
	return lua_tointeger(state, lua_gettop(state));
}

bool LuaScript::getBool() {
	return lua_toboolean(state, lua_gettop(state));
}

float LuaScript::getNumber() {
	return lua_tonumber(state, lua_gettop(state));
}

string LuaScript::getString() {
	return lua_tostring(state, lua_gettop(state));
}