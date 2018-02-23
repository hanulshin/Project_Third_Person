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

	protected:

	private:
		glm::vec3 handleMovement(glm::vec3 delta);
		void sendShoot();
};

#endif // LUAMOVE_HPP;
