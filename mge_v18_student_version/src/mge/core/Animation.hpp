//	AbstractMaterial* playerMaterial = new TextureMaterial(Texture::load(config::MGE_ANIMATIONS_PATH + "Shooting UP.1.png"));
#pragma once

#include <vector>

#include "mge/core/Texture.hpp"

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"

class Animation
{
public:
	//get frame you get Texture of our own creation not sfml
	Animation();
	~Animation();
	void addFrame(TextureMaterial* playerAnimationframe);
	std::size_t getSize();
	TextureMaterial* getFrame(std::size_t n);


private:
	std::vector<TextureMaterial*> m_frames;

};