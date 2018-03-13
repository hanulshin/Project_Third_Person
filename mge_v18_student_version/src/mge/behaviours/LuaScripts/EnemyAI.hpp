#include "mge/behaviours/LuaScripts/LuaScript.hpp"
#include <string>

class EnemyAI : public LuaScript
{
public:
	EnemyAI(std::string tag, std::string ai);
	~EnemyAI();
	virtual AbstractBehaviour* copy();
	virtual void luaStart();
	virtual void update(float pStep);
private:
	std::string _ai;
};