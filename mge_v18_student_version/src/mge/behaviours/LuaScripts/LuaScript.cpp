#include "mge\behaviours\LuaScripts\LuaScript.hpp"
#include <LuaJIT-2.0.5\src\lua.hpp>
#include <string>
#include <cmath>
#include <iostream>
#include <string>
#include "glm.hpp"
#include "mge\config.hpp"
#include "mge\core\AbstractGame.hpp"

using namespace std;

map<string, GameObject*> LuaScript::quickFind = map<string, GameObject*>();

//LUA functions
int LuaScript::spawnObject(lua_State* state) {
	string name = lua_tostring(state, 1);
	string parent = lua_tostring(state, 2);
	float x = (float)lua_tonumber(state, 3);
	float y = (float)lua_tonumber(state, 4);
	float z = (float)lua_tonumber(state, 5);

	GameObject* p = nullptr;
	auto search = quickFind.find(parent);
	if (search != quickFind.end()) {
		if (!quickFind[name]) {
			quickFind.erase(name);
		}
		else {
			p = quickFind[name];
		}
	}
	
	if(p == nullptr){
		p = AbstractGame::Find(name);
		if (p != nullptr) {
			quickFind.insert(pair<string, GameObject*>(name, p));
		}
	}
	AbstractGame::spawnObject(name, glm::vec3(x, y, z), p);
	return 0;
}

//Class

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
	registerFunction("spawn", spawnObject);
	luaStart();
}

void LuaScript::openFile(string fileName) 
{
	_file = fileName;
	if (luaL_dofile(state, (config::MGE_SCRIPTS_PATH + fileName).c_str()) != 0) {
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


int LuaScript::getInt(int i) {
	int a = getIndex(i);
	int I = lua_tointeger(state, a);
	remove(a);
	return I;
}

bool LuaScript::getBool(int i) {
	int a = getIndex(i);
	bool b = lua_toboolean(state, a);
	remove(a);
	return b;
}

float LuaScript::getNumber(int i) {
	int a = getIndex(i);
	float f = (float)lua_tonumber(state, a);
	remove(a);
	return f;
}

string LuaScript::getString(int i) {
	int a = getIndex(i);
	string s = lua_tostring(state, a);
	remove(a);
	return s;
}

void LuaScript::remove(int i){
	lua_remove(state, getIndex(i));
}

int LuaScript::getIndex(int i) {
	if (i == -1) return lua_gettop(state);
	return i;
}

void LuaScript::registerFunction(string name, lua_CFunction func) {
	lua_register(state, name.c_str(), func);
}