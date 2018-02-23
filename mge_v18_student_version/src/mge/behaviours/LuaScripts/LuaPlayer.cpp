#include "mge\behaviours\LuaScripts\LuaPlayer.hpp"
#include <string>
#include <iostream>
#include "mge\config.hpp"
#include "SFML\Window\Keyboard.hpp"
#include "glm.hpp";
#include "mge\core\GameObject.hpp"

using namespace glm;
using namespace sf;

LuaPlayer::LuaPlayer(): LuaScript("Player.lua")
{

}

LuaPlayer::~LuaPlayer()
{

}

void LuaPlayer::luaStart()
{

}

void LuaPlayer::update(float pStep)
{
	callLuaUpdate("step", pStep);
	callLuaUpdate("lastStep", pStep);

	vec3 delta = vec3(0, 0, 0);
	delta.x = Keyboard::isKeyPressed(Keyboard::Right) - Keyboard::isKeyPressed(Keyboard::Left);
	delta.y = Keyboard::isKeyPressed(Keyboard::Up) - Keyboard::isKeyPressed(Keyboard::Down);
	delta.z = Keyboard::isKeyPressed(Keyboard::Space);
	_owner->translate(handleMovement(delta) * pStep);
	if (Keyboard::isKeyPressed(Keyboard::Z)) sendShoot();
}

vec3 LuaPlayer::handleMovement(vec3 delta)
{
	settupFunction("move");
	pushNumber(delta.x);
	pushNumber(delta.y);
	pushNumber(delta.z);
	callFunction(3,2);
	vec3 movement = vec3();
	movement.x = getNumber();
	movement.y = getNumber();
	return movement;
}

void LuaPlayer::sendShoot()
{

}