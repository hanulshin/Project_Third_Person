#include <iostream>
#include <string>

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
#include "mge/behaviours/KeysBehaviour.hpp"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
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
	Mesh* cubeMesh = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");
	Mesh* sphereMesh = Mesh::load(config::MGE_MODEL_PATH + "sphere_smooth.obj");

	AbstractMaterial* playerMaterial = new ColorMaterial(glm::vec3(0, 0, 1));
	AbstractMaterial* runicStoneMaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png"));

	Camera* camera = new Camera("camera", glm::vec3(0, 6, 7));
	camera->rotate(glm::radians(-40.0f), glm::vec3(1, 0, 0));
	_world->add(camera);
	_world->setMainCamera(camera);

	GameObject* player = new GameObject("Player", glm::vec3(0, 0, 0));
	player->setMesh(sphereMesh);
	player->setMaterial(playerMaterial);
	player->setBehaviour(new KeysBehaviour(25, 25));
	_world->add(player);

	GameObject* floor = new GameObject("Floor", glm::vec3(0, -1, 0));
	floor->setMesh(cubeMesh);
	floor->setMaterial(runicStoneMaterial);
	_world->add(floor);
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
