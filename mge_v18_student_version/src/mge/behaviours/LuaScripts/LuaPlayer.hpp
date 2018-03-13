#ifndef LUAPLAYER_HPP
#define LUAPLAYER_HPP

#include "mge\behaviours\LuaScripts\LuaScript.hpp"
#include "glm.hpp"
#include <string>

class LuaPlayer : public LuaScript
{
public:
	LuaPlayer(std::string pTag);
	virtual ~LuaPlayer();

	virtual void luaStart();
	virtual void update(float pStep);
	virtual AbstractBehaviour* copy();

private:
	static void mapKey(sf::Keyboard::Key key, string luaKey);
	static map<string, sf::Keyboard::Key> inputMap;
	void mapInput();
	static int getKey(lua_State * state);
};

#endif // LUAMOVE_HPP;