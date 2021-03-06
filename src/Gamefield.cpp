#include "Gamefield.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Gamefield::Gamefield(b2World* world) {
	//load the background
    loadTexture("texture/sky.png");
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(mGroundTextures["texture/sky.png"]);
	backgroundSprite.setOrigin(0,-20);
	mGroundSprites.push_back(backgroundSprite);




	/*
	1. Create the static body

	2. Load the gamefield data from a file by going it through line by line
		File data structure: (location unit is pixels)
		Type/Shape, texture path, and then variuos parameters

		Depending on the texture type the lines parameters are different.
		1,Texture1name,x,y        this is a rectangle size is calaculated based on the texture. x and y determine the position
		2,Texture2name,x,y,x2,y2,x3,y3 this is a triangle and x's and y's are the triangles three corner positions (not working properly)
		3,Texture3name,x,y,r      this is a circle, x and y are the position and r is the radius
		4,Texture4name,x,y,sx,sy  this is a rectangle but the size is sx*sy and x and y determine the position
		5,Texture5name,x,y,sx,sy  the same as type 4 but this rectangle doesn't have friction at all.

	3. Per one line: Create a texture and create a sprite from it. Push the texture and sprite to a vector.

	4. Create a fixture based on the data

	5. Attach the fixture to the body.

	6. Repeat steps 3-5.  
	

	*/

	//Step 1
	mBodyDef.type = b2_staticBody;
	mBodyDef.position.Set(0, 0);//up-left corner
	mBodyDef.fixedRotation = true; // prevent rotation
	mBody = world->CreateBody(&mBodyDef);
	mBody->SetUserData(this); //emun would be better
	

	
	std::cout<< "Initializing gamefield" << std::endl;

	//Step 2
	std::string line;
	std::ifstream gameFieldFile ("gamefield1");

	if (gameFieldFile.is_open()) {
		while (std::getline(gameFieldFile, line)) {
			//Steps 3-5

			//splitting the line at the "," 

			std::stringstream ss(line);
			std::vector<std::string>fields;
			std::string field = "";
			while (std::getline(ss, field, ',')) {
				fields.push_back(field);
			}

			int type = std::stoi(fields[0],nullptr);
		    std::string filename = fields[1];
		    int x = std::stoi(fields[2], nullptr);
		    int y = std::stoi(fields[3], nullptr);

		    // Texture and sprite
		    loadTexture(filename);
			
		    sf::Sprite mSprite;
		    mSprite.setTexture(mGroundTextures[filename]);
	    	
			//setting the origin to be in the center as it is with the Box2d bodies and fixtures.
			sf::FloatRect bounds = mSprite.getLocalBounds();
			mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
			mSprite.setPosition(x, y);
			mGroundSprites.push_back(mSprite);
		

		    //creating the fixture
		    b2PolygonShape polygonShape;
		    b2FixtureDef mFixtureDef;

		    if(type == 1){
				polygonShape.SetAsBox(0.5f*bounds.width / PIXELS_PER_METER, 0.5f*bounds.height/PIXELS_PER_METER, b2Vec2(x/PIXELS_PER_METER,y/PIXELS_PER_METER), 0);
				mFixtureDef.shape = &polygonShape;
				mFixtureDef.density = 1;
				mFixtureDef.friction = 1.0f;
				mFixtureDef.filter.categoryBits = BOUNDARY; //I am a BOUNDARY, I collide with everything.
				mBody->CreateFixture(&mFixtureDef);
			}

			if(type == 2){
			    int x2 = std::stoi(fields[4], nullptr);
			    int y2 = std::stoi(fields[5], nullptr);
			    int x3 = std::stoi(fields[6], nullptr);
			    int y3 = std::stoi(fields[7], nullptr);

				b2Vec2 vertices[3];
				vertices[0].Set(x / PIXELS_PER_METER,y / PIXELS_PER_METER);
				vertices[1].Set(x2 / PIXELS_PER_METER,y2 / PIXELS_PER_METER);
				vertices[2].Set(x3 / PIXELS_PER_METER,y3 / PIXELS_PER_METER);
				polygonShape.Set(vertices, 3);

				mFixtureDef.shape = &polygonShape;
				mFixtureDef.friction = 0.0f;
				mFixtureDef.density = 1;
				mFixtureDef.filter.categoryBits = BOUNDARY; //I am a BOUNDARY, I collide with everything.
			}

			if(type == 3){
				int radius = std::stoi(fields[4],nullptr);

				b2CircleShape circleShape;
				circleShape.m_p.Set(x / PIXELS_PER_METER,y / PIXELS_PER_METER);
				circleShape.m_radius = radius / PIXELS_PER_METER;
				mFixtureDef.density = 1;
				mFixtureDef.shape = &circleShape;
				mFixtureDef.friction = 0.0f;
				mBody->CreateFixture(&mFixtureDef);
			}

			if(type == 4 || type == 5){
		    	int x2 = std::stoi(fields[4], nullptr);
		    	int y2 = std::stoi(fields[5], nullptr);
				polygonShape.SetAsBox(x2 / PIXELS_PER_METER, y2 / PIXELS_PER_METER, b2Vec2(x/PIXELS_PER_METER,y/PIXELS_PER_METER), 0);
				mFixtureDef.shape = &polygonShape;
				mFixtureDef.density = 1;
				mFixtureDef.friction = 1.0f;
				if(type == 5)
					mFixtureDef.friction = 0.0f;
				mFixtureDef.filter.categoryBits = BOUNDARY; //I am a BOUNDARY, I collide with everything.
				mBody->CreateFixture(&mFixtureDef);
			}
		}
	gameFieldFile.close();
	}
}



void Gamefield::draw(sf::RenderTarget& target) {
	for(auto& groundSprite:mGroundSprites) {
		target.draw(groundSprite);
	}
}

void Gamefield::loadTexture(std::string filename){
	sf::Texture t;
	t.loadFromFile(filename);
	mGroundTextures[filename] = t; 
}
