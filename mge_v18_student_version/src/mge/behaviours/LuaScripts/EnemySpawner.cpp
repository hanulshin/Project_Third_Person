#include "mge/behaviours/LuaScripts/LuaScript.hpp"
#include "mge/behaviours/LuaScripts/EnemySpawner.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Mesh.hpp"
#include <string>

EnemySpawner::EnemySpawner(std::string pTag) : LuaScript("Spawner.lua", pTag){

}

EnemySpawner::~EnemySpawner() {

}

AbstractBehaviour* EnemySpawner::copy() {
	return new EnemySpawner(_owner->getActorTag() + "c");
}

void EnemySpawner::luaStart() {

}

void EnemySpawner::update(float pStep) {
	callLuaUpdate("step", pStep);
}

