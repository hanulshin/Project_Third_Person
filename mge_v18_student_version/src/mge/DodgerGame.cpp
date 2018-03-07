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
#include "../_vs2015/collision/BoxCollider.h"
#include "../_vs2015/Collision/CollisionManager.h"

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "DodgerGame.hpp"
GameObject* player;
GameObject* player2;

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

	/*GameObject* */player = new GameObject("Player", glm::vec3(0, 5, 0));
	//player->scale(glm::vec3(1, 1, 1));
	player->setMesh(sphereMesh);
	player->setMaterial(playerMaterial);
	player->setBehaviour(new KeysBehaviour(5, 5));
	_world->add(player);
	BoxCollider* box = new BoxCollider(2.0f, 2.0f, player->getWorldPosition());
	player->setBoxCollider(box);

	/*GameObject**/ player2 = new GameObject("Player2", glm::vec3(0, 2, 0));
	//player->scale(glm::vec3(1, 1, 1));
	player2->setMesh(sphereMesh);
	player2->setMaterial(playerMaterial);
	//player2->setBehaviour(new KeysBehaviour(5, 5));
	_world->add(player2);
	BoxCollider* box2 = new BoxCollider(2.0f, 2.0f, player2->getWorldPosition());
	box2->setMesh(cubeMesh);
	box2->setMaterial(runicStoneMaterial);
	player2->setBoxCollider(box2);

	Camera* camera = new Camera("camera", glm::vec3(0, 1.5f, 15));
	camera->rotate(glm::radians(-5.0f), glm::vec3(1, 0, 0));
	player->add(camera);
	_world->setMainCamera(camera);
	std::vector<GameObject*> floor;

	for (int a = 0; a < 9; a++) {
		floor.push_back(new GameObject("Floor", glm::vec3(-8 + (a * 2), -2, 0)));
		floor[a]->setMesh(cubeMesh);
		floor[a]->setMaterial(runicStoneMaterial);
		floor[a]->setBoxCollider(new BoxCollider(2.0f,2.0f, floor[a]->getWorldPosition()));
		_world->add(floor[a]);
	}
}
//float oldX = 5.0f;
//float oldY = 5.0f;

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
