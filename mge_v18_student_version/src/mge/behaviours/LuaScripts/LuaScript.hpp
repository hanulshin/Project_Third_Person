#ifndef LUASCRIPT_HPP
#define LUASCRIPT_HPP

#include <LuaJit\LuaJIT-2.0.5\src\lua.hpp>
#include <string>
#include "mge/behaviours/AbstractBehaviour.hpp"

class LuaScript : public AbstractBehaviour 
{
	public:
		LuaScript(std::string pLuaFile);

		virtual void start();
		virtual void _register() = 0;
	protected:
		lua_State * state;
	private:
		std::string _luaFile;
};

#endif // LUASCRIPT_HPP
