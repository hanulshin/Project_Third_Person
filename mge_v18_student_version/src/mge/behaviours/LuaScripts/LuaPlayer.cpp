#include <map>
#include <string>
#include <iostream>
#include <SFML/Audio.hpp>
#include "glm.hpp"
#include "mge\config.hpp"
#include "mge\core\World.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Animation.hpp"
#include "mge\core\GameObject.hpp"
#include "mge\core\AbstractGame.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge\behaviours\BulletBehaviour.hpp"
#include "mge\behaviours\LuaScripts\LuaPlayer.hpp"
#include "SFML/Graphics.hpp"
#include "SFML\Window\Keyboard.hpp"
#include "LuaJIT-2.0.5\src\lua.hpp"

using namespace glm;
//b->rotate(glm::radians(vel.x), glm::vec3(0,0,1));
//Class

sf::Music music;
sf::Music shot;
bool isMusic = true;
AbstractMaterial* runicStoneMaterial;
sf::Texture texture;

Animation shootingUpAnimation;
Animation movingLeftAnimation;
Animation movingRightAnimation;
Animation shooting45RightAnimation;
Animation shooting45LeftAnimation;
Animation idle;

Animation currentAnimation = shootingUpAnimation;
AnimationStates animationState = IDLE;
AnimationStates currentStateSent;
std::size_t m_currentFrame = 0;

LuaPlayer::LuaPlayer(std::string pTag) : LuaScript("Player.lua", pTag)
{
	texture.loadFromFile(config::MGE_ANIMATIONS_PATH + "Shooting UP.1.png");
	sf::Sprite sprite(texture, sf::IntRect(0, 0, 200, 280));

	for (int i = 1; i < 21; i++)
	{
		std::string animationframe = std::to_string(i);
		TextureMaterial* playerMaterialAnimation = new TextureMaterial(Texture::load(config::MGE_ANIMATIONS_PATH + "Shoot/" + "Shooting UP." + animationframe + ".png"));
		shootingUpAnimation.addFrame(playerMaterialAnimation);
		//delete playerMaterialAnimation;
	}

	for (int i = 1; i < 21; i++)
	{
		std::string animationframe = std::to_string(i);
		TextureMaterial* playerMaterialAnimation = new TextureMaterial(Texture::load(config::MGE_ANIMATIONS_PATH + "MoveL/" + "Run L (" + animationframe + ").png"));
		movingLeftAnimation.addFrame(playerMaterialAnimation);
		//delete playerMaterialAnimation;
	}
	for (int i = 1; i < 21; i++)
	{
		std::string animationframe = std::to_string(i);
		TextureMaterial* playerMaterialAnimation = new TextureMaterial(Texture::load(config::MGE_ANIMATIONS_PATH + "MoveR/" + "Run (" + animationframe + ").png"));
		movingRightAnimation.addFrame(playerMaterialAnimation);
		//delete playerMaterialAnimation;
	}
	for (int i = 1; i < 21; i++)
	{
		std::string animationframe = std::to_string(i);
		TextureMaterial* playerMaterialAnimation = new TextureMaterial(Texture::load(config::MGE_ANIMATIONS_PATH + "RunShoot45DegR/" + "Run Shoot 45 Deg R  (" + animationframe + ").png"));
		shooting45RightAnimation.addFrame(playerMaterialAnimation);
		//delete playerMaterialAnimation;
	}
	for (int i = 1; i < 21; i++)
	{
		std::string animationframe = std::to_string(i);
		TextureMaterial* playerMaterialAnimation = new TextureMaterial(Texture::load(config::MGE_ANIMATIONS_PATH + "RunShoot45DegL/" + "Run Shoot 45 L (" + animationframe + ").png"));
		shooting45LeftAnimation.addFrame(playerMaterialAnimation);
		//delete playerMaterialAnimation;
	}
	for (int i = 1; i < 21; i++)
	{
		std::string animationframe = std::to_string(i);
		TextureMaterial* playerMaterialAnimation = new TextureMaterial(Texture::load(config::MGE_ANIMATIONS_PATH + "Idle/" + "Idle (" + animationframe + ").png"));
		idle.addFrame(playerMaterialAnimation);
		//delete playerMaterialAnimation;
	}
}

