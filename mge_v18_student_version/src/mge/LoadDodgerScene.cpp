#include "LoadDodgerScene.hpp"
#include "mge/behaviours/LuaScripts/EnemySpawner.hpp"
#include "collision\BoxCollider.h"
#include "mge\core\Prefab.hpp"

LoadDodgerScene::LoadDodgerScene() :AbstractGame(), _hud(0)
{
}

AbstractMaterial* whitematerial;
AbstractMaterial* stoner;
AbstractMaterial* elevatorPlatform;
AbstractMaterial* shaftT;
AbstractMaterial* gearsT;

void LoadDodgerScene::initialize()
{
	//setup the core part
	AbstractGame::initialize();
	_hud = new DebugHud(_window);
	//setup the custom part so we can display some text
	std::cout << "HUD Initialized." << std::endl << std::endl;
}

void LoadDodgerScene::_initializeScene()
{
	//sf::Music music;
	//music.openFromFile(config::MGE_MUSIC_PATH + "OffLimits.wav");
	//music.play();

	Prefab* prefab = Prefab::instance();

	//Mesh* cubeMesh = Mesh::load(config::MGE_MODEL_PATH + "Bullet.obj");
	Mesh* cubeMesh = prefab->getMesh("cube");
	Mesh* playerMesh = prefab->getMesh("player");

	AbstractMaterial* red = prefab->getMaterial("red");
	AbstractMaterial* brown = prefab->getMaterial("brown");
	AbstractMaterial* playerMaterial = prefab->getMaterial("sky");
	AbstractMaterial* runicStoneMaterial = prefab->getMaterial("stone");

	whitematerial = new ColorMaterial(glm::vec3(1, 1, 1));
	stoner = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png"));
	elevatorPlatform = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "Elevator_PipeBarrierSG1_Diffuse (1).png"));
	shaftT = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "Shaft_phong2SG_Diffuse 1.png"));
	gearsT = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "Gears_phong4SG_Diffuse 1.png"));

	Camera* camera = new Camera("camera", glm::vec3(0, 10.9, 30.5));
	camera->rotate(glm::radians(0.0f), glm::vec3(0.0, -1.0, 0.0));
	//camera->setBehaviour(new CameraMovementBehaviour());
	//camera->setBehaviour(upMove);

	camera->setBehaviour(new UpMovementBehaviour(10.9f, 7.0f));
	_world->add(camera);
	_world->setMainCamera(camera);


	//read the file as char vector
	std::ifstream myXml(config::MGE_SCENE_PATH + "scene.xml");
	std::vector<char> buffer((std::istreambuf_iterator<char>(myXml)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	//parse the xml file
	rapidxml::xml_document<> doc;
	doc.parse<0>(&buffer[0]);

	//find the root and send it to process
	rapidxml::xml_node<> * root_node = doc.first_node("root");
	_processChildren(root_node, _world);

	GameObject* player = new GameObject("Player", glm::vec3(0, 0, 6));
	player->scale(glm::vec3(0.8f, 1, 0.8f));
	player->setMesh(playerMesh);
	player->setMaterial(playerMaterial);
	player->setBehaviour(new LuaPlayer("player"));
	//player->setActor("player");
	player->setBoxCollider(new BoxCollider(2.0f, 2.0f, player->getWorldPosition()));
	_world->add(player);

}


void LoadDodgerScene::_processChildren(rapidxml::xml_node<>* pXmlNode, GameObject* pGameObjectNode)
{
	for (rapidxml::xml_node<> * child = pXmlNode->first_node(); child != NULL; child = child->next_sibling())
	{
		_processSingle(child, pGameObjectNode);
	}
}

void LoadDodgerScene::_processSingle(rapidxml::xml_node<>* pXmlNode, GameObject* pGameObjectNode)
{
	GameObject* currentNode = pGameObjectNode;
	std::cout << "Processing" << pXmlNode->name() << std::endl;
	if (strcmp(pXmlNode->name(), "GameObject") == 0)
	{
		GameObject * newNode = _convertGameObject(pXmlNode, currentNode);
		currentNode->add(newNode);
		std::cout << newNode->getName() << " added to " << currentNode->getName() << std::endl;
		currentNode = newNode;
	}
	_processChildren(pXmlNode, currentNode);
}

GameObject* LoadDodgerScene::_convertGameObject(rapidxml::xml_node<>* pXmlNode, GameObject* pgameObjectNode)
{
	GameObject* gameObject = new GameObject("temp");
	Prefab* prefab = Prefab::instance();
	//use material library set up by the artists

	//Gears_phong4SG_Diffuse 1
	gameObject->setMaterial(stoner);
	for (rapidxml::xml_attribute<>*attrib = pXmlNode->first_attribute();
		attrib != NULL; attrib = attrib->next_attribute())
	{
		std::cout << attrib->name() << "=" << attrib->value() << std::endl;
		std::string attribName = attrib->name();
		std::string attribValue = attrib->value();

		if (attribName == "name")
		{
			gameObject->setName(attribValue);

			//setup a fiunction which takes attrib value and assigns texture depending on it
			if (attribValue == "GearsWheel")
			{
				std::cout << "GearDetected" << endl;
				gameObject->setBehaviour(new RotatingBehaviour(15, glm::vec3(0, 0, 1)));
			}
			if (attribValue == "ElevatorPlatform")
			{
				gameObject->setMaterial(elevatorPlatform);
			}
			if (attribValue == "ShaftWall")
			{
				gameObject->setMaterial(shaftT);
			}
			if (attribValue == "GearsWheel")
			{
				gameObject->setMaterial(gearsT);
				//gameObject->setBehaviour(new UpMovementBehaviour());
			}
		}
		else if (attribName == "position")
		{
			glm::vec3 position;
			sscanf(attrib->value(), "(%f,%f,%f)", &position.x, &position.y, &position.z);
			gameObject->setLocalPosition(position);
		}
		else if (attribName == "rotation")
		{
			glm::quat rotation;
			sscanf(attrib->value(), "(%f,%f,%f,%f)", &rotation.x, &rotation.y, &rotation.z, &rotation.w);
			gameObject->rotate(glm::angle(rotation), glm::axis(rotation));
		}
		else if (attribName == "scale")
		{
			glm::vec3 scale;
			sscanf(attrib->value(), "(%f,%f,%f)", &scale.x, &scale.y, &scale.z);
			gameObject->scale(scale);
		}
		else if (attribName == "mesh")
		{
			Mesh* objMesh = Mesh::load(config::MGE_MODEL_PATH + attribValue);
			gameObject->setMesh(objMesh);
			if (gameObject->getName() == "ElevatorPlatform")
			{
				gameObject->setBoxCollider(new BoxCollider(200.0f, 1.0f, gameObject->getWorldPosition()));
				gameObject->setBehaviour(new UpMovementBehaviour(gameObject->getLocalPosition().y, 6.0f));
			}
		}
		else if (attribName == "actor") {
			gameObject->setActor(attribValue);
		}
		else if (attribName == "behaviour") {
			if (attribValue == "spawner") {
				gameObject->setBehaviour(new EnemySpawner(attribValue));
			}
			else if (attribValue == "player") {
				gameObject->setBehaviour(new LuaPlayer(attribValue));
			}
			else
			if (attribValue == "elevator") {
				gameObject->setBehaviour(new UpMovementBehaviour(0.0f));
			}
		}

	}
	_world->add(gameObject);
	return gameObject;
}



void LoadDodgerScene::_render()
{
	AbstractGame::_render();
	_updateHud();

}

void LoadDodgerScene::_updateHud()
{
	std::string debugInfo = "";
	debugInfo += std::string("FPS:") + std::to_string((int)_fps) + "\n";

	_hud->setDebugInfo(debugInfo);
	_hud->draw();
}
LoadDodgerScene::~LoadDodgerScene()
{
}
