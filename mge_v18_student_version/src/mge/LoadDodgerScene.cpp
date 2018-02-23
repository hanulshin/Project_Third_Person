#include "LoadDodgerScene.hpp"


LoadDodgerScene::LoadDodgerScene() :AbstractGame(), _hud(0)
{
}



void LoadDodgerScene::initialize()
{
	//setup the core part
	AbstractGame::initialize();

	//setup the custom part so we can display some text
	std::cout << "HUD Initialized." << std::endl << std::endl;
}

void LoadDodgerScene::_initializeScene()
{
	
	Mesh* cubeMesh = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");
	Mesh* sphereMesh = Mesh::load(config::MGE_MODEL_PATH + "sphere_smooth.obj");

	AbstractMaterial* playerMaterial = new ColorMaterial(glm::vec3(0, 0.5f, 1));
	AbstractMaterial* runicStoneMaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png"));

	GameObject* player = new GameObject("Player", glm::vec3(0, 1, 0));
	player->scale(glm::vec3(0.8f, 1, 0.8f));
	player->setMesh(sphereMesh);
	player->setMaterial(playerMaterial);
	//player->setBehaviour(new PlayerBehaviour(500));
	_world->add(player);

	
	
	std::vector<GameObject*> floor;
	for (int a = 0; a < 9; a++) {
		floor.push_back(new GameObject("Floor", glm::vec3(-8 + (a * 2), -2, 0)));
		floor[a]->setMesh(cubeMesh);
		floor[a]->setMaterial(runicStoneMaterial);
		_world->add(floor[a]);
	}
	
	Camera* camera = new Camera("camera", glm::vec3(0, 1.5f, 15));
	camera->rotate(glm::radians(-5.0f), glm::vec3(1, 0, 0));
	camera->setBehaviour(new CameraMovementBehaviour());
	player->add(camera);
	_world->setMainCamera(camera);

	
	//read the file as char vector
	std::ifstream myXml("C:/Users/hanul/Desktop/Project Third person/Project_Third_Person/mge_v18_student_version/src/mge/scene.xml");
	std::vector<char> buffer((std::istreambuf_iterator<char>(myXml)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');

	//parse the xml file
	rapidxml::xml_document<> doc;
	doc.parse<0>(&buffer[0]);

	//find the root and send it to process
	rapidxml::xml_node<> * root_node = doc.first_node("root");
	_processChildren(root_node, _world);

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
	if (strcmp(pXmlNode->name(),"GameObject")==0)
	{
		GameObject * newNode = _convertGameObject(pXmlNode, currentNode);
		currentNode->add(newNode);
		std::cout << newNode->getName() << " added to " << currentNode->getName() << std::endl;
		currentNode = newNode;
	}
	_processChildren(pXmlNode,currentNode);
}

GameObject* LoadDodgerScene::_convertGameObject(rapidxml::xml_node<>* pXmlNode, GameObject* pgameObjectNode)
{
	GameObject* gameObject = new GameObject("temp");
	//use material library set up by the artists
	AbstractMaterial* whitematerial = new ColorMaterial(glm::vec3(1, 1, 1));
	AbstractMaterial* stoner = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png"));
	gameObject->setMaterial(stoner);
	for (rapidxml::xml_attribute<>*attrib = pXmlNode->first_attribute();
		attrib!=NULL;attrib=attrib->next_attribute())
	{
		std::cout << attrib->name() << "=" << attrib->value() << std::endl;
		std::string attribName = attrib->name();

		if (attribName == "name")
		{
			gameObject->setName(attrib->value());
		}
		else if (attribName=="position")
		{
			glm::vec3 position;
			sscanf(attrib->value(), "(%f,%f,%f)", &position.x, &position.y, &position.z);
			gameObject->setLocalPosition(position);
		}
		else if (attribName == "rotation")
		{
			glm::quat rotation;
			sscanf(attrib->value(),"(%f,%f,%f,%f)",&rotation.x,&rotation.y,&rotation.z,&rotation.w);
			gameObject->rotate(glm::angle(rotation),glm::axis(rotation));
		}
		else if(attribName == "scale")
		{
			glm::vec3 scale;
			sscanf(attrib->value(), "(%f,%f,%f)", &scale.x, &scale.y, &scale.z);
			gameObject->scale(scale);
		}
		else if(attribName=="mesh")
		{
			Mesh* objMesh = Mesh::load(config::MGE_MODEL_PATH + attrib->value());
			gameObject->setMesh(objMesh);
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

	//_hud->setDebugInfo(debugInfo);
	//_hud->draw();
}
LoadDodgerScene::~LoadDodgerScene()
{
}