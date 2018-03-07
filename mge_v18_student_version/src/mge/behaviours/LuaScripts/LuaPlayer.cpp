#include "mge\behaviours\LuaScripts\LuaPlayer.hpp"
#include "mge\behaviours\BulletBehaviour.hpp"
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
//LUA Functions

int LuaPlayer::fireBullet(lua_State * state) {
	string bulletTemplate = "_bullet";
	string name = lua_tostring(state, 1) + bulletTemplate;
	vec2 pos = vec2(lua_tonumber(state, 2), lua_tonumber(state, 3));
	vec2 vel = vec2(lua_tonumber(state, 4), lua_tonumber(state, 5));
	int bDamage = lua_tointeger(state, 6);
	float bSpeed = (float)lua_tonumber(state, 7);
	float pTime = (float)lua_tonumber(state, 8);

	//printf((name + " fires!").c_str());
	//std::cout<<"[\""<<name<<"\" - p["<<pos.x<<", "<<pos.y<<"] d["<<vel.x<<", "<<vel.y<<"] - d:"<<bDamage<<" s:"<<bSpeed<<" t:"<<pTime<<"]"<<std::endl;
	vel *= bSpeed;

	GameObject* b = GameObject::getActor(bulletTemplate)->copy();
	b->setLocalPosition(GameObject::getActor("player")->getLocalPosition());
	b->setBehaviour(new BulletBehaviour(vel, bDamage, pTime));
	GameObject::getActor(config::CURRENT_SCENE)->add(b);
	return 0;
}
//Class

LuaPlayer::LuaPlayer() : LuaScript("Player.lua")
{

}

LuaPlayer::~LuaPlayer()
{

}

void LuaPlayer::luaStart()
{
	registerFunction("fire", fireBullet);
}

void LuaPlayer::update(float pStep)
{
	using namespace sf;
	callLuaUpdate("step", pStep);
	callLuaUpdate("lastStep", pStep);

	vec3 delta = vec3(0, 0, 0);
	delta.x = Keyboard::isKeyPressed(Keyboard::Right) - Keyboard::isKeyPressed(Keyboard::Left);
	delta.y = Keyboard::isKeyPressed(Keyboard::Up) - Keyboard::isKeyPressed(Keyboard::Down);
	delta.z = Keyboard::isKeyPressed(Keyboard::Space);
	inputDelta(delta);
	if (Keyboard::isKeyPressed(Keyboard::Z)) shoot(delta);
}

void LuaPlayer::inputDelta(vec3 delta)
{
	settupFunction("move");
	pushNumber(delta.x);
	pushNumber(delta.y);
	pushNumber(delta.z);
	callFunction(3);
}

void LuaPlayer::equipWeapon(string weapon)
{
	settupFunction("equip");
	pushString(weapon);
	callFunction(1);
}

void LuaPlayer::shoot(vec2 delta)
{
	settupFunction("shoot");
	vec3 playerPos = _owner->getLocalPosition();
	pushNumber(playerPos.x);
	pushNumber(playerPos.y);
	callFunction(2);
}

AbstractBehaviour* LuaPlayer::copy() {
	return new LuaPlayer();
}