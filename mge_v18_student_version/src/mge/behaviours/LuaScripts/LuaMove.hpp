#ifndef LUAMOVE_HPP
#define LUAMOVE_HPP

#include "mge\behaviours\LuaScripts\LuaScript.hpp"

class LuaMove : public LuaScript
{
	public:
		LuaMove();
		virtual ~LuaMove();

		virtual void update(float pStep);
		virtual void _register();

	protected:

	private:

};

#endif // LUAMOVE_HPP;
