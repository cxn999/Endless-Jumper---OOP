#include "Background.h"
#include <iostream>

Background::Background() = default;

void Background::addLayer(const sf::Texture& s)
{
	m_length++;
	sf::Sprite t = sf::Sprite(s);
	auto size = Vec2((float)(s.getSize().x), (float)s.getSize().y);
	t.setOrigin(size.x / 2.f, size.y / 2.f);
	t.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
	t.setScale(6, 6);
	m_layers.push_back(t);
}

size_t Background::getLength() {
	return m_length;
}

std::vector<sf::Sprite> & Background::getLayers() {
	return m_layers;
}