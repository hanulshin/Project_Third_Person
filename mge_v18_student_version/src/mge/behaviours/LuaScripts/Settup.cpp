#include "mge\behaviours\LuaScripts\Settup.hpp"
#include "mge\behaviours\LuaScripts\LuaScript.hpp"
#include "mge\behaviours\AbstractBehaviour.hpp"
#include "mge\core\GameObject.hpp"
#include "mge/core/Prefab.hpp"
#include <string>

Settup::Settup(std::string tag) : LuaScript("Settup.lua", tag) {

}

Settup::~Settup() {

}

void Settup::earlyStart() {
	printf("Setting Up Game!");
	registerFunction("loadColor", loadColor);
	registerFunction("loadMesh", loadMesh);
	registerFunction("loadTexture", loadTexture);
}

void Settup::lateStart() {

}

void Settup::update(float pStep) {
	callLuaUpdate("step", pStep);
}

AbstractBehaviour* Settup::copy() {
	return new Settup(_owner->getActorTag() + "c");
}

int Settup::loadTexture(lua_State * state) {
	string fileName = lua_tostring(state, 1);
	string fileType = lua_tostring(state, 2);
	bool success = Prefab::instance()->loadTexture(fileName, fileType);
	lua_pushboolean(state, success);
	return 1;
}

int Settup::loadMesh(lua_State * state) {
	string fileName = lua_tostring(state, 1);
	string fileType = lua_tostring(state, 2);
	bool success = Prefab::instance()->loadMesh(fileName, fileType);
	lua_pushboolean(state, success);
	return 1;
}


int Settup::loadColor(lua_State * state) {
	string key = string(lua_tostring(state, 1));
	glm::vec4 color = glm::vec4(lua_tonumber(state, 2), lua_tonumber(state, 3), lua_tonumber(state, 4), lua_tonumber(state, 5));
	bool success = Prefab::instance()->setColor(key, color);
	lua_pushboolean(state, success);
	return 1;
}