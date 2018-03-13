#pragma once
#include "mge/behaviours/LuaScripts/LuaScript.hpp"
#include <string>

class EnemySpawner : public LuaScript {
public:
	EnemySpawner(std::string tag);
	~EnemySpawner();
	virtual AbstractBehaviour* copy();
	virtual void luaStart();
	virtual void update(float pStep);
private:
};