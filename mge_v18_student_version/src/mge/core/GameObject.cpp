#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include "mge/config.hpp"
#include "GameObject.hpp"
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "../collision/BoxCollider.h"

GameObject::GameObject(const std::string& pName, const glm::vec3& pPosition)
	: _name(pName), _transform(glm::translate(pPosition)), _parent(nullptr), _children(),
	_mesh(nullptr), _behaviour(nullptr), _material(nullptr), _world(nullptr), _boxCollider(nullptr), actor_tag(""), tag("default")

{
	id++;
	_boxCollider = nullptr;
	_gameObjects.push_back(this);
}

GameObject::~GameObject()
{
	//do not forget to delete behaviour, material, mesh, collider manually if required!
	_gameObjects.erase(
		std::remove_if(
			_gameObjects.begin(),
			_gameObjects.end(),
			//here comes the C++11 lambda:
			[&](GameObject* const& go) {
			return go->id == this->id && go->getName() == this->getName(); }),
		_gameObjects.end());
	std::cout << "erased " << this->_name << std::endl;
	delete _behaviour;
	_behaviour = nullptr;
	std::cout << "_behaviour erased" << std::endl;
	delete _boxCollider;
	_boxCollider = nullptr;
	std::cout << "_boxCollider erased" << std::endl;
	//detach all children
	std::cout << "GC running on:" << _name << std::endl;

	while (_children.size() > 0) {
		GameObject* child = _children[0];
		remove(child);
		delete child;
	}
	_parent->remove(this);
	removeActor();

	//do not forget to delete behaviour, material, mesh, collider manually if required!
	_gameObjects.erase(std::find(_gameObjects.begin(),_gameObjects.end(), this));
	std::cout << "erased " << this->_name << std::endl;
}

void GameObject::setName(const std::string& pName)
{
	_name = pName;
}

std::string GameObject::getName() const
{
	return _name;
}

void GameObject::setTransform(const glm::mat4& pTransform)
{
	_transform = pTransform;
}

const glm::mat4& GameObject::getTransform() const
{
	return _transform;
}

void GameObject::setLocalPosition(glm::vec3 pPosition)
{
	_transform[3] = glm::vec4(pPosition, 1);
}

glm::vec3 GameObject::getLocalPosition() const
{
	return glm::vec3(_transform[3]);
}

void GameObject::setMaterial(AbstractMaterial* pMaterial)
{
	_material = pMaterial;
}

AbstractMaterial * GameObject::getMaterial() const
{
	return _material;
}

void GameObject::setMesh(Mesh* pMesh)
{
	_mesh = pMesh;
}

Mesh * GameObject::getMesh() const
{
	return _mesh;
}

void GameObject::setBehaviour(AbstractBehaviour* pBehaviour)
{
	_behaviour = pBehaviour;
	_behaviour->setOwner(this);
	_behaviour->start();
}

AbstractBehaviour* GameObject::getBehaviour() const
{
	return _behaviour;
}

void GameObject::setBoxCollider(BoxCollider* pBoxCollider) {
	_boxCollider = pBoxCollider;
	add(_boxCollider);
	_boxCollider->setName(_name + _boxCollider->getName());
}
BoxCollider* GameObject::getBoxCollider() const
{
	return _boxCollider;
}

void GameObject::setParent(GameObject* pParent) {
	//remove from previous parent
	if (_parent != nullptr) {
		_parent->_innerRemove(this);
	}

	//set new parent
	if (pParent != nullptr) {
		pParent->_innerAdd(this);
	}

	//if we have been detached from our parent, make sure
	//the world reference for us and all our children is set to null
	//if we have been attached to a parent, make sure
	//the world reference for us and all our children is set to our parent world reference
	//(this could still be null if the parent or parent's parent is not attached to the world)
	if (_parent == nullptr) {
		_setWorldRecursively(nullptr);
	}
	else {
		//might still not be available if our parent is not part of the world
		_setWorldRecursively(_parent->_world);
	}
}

void GameObject::_innerRemove(GameObject* pChild) {
	for (auto i = _children.begin(); i != _children.end(); ++i) {
		if (*i == pChild) {
			_children.erase(i);
			pChild->_parent = nullptr;
			return;
		}
	}
}

