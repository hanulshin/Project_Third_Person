#include <LuaJIT-2.0.5\src\lua.hpp>
#include <string>
#include <cmath>
#include <iostream>
#include <string>
#include <map>
#include "SFML\Window\Keyboard.hpp"
#include "glm.hpp"
#include "mge\config.hpp"
#include "mge\core\AbstractGame.hpp"
#include "mge\core\GameObject.hpp"
#include "mge\core\Prefab.hpp"
#include "mge\materials\AbstractMaterial.hpp"
#include "mge\materials\ColorMaterial.hpp"
#include "mge\materials\TextureMaterial.hpp"
#include "mge\collision\BoxCollider.h"
#include "mge\behaviours\BulletBehaviour.hpp"
#include "mge\behaviours\RotatingBehaviour.hpp"
#include "mge\behaviours\LuaScripts\LuaScript.hpp"
#include "mge\behaviours\LuaScripts\LuaPlayer.hpp"
#include "mge\behaviours\LuaScripts\EnemySpawner.hpp"
#include "mge\behaviours\LuaScripts\EnemyAI.hpp"

using namespace std;

//LUA functions
int LuaScript::spawnObject(lua_State* state) {
	string name = lua_tostring(state, 1);
	string parent = lua_tostring(state, 2);
	float x = (float)lua_tonumber(state, 3);
	float y = (float)lua_tonumber(state, 4);
	float z = (float)lua_tonumber(state, 5);

	return 0;
}
int LuaScript::blueprint(lua_State * state) {
	Prefab* prefab = Prefab::instance();
	string pName = lua_tostring(state, 1);
	printf("%s", pName.c_str());
	string pMesh = lua_tostring(state, 2);
	string pTexture = lua_tostring(state, 3);
	GameObject* pref = new GameObject(pName);
	GameObject* prefBody = new GameObject(pName + "Body");
	pref->add(prefBody);
	prefBody->setMesh(prefab->getMesh(pMesh));
	prefBody->setMaterial(prefab->getMaterial(pTexture));
	pref->setActor("_" + pName);

	return 0;
}
int LuaScript::move(lua_State * state) {
	GameObject* actor = GameObject::getActor(lua_tostring(state, 1));
	if (actor == nullptr) return 0;
	glm::vec3 delta = glm::vec3(lua_tonumber(state, 2), lua_tonumber(state, 3), lua_tonumber(state, 4));
	actor->translate(delta);
	return 0;
}
int LuaScript::rotate(lua_State * state) {
	string actor = lua_tostring(state, 1);
	glm::vec3 delta = glm::vec3(lua_tonumber(state, 2), lua_tonumber(state, 3), lua_tonumber(state, 4));
	GameObject::getActor(actor)->rotate(delta.x, glm::vec3(1, 0, 0));
	GameObject::getActor(actor)->rotate(delta.y, glm::vec3(0, 1, 0));
	GameObject::getActor(actor)->rotate(delta.z, glm::vec3(0, 0, 1));
	return 0;
}
int LuaScript::scale(lua_State * state) {
	string actor = lua_tostring(state, 1);
	glm::vec3 delta = glm::vec3(lua_tonumber(state, 2), lua_tonumber(state, 3), lua_tonumber(state, 4));
	GameObject::getActor(actor)->scale(delta);
	return 0;
}
int LuaScript::addChild(lua_State * state) {
	string parent = lua_tostring(state, 1);
	string child = lua_tostring(state, 2);
	GameObject::getActor(parent)->add(GameObject::getActor(child));
	return 0;

}
int LuaScript::addToWorld(lua_State * state) {
	GameObject::getActor("world")->add(GameObject::getActor(lua_tostring(state, 1)));
	return 0;
}
int LuaScript::clone(lua_State * state) {
	string original = lua_tostring(state, 1);
	string copy = lua_tostring(state, 2);
	GameObject * o = GameObject::getActor(original)->copy(copy);
	o->setActor(copy);
	return 0;
}
int LuaScript::addLuaScript(lua_State * state) {
	string actor = lua_tostring(state, 1);
	string script = lua_tostring(state, 2);
	string tag = lua_tostring(state, 3);
	AbstractBehaviour* b;
	if (script == "player") {
		b = new LuaPlayer(tag);
	} 
	else if (script == "spawner") {
		b = new EnemySpawner(tag);
	} 
	else if (script == "enemy") {
		b = new EnemyAI(tag, lua_tostring(state, 4));
	}
	else {
		b = nullptr;
	}

	if (b != nullptr) {
		GameObject::getActor(actor)->setBehaviour(b);
	}
	else {
		printf("No such script [%s] exists!", script);
	}
	return 0;
}
int LuaScript::addBullet(lua_State * state) {
	GameObject * actor = GameObject::getActor(lua_tostring(state, 1));
	glm::vec2 velocity = glm::vec2(lua_tonumber(state, 2), lua_tonumber(state, 3));
	int damage = lua_tointeger(state, 4);
	float knockback = lua_tonumber(state, 5);
	float time = lua_tonumber(state, 6);
	actor->setBehaviour(new BulletBehaviour(velocity, damage, knockback, time));
	return 0;
}
int LuaScript::addSpin(lua_State * state) {
	GameObject * actor = GameObject::getActor(lua_tostring(state, 1));
	float rpm = lua_tonumber(state, 2);
	glm::vec3 axis = glm::vec3();
	axis.x = lua_tonumber(state, 3);
	axis.y = lua_tonumber(state, 4);
	axis.z = lua_tonumber(state, 5);
	actor->setBehaviour(new RotatingBehaviour(rpm, axis));
	return 0;
}
int LuaScript::addBox(lua_State* state) {
	GameObject * actor = GameObject::getActor(lua_tostring(state, 1));
	glm::vec3 pos = glm::vec3();
	float width = lua_tonumber(state, 2);
	float height = lua_tonumber(state, 3);
	pos.x = lua_tonumber(state, 4);
	pos.y = lua_tonumber(state, 5);
	pos.z = lua_tonumber(state, 6);
	actor->setBoxCollider(new BoxCollider(width, height, pos));
	return 0;
}
int LuaScript::addCBox(lua_State* state) {
	GameObject * actor = GameObject::getActor(lua_tostring(state, 1));
	glm::vec3 pos = glm::vec3(0,0,0);
	float width = lua_tonumber(state, 2);
	float height = lua_tonumber(state, 3);
	actor->setBoxCollider(new BoxCollider(width, height, pos));
	return 0;
}
int LuaScript::getGlobalPosition(lua_State * state) {
	GameObject * actor = GameObject::getActor(lua_tostring(state, 1));
	glm::vec3 pos = actor->getWorldPosition();
	lua_pushnumber(state, pos.x);
	lua_pushnumber(state, pos.y);
	lua_pushnumber(state, pos.z);
	return 3;
}
int LuaScript::getPosition(lua_State * state) {
	GameObject * actor = GameObject::getActor(lua_tostring(state, 1));
	glm::vec3 pos = actor->getLocalPosition();
	lua_pushnumber(state, pos.x);
	lua_pushnumber(state, pos.y);
	lua_pushnumber(state, pos.z);
	return 3;
}
int LuaScript::actorExists(lua_State * state) {
	lua_pushboolean(state, GameObject::isActor(lua_tostring(state, 1)));
	return 1;
}
int LuaScript::setPosition(lua_State * state) {
	GameObject * actor = GameObject::getActor(lua_tostring(state, 1));
	glm::vec3 pos = glm::vec3(lua_tonumber(state, 2), lua_tonumber(state, 3), lua_tonumber(state, 4));
	actor->setLocalPosition(pos);
	return 0;
}
int LuaScript::kill(lua_State * state) 
{
	delete(GameObject::getActor(lua_tostring(state, 1)));
	return 0;
}
int LuaScript::onCollide(lua_State * state) 
{
	BoxCollider * one = GameObject::getActor(lua_tostring(state, 1))->getBoxCollider();
	BoxCollider * other = GameObject::getActor(lua_tostring(state, 2))->getBoxCollider();

	lua_pushboolean(state, one->IsOverlapping(other));
	return 1;
}
int LuaScript::onBulletHit(lua_State * state) {
	GameObject * one = GameObject::getActor(lua_tostring(state, 1));
	if (one == nullptr || !one->hasCollider()) {
		lua_pushboolean(state, false);
		return 1;
	}
	std::vector<BulletBehaviour*>* bullets = BulletBehaviour::getBullets();
	for (int a = bullets->size() - 1; a >= 0; a--) {
		BulletBehaviour* b = bullets->at(a);
		GameObject* bullet = b->getOwner();
		if (!bullet->hasCollider()) continue;
		if (one->getBoxCollider()->IsOverlapping(bullet->getBoxCollider())) {
			lua_pushboolean(state, true);
			lua_pushinteger(state, b->getDamage());
			lua_pushnumber(state, b->getKnockBack());
			delete(bullet);
			return 3;
		}
	}
	lua_pushboolean(state, false);
	return 1;
}
int LuaScript::onEnemyHit(lua_State * state) {
	GameObject * one = GameObject::getActor(lua_tostring(state, 1));

	if (one == nullptr || !one->hasCollider()) {
		lua_pushboolean(state, false);
		return 1;
	}
	std::vector<EnemyAI*>* enemies = EnemyAI::getEnemies();
	for (int a = enemies->size() - 1; a >= 0; a--) {
		EnemyAI* e = enemies->at(a);
		GameObject* enemy = e->getOwner();
		if (!enemy->hasCollider()) continue;
		if (one->getBoxCollider()->IsOverlapping(enemy->getBoxCollider())) {
			lua_pushboolean(state, true);
			lua_pushstring(state, enemy->getActorTag().c_str());
			lua_pushinteger(state, e->getDamage());
			e->HitPlayer();
			return 3;
		}
	}
	lua_pushboolean(state, false);
	return 1;
}
int LuaScript::setActive(lua_State * state) {
	GameObject* actor = GameObject::getActor(lua_tostring(state, 1));
	actor->getBehaviour()->setActive(lua_toboolean(state, 2));
	return 0;
}

