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

//load all the materials here
AbstractMaterial* box_pickup_Mat;
AbstractMaterial* bullet_Mat;
AbstractMaterial* clean_wall_mat;
AbstractMaterial* gears_mat;
AbstractMaterial* hangar_mat;
AbstractMaterial* heart_mat;
AbstractMaterial* shaft_section_1_mat;
AbstractMaterial* shaft_section_2_mat;
AbstractMaterial* shaft_section_3_mat;
AbstractMaterial* shaft_section_4_mat;
AbstractMaterial* shaft_section_5_mat;
AbstractMaterial* shaft_tutorial_mat;
AbstractMaterial* van_mat;


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
	elevatorPlatform = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH +"FinalTex/" + "Elevator.png"));
	shaftT = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "Shaft_phong2SG_Diffuse 1.png"));
	gearsT = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "Gears_phong4SG_Diffuse 1.png"));

	box_pickup_Mat = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "FinalTex/" + "box_Pickup.png"));
	bullet_Mat = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "FinalTex/" + "BulletTexture.png"));
	clean_wall_mat = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "FinalTex/" + "Clean Wall.png"));
	gears_mat = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "FinalTex/" + "Gears.png"));
	hangar_mat = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "FinalTex/" + "Hangar.png"));
	heart_mat = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "FinalTex/" + "Heart.png"));
	shaft_section_1_mat = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "FinalTex/" + "Section 01.png"));
	shaft_section_2_mat = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "FinalTex/" + "Section 02.png"));
	shaft_section_3_mat = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "FinalTex/" + "Section 03.png"));
	shaft_section_4_mat = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "FinalTex/" + "Section 04.png"));
	shaft_section_5_mat = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "FinalTex/" + "Section 05.png"));
	shaft_tutorial_mat = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "FinalTex/" + "Tutorial Wall.png"));
	van_mat = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "FinalTex/" + "Van.png"));

	Camera* camera = new Camera("camera", glm::vec3(0, 10.9, 30.5));
	camera->rotate(glm::radians(0.0f), glm::vec3(0.0, -1.0, 0.0));
	//camera->setBehaviour(new CameraMovementBehaviour());
	//camera->setBehaviour(upMove);

	camera->setBehaviour(new UpMovementBehaviour(50.0f, 10.9f, 7.0f));
	camera->setActor("camera");
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
				gameObject->setMaterial(gears_mat);
			}
			else
			if (attribValue == "ElevatorPlatform")
			{
				gameObject->setMaterial(elevatorPlatform);
			}
			else
			if (attribValue == "box_Pickup")
			{
				gameObject->setMaterial(box_pickup_Mat);
			}
			else
			if (attribValue == "Van")
			{
				gameObject->setMaterial(van_mat);
			}
			else
			if (attribValue == "Hangar")
			{
				gameObject->setMaterial(hangar_mat);
			}
			else
			//if (attribValue == "ShaftWall")
			//{
			//	gameObject->setMaterial(shaftT);
			//}
			if (attribValue == "GearsWheel")
			{
				gameObject->setMaterial(gearsT);
				//gameObject->setBehaviour(new UpMovementBehaviour());
			}
			else
			if (attribValue == "ShaftWallSection01")
			{
				gameObject->setMaterial(shaft_tutorial_mat);
			}
			else
			if (attribValue == "ShaftWallSection02")
			{
				gameObject->setMaterial(clean_wall_mat);
			}
			else
			if (attribValue == "ShaftWallSection03")
			{
				gameObject->setMaterial(shaft_section_1_mat);
			}
			else
			if (attribValue == "ShaftWallSection04")
			{
				gameObject->setMaterial(clean_wall_mat);
			}
			else
			if (attribValue == "ShaftWallSection05")
			{
				gameObject->setMaterial(clean_wall_mat);
			}
			else
			if (attribValue == "ShaftWallSection06")
			{
				gameObject->setMaterial(shaft_section_2_mat);
			}
			else
			if (attribValue == "ShaftWallSection07")
			{
				gameObject->setMaterial(clean_wall_mat);
			}
			else
			if (attribValue == "ShaftWallSection08")
			{
				gameObject->setMaterial(clean_wall_mat);
			}
			else
			if (attribValue == "ShaftWallSection09")
			{
				gameObject->setMaterial(shaft_section_3_mat);
			}
			else
			if (attribValue == "ShaftWallSection10")
			{
				gameObject->setMaterial(clean_wall_mat);
			}
			else
			if (attribValue == "ShaftWallSection11")
			{
				gameObject->setMaterial(clean_wall_mat);
			}
			else
			if (attribValue == "ShaftWallSection12")
			{
				gameObject->setMaterial(shaft_section_4_mat);
			}
			else
			if (attribValue == "ShaftWallSection13")
			{
				gameObject->setMaterial(clean_wall_mat);
			}
			else
			if (attribValue == "ShaftWallSection14")
			{
				gameObject->setMaterial(clean_wall_mat);
			}
			else
			if (attribValue == "ShaftWallSection15")
			{
				gameObject->setMaterial(shaft_section_5_mat);
			}
			else
			if (attribValue == "ShaftWallSection16")
			{
				gameObject->setMaterial(clean_wall_mat);
			}
			else
			if (attribValue == "ShaftWallSection17")
			{
				gameObject->setMaterial(clean_wall_mat);
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
				//gameObject->setBehaviour(new UpMovementBehaviour(50.0f, gameObject->getLocalPosition().y, 6.0f));
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
				gameObject->setBehaviour(new UpMovementBehaviour(50.0f, gameObject->getLocalPosition().y, 7.0f));
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
