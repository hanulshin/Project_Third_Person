#include "mge/behaviours/LuaScripts/EnemyAI.hpp"
#include "mge/behaviours/LuaScripts/LuaScript.hpp"
#include "mge/core/AbstractGame.hpp"
#include "mge/core/GameObject.hpp"
#include <string>

EnemyAI::EnemyAI(std::string pTag, std::string ai): LuaScript("Enemy.lua", pTag), _ai(ai){

}

EnemyAI::~EnemyAI() {

}

void EnemyAI::luaStart() {
	settupFunction("settupAI");
	pushString(_ai);
	callFunction(1);
}

void EnemyAI::update(float pStep) {
	callLuaUpdate("step", pStep);
}

AbstractBehaviour* EnemyAI::copy() {
	return(new EnemyAI(_owner->getActorTag() + "c", _ai));
}