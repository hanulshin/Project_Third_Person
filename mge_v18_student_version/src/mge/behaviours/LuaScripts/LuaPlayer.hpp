#ifndef LUAPLAYER_HPP
#define LUAPLAYER_HPP

#include "mge\behaviours\LuaScripts\LuaScript.hpp"
#include "glm.hpp"

class LuaPlayer : public LuaScript
{
public:
	LuaPlayer();
	virtual ~LuaPlayer();

	virtual void luaStart();
	virtual void update(float pStep);
	virtual AbstractBehaviour* copy();

protected:

private:
	glm::vec3 handleMovement(glm::vec3 delta);
	void shoot(glm::vec2 delta);
	void equipWeapon(std::string weapon);

	//For Lua
	static int fireBullet(lua_State * state);
};

#endif // LUAMOVE_HPP;