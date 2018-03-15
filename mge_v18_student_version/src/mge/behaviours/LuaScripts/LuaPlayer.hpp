#ifndef LUAPLAYER_HPP
#define LUAPLAYER_HPP

#include "mge\behaviours\LuaScripts\LuaScript.hpp"
#include "glm.hpp"
#include <string>

enum AnimationStates
{
	IDLE, MOVING_LEFT, MOVING_RIGHT, SHOOTING_IDLE, SHOOTING_LEFT, SHOOTING_RIGHT
};

class LuaPlayer : public LuaScript
{
public:
	LuaPlayer(std::string pTag);
	virtual ~LuaPlayer();

	virtual void earlyStart();
	virtual void lateStart();
	virtual void update(float pStep);
	virtual AbstractBehaviour* copy();

	int getHealth();
private:
	static void mapKey(sf::Keyboard::Key key, string luaKey);
	static map<string, sf::Keyboard::Key> inputMap;
	void mapInput();
	static int getKey(lua_State * state);
	void Animate(AnimationStates& animeState, float pStep);
};

#endif // LUAMOVE_HPP;