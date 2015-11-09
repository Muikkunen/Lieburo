#include "Game.hpp"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int BITS_PER_PIXEL = 32;
const sf::Time TIMESTEP = sf::seconds(1.0f / 60.0f); // timestep, 60 fps
const int velocityIterations = 8;
const int positionIterations = 3;



void Game::setup() {
	//create the Box2D world
	b2Vec2 gravity(0.0f, -9.8f);
	b2World* mWorld = new b2World(gravity, true);
	//create the ground body
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	b2Body *groundBody = mWorld->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);

	sf::RenderWindow rWindow;
	//instantiate the main window
	rWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, BITS_PER_PIXEL), "Lieburo");

	while(running) {
		run();
	}

	rWindow.close();
}

//main game loop
void Game::run() {
	
	sf::Clock clock;

	//double currentTime = clock.getElapsedTime().asSeconds();
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	//fixed fps game loop, http://gafferongames.com/game-physics/fix-your-timestep/

	while(rWindow.isOpen()) {
		/*
		double newTime = clock.getElapsedTime().asSeconds();
		double frameTime = newTime - currentTime;
		*/
		sf::Time dt = clock.restart();


		//For avoiding spiral of death
		if(dt > sf::seconds(0.25f)) {
			dt =  sf::seconds(0.25f);
		}

		//currentTime = newTime;
		timeSinceLastUpdate += dt;

		

		//logic update loop, everything that affects physics need to be here
		while(timeSinceLastUpdate > TIMESTEP) {
			
			timeSinceLastUpdate -= TIMESTEP;
			//Process system events
			//processEvents();

			//update game entities
			update(timeSinceLastUpdate);
		}
		// synchronize();
		// render entities
		render();
	}
}

void Game::update(sf::Time deltaTime) {
	//foreach entity call update
}

void Game::render() {
	//foreach entity call render
}

void synchronize(){
	//foreach entity call synchronize
}