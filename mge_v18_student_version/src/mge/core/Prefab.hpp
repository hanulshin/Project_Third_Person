#pragma once
#include "mge/core/Mesh.hpp"
#include "mge/materials/AbstractMaterial.hpp"
#include <string>
#include <unordered_map>
#include "mge/config.hpp"
#include "glm.hpp"

class Prefab {
public:
	static Prefab* instance();
	~Prefab();

	Mesh* getMesh(std::string pKey);
	void loadMesh(std::string pFileName, std::string pFileType = "obj");
	AbstractMaterial* getMaterial(std::string pKey);
	void loadTexture(std::string pFileName, std::string pFileType = "png");
	void setColor(std::string pName, glm::vec4 pColor);
private:
	std::unordered_map<std::string, Mesh*> _meshes;
	std::unordered_map<std::string, AbstractMaterial*> _materials;

	static Prefab * _instance;
	Prefab();
};