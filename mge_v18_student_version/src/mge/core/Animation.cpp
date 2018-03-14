#include "mge/core/Animation.hpp"

Animation::Animation()
{
}


Animation::~Animation()
{
}

void Animation::addFrame(TextureMaterial* playerAnimationframe)
{
	m_frames.push_back(playerAnimationframe);
}

std::size_t Animation::getSize()
{
	return m_frames.size();
}


TextureMaterial* Animation::getFrame(std::size_t n)
{
	return m_frames[n];
}