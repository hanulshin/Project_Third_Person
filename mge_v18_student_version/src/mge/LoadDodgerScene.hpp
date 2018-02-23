#pragma once


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
#include "mge/behaviours/LuaScripts/LuaMove.hpp"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "mge/core/AbstractGame.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include "behaviours\CameraMovementBehaviour.h"

class DebugHud;

/**
* An example subclass of AbstractGame showing how we can setup a scene.
*/
class LoadDodgerScene : public AbstractGame
{
	//PUBLIC FUNCITONS
public:
	LoadDodgerScene();
	virtual ~LoadDodgerScene();

	//override initialize so we can add a DebugHud
	virtual void initialize();

protected:
	//override so we can construct the actuall scene
	virtual void _initializeScene();
	void _processChildren(rapidxml::xml_node<>* pXmlNode, GameObject* pGameObjectNode);
	void _processSingle(rapidxml::xml_node<>* pXmlNode, GameObject* pGameObjectNode);

	GameObject * _convertGameObject(rapidxml::xml_node<>* pXmlNode, GameObject * pgameObjectNode);

	//override render to render the hud as well.
	virtual void _render();
private:
	DebugHud * _hud;
	void _updateHud();
	LoadDodgerScene(const LoadDodgerScene&);
	LoadDodgerScene& operator=(const LoadDodgerScene&);
};