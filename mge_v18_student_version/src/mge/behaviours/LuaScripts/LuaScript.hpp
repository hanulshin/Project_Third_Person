#ifndef LUASCRIPT_HPP
#define LUASCRIPT_HPP

#include <LuaJIT-2.0.5\src\lua.hpp>
#include <string>
#include <map>
#include "mge/behaviours/AbstractBehaviour.hpp"

using namespace std;

class LuaScript : public AbstractBehaviour
{
public:
	LuaScript(string fileName);
	virtual ~LuaScript();

	
	virtual void start();
	virtual void luaStart() = 0;

	std::string getFile() { return _file; }

protected:
	lua_State * state;

	void openFile(string fileName);
	void settupFunction(string funcName);

	void callLuaUpdate(string pName, float pStep);

	void callFunction(int args = 0, int results = 0);

	void pushInt(int num);
	void pushNumber(float num);
	void pushBool(bool b);
	void pushString(string str);
	void pushObject(void* obj);

	int getInt(int i = -1);
	float getNumber(int i = -1);
	bool getBool(int i = -1);
	string getString(int i = -1);
	void remove(int i = -1);
	int getIndex(int i);

	void registerFunction(string name, lua_CFunction func);
private:
	std::string _file;

	static map<string, GameObject*> quickFind;

	//For Lua
	static int spawnObject(lua_State* state);
	static int action(lua_State* state);
	static int getAction(std::string action);
};



#endif // LUASCRIPT_HPP