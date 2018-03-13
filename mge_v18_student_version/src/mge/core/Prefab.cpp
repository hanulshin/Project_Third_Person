#include "mge/core/Prefab.hpp"
#include "mge/core/Texture.hpp"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/core/Mesh.hpp"
#include <string>
#include <unordered_map>
#include "glm.hpp"
using namespace std;

Prefab* Prefab::_instance(nullptr);

Prefab::Prefab(): _meshes(unordered_map<string, Mesh*>()), _materials(unordered_map<string, AbstractMaterial*>()) {
	
}

Prefab::~Prefab() {

}

void Prefab::loadMesh(string pFile, string pFileType) {
	if (_meshes.count(pFile.c_str()) == 0) {
		Mesh* mesh = Mesh::load(config::MGE_MODEL_PATH + pFile + "." + pFileType);
		_meshes.insert(pair<string, Mesh*>(pFile, mesh));
	}
	else {
		printf("Mesh [%s] already exists!\n", pFile.c_str());
	}
}

void Prefab::loadTexture(string pFile, string pFileType) {
	if (_materials.count(pFile.c_str()) == 0) {
		AbstractMaterial* texture = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + pFile + "." + pFileType));
		_materials.insert(pair<string, AbstractMaterial*>(pFile, texture));
	}
	else {
		printf("Texture [%s] already exists!", pFile.c_str());
	}
}

void Prefab::setColor(string pName, glm::vec4 pColor) {
	if (_materials.count(pName.c_str()) == 0) {
		AbstractMaterial* color = new ColorMaterial(pColor);
		_materials.insert(pair<string, AbstractMaterial*>(pName, color));
	}
	else {
		printf("Color [%s] already exists!\n", pName.c_str());
	}
}

Prefab* Prefab::instance() {
	if (_instance == nullptr) _instance = new Prefab();
	return _instance;
}

AbstractMaterial* Prefab::getMaterial(string pName) {
	if (_materials.count(pName.c_str()) > 0) {
		return _materials[pName];
	}
	else {
		printf("Material [%s] doesn't exist!\n", pName.c_str());
		return nullptr;
	}
}

Mesh* Prefab::getMesh(string pName) {
	if (_meshes.count(pName.c_str()) > 0) {
		return _meshes[pName];
	}
	else {
		printf("Mesh [%s] doesn't exist!\n", pName.c_str());
		return nullptr;
	}
}