//Class

LuaScript::LuaScript(string fileName, string ptag) : _file(fileName), _tag(ptag)
{

}

LuaScript::~LuaScript()
{

}

void LuaScript::callInput() {
	using namespace sf;
	lua_newtable(state);
	map<string, bool> inputMap;

	callFunction(6);
}

void LuaScript::start()
{
	state = luaL_newstate();
	luaL_openlibs(state);
	openFile(_file, false);
	if(!GameObject::isActor(_tag)) _owner->setActor(_tag);
	registerFunction("spawn", spawnObject);
	registerFunction("blueprint", blueprint);
	registerFunction("clone", clone);
	registerFunction("move", move);
	registerFunction("rotate", rotate);
	registerFunction("scale", scale);
	registerFunction("addChild", addChild);
	registerFunction("addToWorld", addToWorld);
	registerFunction("kill", kill);

	registerFunction("addLua", addLuaScript);
	registerFunction("addBullet", addBullet);
	registerFunction("addSpin", addSpin);
	registerFunction("addBox", addBox);
	registerFunction("addCBox", addCBox);

	registerFunction("setPos", setPosition);
	registerFunction("getPos", getPosition);
	registerFunction("getGPos", getGlobalPosition);
	registerFunction("isActor", actorExists);

	registerFunction("onEnemyHit", onEnemyHit);
	registerFunction("onBulletHit", onBulletHit);
	registerFunction("onCollide", onCollide);
	registerFunction("setActive", setActive);

	earlyStart();
	settupFunction("start");
	pushString(_tag);
	callFunction(1);
	lateStart();
}

