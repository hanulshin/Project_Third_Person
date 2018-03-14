#include "mge/behaviours/LuaScripts/LuaScript.hpp"
#include <string>

class Settup : public LuaScript {
public:
	Settup(std::string tag);
	~Settup();
	virtual void earlyStart();
	virtual void lateStart();
	virtual void update(float dt);
	virtual AbstractBehaviour* copy();
private:
	static int loadColor(lua_State * state);
	static int loadTexture(lua_State * state);
	static int loadMesh(lua_State * state);
};