#include "mge/behaviours/LuaScripts/EnemyAI.hpp"
#include "mge/behaviours/LuaScripts/LuaScript.hpp"
#include "mge/core/AbstractGame.hpp"
#include "mge/core/GameObject.hpp"
#include <string>
#include <vector>

EnemyAI::EnemyAI(std::string pTag, std::string ai): LuaScript("Enemy.lua", pTag), _ai(ai){
	enemies->push_back(this);
}

EnemyAI::~EnemyAI() {
	enemies->erase(std::remove(enemies->begin(), enemies->end(), this), enemies->end());
}

std::vector<EnemyAI*>* EnemyAI::enemies = new std::vector<EnemyAI*>();
std::vector<EnemyAI*>* EnemyAI::getEnemies() {
	return enemies;
}

void EnemyAI::earlyStart() {

}

void EnemyAI::lateStart()
{
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

int EnemyAI::getDamage() {
	settupFunction("getDamage");
	callFunction(0, 1);
	return toInt();
}

void EnemyAI::HitPlayer() {
	settupFunction("onHitPlayer");
	callFunction();
}