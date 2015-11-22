#ifndef GAME_HH
#define GAME_HH

//library includes
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>



//include required objects
#include "MyContactListener.hpp"
#include "SceneNode.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Menu.hpp"
#include "Options.hpp"
#include "Constants.h"
#include "Gamefield.hpp"

class Gamefield;
class Player;

class Game {
public:

	//TODO: Contact masks

	Game();
	~Game(){}
	void run();
	void update(sf::Time deltaTime, Menu &menu, Options &options);
	void render();
	bool navigate(sf::Event &event, Menu &menu);
	bool navigate(sf::Event &event, Options &options);
	b2World* getWorld();
	std::shared_ptr<SceneNode> getSceneNode();

private:
	std::shared_ptr<Player> player1;
	bool running;
	bool menu_screen;
	sf::RenderWindow rWindow;
	MyContactListener myContactListenerInstance;
	std::shared_ptr<SceneNode> sceneNode;
	b2World* mGameWorld;
	std::shared_ptr<Gamefield> gamefield;
};

#endif