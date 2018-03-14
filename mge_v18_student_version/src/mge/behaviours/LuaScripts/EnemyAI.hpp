#include "mge/behaviours/LuaScripts/LuaScript.hpp"
#include <string>
#include <vector>

class EnemyAI : public LuaScript
{
public:
	EnemyAI(std::string tag, std::string ai);
	~EnemyAI();
	virtual AbstractBehaviour* copy();
	virtual void earlyStart();
	virtual void lateStart();
	virtual void update(float pStep);
	int getDamage();
	void HitPlayer();
	static std::vector<EnemyAI*>* getEnemies();
private:
	std::string _ai;
	static std::vector<EnemyAI*>* enemies;
};