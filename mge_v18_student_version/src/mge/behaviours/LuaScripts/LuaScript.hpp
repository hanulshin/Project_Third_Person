#ifndef LUASCRIPT_HPP
#define LUASCRIPT_HPP

#include <LuaJIT-2.0.5\src\lua.hpp>
#include <string>
#include "mge/behaviours/AbstractBehaviour.hpp"

using namespace std;

class LuaScript : public AbstractBehaviour 
{
	public:
		LuaScript(string fileName);
		~LuaScript();

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

		int getInt();
		float getNumber();
		bool getBool();
		string getString();
	private:
		std::string _file;
};

#endif // LUASCRIPT_HPP