void LuaScript::openFile(string fileName, bool runStart)
{
	_file = fileName;
	if (luaL_dofile(state, (config::MGE_SCRIPTS_PATH + fileName).c_str()) != 0) {
		std::string error = lua_tostring(state, -1);
		printf("Could not do file: %s\n", error.c_str());
	}

	if (runStart) {
		settupFunction("start");
		pushString(_owner->getActorTag());
		callFunction();
	}
}

void LuaScript::settupFunction(string funcName)
{
	lua_getglobal(state, funcName.c_str());
	if (!lua_isfunction(state, -1)) {
		printf(("Error: [" + funcName + "] is not a function.").c_str());
	}
}

void LuaScript::callLuaUpdate(string pName, float pStep)
{
	settupFunction(pName);
	pushNumber(pStep);
	callFunction(1, 0);
}

void LuaScript::callFunction(int args, int results)
{
	if (lua_pcall(state, args, results, 0) != 0) { // call init()
		printf("Lua call error %s\n", lua_tostring(state, -1));
	}
}

void LuaScript::pushInt(int num) {
	lua_pushinteger(state, num);
}

void LuaScript::pushNumber(float num) {
	lua_pushnumber(state, num);
}

void LuaScript::pushString(string str) {
	lua_pushstring(state, str.c_str());
}

void LuaScript::pushBool(bool b) {
	lua_pushboolean(state, b);
}

void LuaScript::pushObject(void* obj) {
	lua_pushlightuserdata(state, obj);
}


int LuaScript::toInt(int i) {
	int a = getIndex(i);
	int I = lua_tointeger(state, a);
	remove(a);
	return I;
}

bool LuaScript::toBool(int i) {
	int a = getIndex(i);
	bool b = lua_toboolean(state, a);
	remove(a);
	return b;
}

float LuaScript::toNumber(int i) {
	int a = getIndex(i);
	float f = (float)lua_tonumber(state, a);
	remove(a);
	return f;
}

string LuaScript::toString(int i) {
	int a = getIndex(i);
	string s = lua_tostring(state, a);
	remove(a);
	return s;
}

void LuaScript::remove(int i) {
	lua_remove(state, getIndex(i));
}

int LuaScript::getIndex(int i) {
	if (i == -1) return lua_gettop(state);
	return i;
}

void LuaScript::registerFunction(string name, lua_CFunction func) {
	lua_register(state, name.c_str(), func);
}