LuaPlayer::~LuaPlayer()
{

}

void LuaPlayer::earlyStart()
{
	registerFunction("getKey", getKey);
	mapInput();
}

void LuaPlayer::lateStart()
{

}

void LuaPlayer::update(float pStep)
{
	callLuaUpdate("step", pStep);
	/**
	if (isMusic)
	{
		music.openFromFile(config::MGE_MUSIC_PATH + "Background.wav");
		//music.play();
		isMusic = false;
	}
	/**/
	
	vec3 delta = vec3(0, 0, 0);
	animationState = IDLE;

	delta.x = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) - sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	if (delta.x>0)
	{
		animationState = MOVING_RIGHT;
	}
	else if (delta.x<0)
	{
		animationState = MOVING_LEFT;
	}
	


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		if (animationState == MOVING_LEFT)
		{
			animationState = SHOOTING_LEFT;
		}
		else if (animationState == MOVING_RIGHT)
		{
			animationState = SHOOTING_RIGHT;
		}
		else if (animationState == IDLE)
		{
			animationState = SHOOTING_IDLE;
		}
	}
	Animate(animationState, pStep);
}

float animationSpeed = 30.0f;
float animationUpdateTime = 1.0f / animationSpeed;
float timeSinceLastFrameSwap = 0.0f;
void LuaPlayer::Animate(AnimationStates & animeState, float pStep)
{
	switch (animeState)
	{
	case IDLE: currentAnimation = idle; break;
	case MOVING_LEFT: currentAnimation = movingLeftAnimation; break;
	case MOVING_RIGHT: currentAnimation = movingRightAnimation; break;
	case SHOOTING_IDLE: currentAnimation = shootingUpAnimation; break;
	case SHOOTING_LEFT: currentAnimation = shooting45LeftAnimation; break;
	case SHOOTING_RIGHT: currentAnimation = shooting45RightAnimation; break;
	}
	if (m_currentFrame + 1 < currentAnimation.getSize())
	{
		timeSinceLastFrameSwap += pStep;
		if (timeSinceLastFrameSwap > animationUpdateTime)
		{
			m_currentFrame++;
			timeSinceLastFrameSwap = 0.0f;
		}
	}
	else
	{
		// animation has ended
		m_currentFrame = 0; // reset to start
		timeSinceLastFrameSwap = 0.0f;
	}


	AbstractMaterial* playerMaterialAnimationHARD = currentAnimation.getFrame(m_currentFrame);
	//std::cout << playerMaterialAnimationHARD << endl;
	//std::cout << _owner->getMaterial() << endl;
	_owner->setMaterial(playerMaterialAnimationHARD);
}

AbstractBehaviour* LuaPlayer::copy() {
	return new LuaPlayer(_owner->getActorTag() + "c");
}

map<string, sf::Keyboard::Key> LuaPlayer::inputMap = map<string, sf::Keyboard::Key>();

void LuaPlayer::mapKey(sf::Keyboard::Key key, string luaKey) {
	inputMap.insert(std::pair<string, sf::Keyboard::Key>(luaKey, key));
}

void LuaPlayer::mapInput() {
	using namespace sf;
	mapKey(Keyboard::Up, "up");
	mapKey(Keyboard::Down, "down");
	mapKey(Keyboard::Right, "right");
	mapKey(Keyboard::Left, "left");
	mapKey(Keyboard::Space, "space");
	mapKey(Keyboard::Z, "z");
}

int LuaPlayer::getKey(lua_State * state) {
	string input = lua_tostring(state, 1);
	if (inputMap.count(input) == 0) {
		std::string errorLog = "No input with name [" + input + "] was found";
		return luaL_error(state, errorLog.c_str());
	}
	lua_pushboolean(state, sf::Keyboard::isKeyPressed(inputMap[input]));
	return 1;
}
