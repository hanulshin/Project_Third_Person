#include <iostream>
#include <string>
#include <vector>

#include "glm.hpp"

#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Texture.hpp"
#include "mge/core/Light.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/GameObject.hpp"

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/PlayerBehaviour.hpp"
#include "mge/behaviours/LuaScripts/LuaPlayer.hpp"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "mge/prefabs.hpp"
#include "DodgerGame.hpp"



//construct the game class into _window, _renderer and hud (other parts are initialized by build)
DodgerGame::DodgerGame() :AbstractGame(), _hud(0)
{
}

void DodgerGame::initialize() {
	//setup the core part
	AbstractGame::initialize();

	//setup the custom part so we can display some text
	std::cout << "Initializing HUD" << std::endl;
	_hud = new DebugHud(_window);
	std::cout << "HUD initialized." << std::endl << std::endl;
}

//build the game _world
void DodgerGame::_initializeScene()
{
	GameObject* player = new GameObject("Player", glm::vec3(0, 1, 0));
	player->scale(glm::vec3(0.8f, 1, 0.8f));
	player->setMesh(meshes::sphere);
	player->setMaterial(colors::skyBlue);
	//player->setBehaviour(new PlayerBehaviour(5));
	player->setBehaviour(new LuaPlayer());
	_world->add(player);


	std::vector<GameObject*> floor;
	for (int a = 0; a < 9; a++) {
		floor.push_back(new GameObject("Floor", glm::vec3(-8 + (a * 2), -2, 0)));
		floor[a]->setMesh(meshes::cube);
		floor[a]->setMaterial(textures::runicStone);
		_world->add(floor[a]);
	}

	//GameObject*


	Camera* camera = new Camera("camera", glm::vec3(0, 1.5f, 15));
	camera->rotate(glm::radians(-5.0f), glm::vec3(1, 0, 0));
	player->add(camera);
	_world->setMainCamera(camera);
}

void DodgerGame::_render() {
	AbstractGame::_render();
	_updateHud();
}

void DodgerGame::_updateHud() {
	std::string debugInfo = "";
	debugInfo += std::string("FPS:") + std::to_string((int)_fps) + "\n";

	_hud->setDebugInfo(debugInfo);
	_hud->draw();
}

DodgerGame::~DodgerGame()
{

}
