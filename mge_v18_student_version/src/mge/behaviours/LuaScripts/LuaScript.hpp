#ifndef LUASCRIPT_HPP
#define LUASCRIPT_HPP

#include <LuaJit\LuaJIT-2.0.5\src\lua.hpp>
#include <string>
#include "mge/behaviours/AbstractBehaviour.hpp"

class LuaScript : public AbstractBehaviour 
{
	public:
		LuaScript(std::string luaFile);
		virtual ~LuaScript() = 0;

		virtual void update(float pStep);

	protected:
		lua_State * state;
	private:
};

#endif // LUASCRIPT_HPP
