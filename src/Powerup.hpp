#pragma once

#include "Entity.hpp"
#include "Game.hpp"

class Powerup : public Entity{

public:
	Powerup(Game* game, std::string textureName);
	~Powerup();

	void changeGravity(Game* game);
	void startContact(Entity* contact);
	void update(sf::Time deltaTime);
private:
};