#include "mge\behaviours\LuaScripts\LuaScript.hpp"
#include <LuaJit\LuaJIT-2.0.5\src\lua.hpp>
#include <string>

LuaScript::LuaScript(std::string pLuaFile): _luaFile(pLuaFile){

}

void LuaScript::start() 
{
	//state = luaL_newstate();
	_register();
	
	//luaL_dostring(state, "print('Hello Lua World')");
}