void GameObject::_innerAdd(GameObject* pChild)
{
	_children.push_back(pChild);
	pChild->_parent = this;
}

void GameObject::add(GameObject* pChild) {
	pChild->setParent(this);
}

void GameObject::remove(GameObject* pChild) {
	pChild->setParent(nullptr);
}

GameObject* GameObject::getParent() const {
	return _parent;
}

////////////

//costly operation, use with care
glm::vec3 GameObject::getWorldPosition() const
{
	return glm::vec3(getWorldTransform()[3]);
}

//costly operation, use with care
glm::mat4 GameObject::getWorldTransform() const
{
	if (_parent == nullptr) return _transform;
	else return _parent->getWorldTransform() * _transform;
}

void GameObject::translate(glm::vec3 pTranslation)
{
	setTransform(glm::translate(_transform, pTranslation));
}

void GameObject::scale(glm::vec3 pScale)
{
	setTransform(glm::scale(_transform, pScale));
}

void GameObject::rotate(float pAngle, glm::vec3 pAxis)
{
	setTransform(glm::rotate(_transform, pAngle, pAxis));
}

void GameObject::update(float pStep)
{
	//make sure behaviour is updated after worldtransform is set
	if (_behaviour) {
		_behaviour->update(pStep);
	}

	for (int i = _children.size() - 1; i >= 0; --i) {
		_children[i]->update(pStep);
	}
}

bool GameObject::hasCollider()
{
	return _boxCollider != nullptr;
}

void GameObject::OnCollision(GameObject * pOther)
{
	for (int i = _children.size() - 1; i >= 0; --i) {
		_children[i]->OnCollision(pOther);
	}
}

void GameObject::_setWorldRecursively(World* pWorld) {
	_world = pWorld;

	for (int i = _children.size() - 1; i >= 0; --i) {
		_children[i]->_setWorldRecursively(pWorld);
	}
}

GameObject* GameObject::copy(std::string pName, GameObject* o)
{
	if (o == this) {
		printf(("Error: Parent loop in " + _name).c_str());
		return nullptr;
	}
	if (o == nullptr) o = this;
	std::string copyName = pName;
	glm::vec3 pos = getLocalPosition();
	if (copyName == "") copyName = _name;
	GameObject* g = new GameObject(copyName, pos);
	g->setParent(getParent());
	for (int a = 0; a < getChildCount(); a++) {
		g->add(getChildAt(a)->copy());
	}
	g->setMesh(getMesh());
	AbstractBehaviour* beh = getBehaviour();
	if (beh != nullptr) {
		g->setBehaviour(beh->copy());
	}
	g->setMaterial(getMaterial());
	g->setTransform(getTransform());
	GameObject::getActor(config::CURRENT_SCENE);
	_gameObjects.push_back(this);
	return g;
}

int GameObject::getChildCount() const {
	return _children.size();
}

GameObject* GameObject::getChildAt(int pIndex) const {
	return _children[pIndex];
}

std::map<std::string, GameObject*> GameObject::actors = std::map<std::string, GameObject*>();

GameObject* GameObject::getActor(std::string tag)
{
	GameObject* actor = nullptr;
	if (tag != "" || isActor(tag)) {
		return actors[tag];
	}
	if (actor == nullptr) {
		std::cout << "No Actor with tag [" << tag << "] exists!";
	}
	return actor;
}

std::vector<GameObject*> GameObject::getAllObjects()
{
	return _gameObjects;
}

bool GameObject::isActor(std::string tag)
{
	return(actors.count(tag));
}

void GameObject::setActor(std::string tag)
{
	using namespace std;
	if (tag == "") return;
	if (isActor(tag)) {
		cout << "Actor with tag [" << tag << "] already exists." << endl;
		return;
	}
	else {
		actors.insert(pair<string, GameObject*>(tag, this));
		actor_tag = tag;
	}
}

void GameObject::removeActor()
{
	if (actor_tag != "") {
		actors.erase(actor_tag);
	}
}

std::string GameObject::getActorTag() { return actor_tag; }

void GameObject::setTag(std::string pTag) { tag = pTag; }
std::string GameObject::getTag() { return tag; }
std::vector<GameObject*> GameObject::_gameObjects;
int GameObject::id;