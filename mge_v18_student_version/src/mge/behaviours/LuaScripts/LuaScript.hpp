#ifndef LUASCRIPT_HPP
#define LUASCRIPT_HPP

#include <LuaJIT-2.0.5\src\lua.hpp>
#include <string>
#include <map>
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "SFML\Window\Keyboard.hpp"

using namespace std;

class LuaScript : public AbstractBehaviour
{
public:
	LuaScript(string fileName, string tag);
	virtual ~LuaScript();

	virtual void start();
	virtual void earlyStart() = 0; //Called before the start in lua
	virtual void lateStart() = 0; //Called after the start in lua

	std::string getFile() { return _file; }

protected:
	lua_State * state;

	void openFile(string fileName, bool runStart = true);
	void settupFunction(string funcName);

	void callLuaUpdate(string pName, float pStep);
	void callFunction(int args = 0, int results = 0);

	void pushInt(int num);
	void pushNumber(float num);
	void pushBool(bool b);
	void pushString(string str);
	void pushObject(void* obj);


	int toInt(int i = -1);
	float toNumber(int i = -1);
	bool toBool(int i = -1);
	string toString(int i = -1);
	void remove(int i = -1);
	int getIndex(int i);

	void registerFunction(string name, lua_CFunction func);
private:
	void callInput();
	std::string _file;
	std::string _tag;

	//For Lua

	static int spawnObject(lua_State* state);
	static int blueprint(lua_State * state);
	static int clone(lua_State * state);
	static int move(lua_State * state);
	static int rotate(lua_State * state);
	static int scale(lua_State * state);
	static int addChild(lua_State * state);
	static int addToWorld(lua_State * state);
	static int kill(lua_State * state);

	static int addLuaScript(lua_State * state);
	static int addBullet(lua_State * state);
	static int addSpin(lua_State * state);
	static int addBox(lua_State * state);
	static int addCBox(lua_State * state);

	static int setPosition(lua_State * state);
	static int getPosition(lua_State * state);
	static int getGlobalPosition(lua_State * state);
	static int actorExists(lua_State * state);

	static int onCollide(lua_State * state);
	static int onBulletHit(lua_State * state);
	static int onEnemyHit(lua_State * state);
};



#endif // LUASCRIPT_HPP