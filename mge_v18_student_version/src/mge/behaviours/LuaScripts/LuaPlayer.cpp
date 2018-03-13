#include "mge\behaviours\LuaScripts\LuaPlayer.hpp"
#include "mge\behaviours\BulletBehaviour.hpp"
#include <map>
#include <string>
#include <iostream>
#include "mge\config.hpp"
#include "SFML\Window\Keyboard.hpp"
#include "glm.hpp"
#include "mge\core\GameObject.hpp"
#include "mge\core\AbstractGame.hpp"
#include "mge\core\World.hpp"
#include <string>
#include "LuaJIT-2.0.5\src\lua.hpp"

using namespace glm;
//Class

LuaPlayer::LuaPlayer(std::string pTag) : LuaScript("Player.lua", pTag)
{

}

LuaPlayer::~LuaPlayer()
{

}

void LuaPlayer::luaStart()
{
	registerFunction("getKey", getKey);
	mapInput();
}

void LuaPlayer::update(float pStep)
{
	callLuaUpdate("step", pStep);
	callLuaUpdate("lastStep", pStep);

	vec3 delta = vec3(0, 0, 0);
	glm::vec3 currentPos = _owner->getWorldPosition();
	//std::cout <<"Player x position: " << currentPos.x << std::endl;
	if (currentPos.x + pStep>-7.0f && currentPos.x + pStep<5.0f)
		delta.x = Keyboard::isKeyPressed(Keyboard::Right) - Keyboard::isKeyPressed(Keyboard::Left);
	else
		delta.x = glm::normalize(-currentPos.x);
	delta.y = Keyboard::isKeyPressed(Keyboard::Up) - Keyboard::isKeyPressed(Keyboard::Down);
	delta.z = Keyboard::isKeyPressed(Keyboard::Space);
	inputDelta(delta);
	if (Keyboard::isKeyPressed(Keyboard::Z)) shoot(delta);
}

AbstractBehaviour* LuaPlayer::copy() {
	return new LuaPlayer(_owner->getActorTag() + "c");
}

map<string, sf::Keyboard::Key> LuaPlayer::inputMap = map<string, sf::Keyboard::Key>();

void LuaPlayer::mapKey(sf::Keyboard::Key key, string luaKey) {
	inputMap.insert(std::pair<string, sf::Keyboard::Key>(luaKey, key));
}

void LuaPlayer::mapInput() {
	using namespace sf;
	mapKey(Keyboard::Up, "up");
	mapKey(Keyboard::Down, "down");
	mapKey(Keyboard::Right, "right");
	mapKey(Keyboard::Left, "left");
	mapKey(Keyboard::Space, "space");
	mapKey(Keyboard::Z, "z");
}

int LuaPlayer::getKey(lua_State * state) {
	string input = lua_tostring(state, 1);
	if (inputMap.count(input) == 0) {
		std::string errorLog = "No input with name [" + input + "] was found";
		return luaL_error(state, errorLog.c_str());
	}
	lua_pushboolean(state, sf::Keyboard::isKeyPressed(inputMap[input]));
	return 1;
}