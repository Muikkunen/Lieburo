CC=g++
SFML=SFML-2.1
BOX2D=Box2D_v2.1.2
CPPFLAGS=-c -g -std=c++0x -Wall -Wextra -pedantic -I $(BOX2D)/Box2D # -I $(SFML)/include
SOURCES=main.cpp MyContactListener.cpp MyContactListener.hpp Menu.cpp Menu.hpp Options.cpp Options.hpp Game.hpp Game.cpp SceneNode.hpp SceneNode.cpp Entity.hpp Entity.cpp\
	Player.hpp Player.cpp Weapon.hpp Weapon.cpp BananaGun.hpp BananaGun.cpp Projectile.hpp Banana.hpp Banana.cpp Gamefield.hpp Gamefield.cpp\
	Powerup.hpp Powerup.cpp Missile.hpp Missile.cpp MissileLauncher.hpp MissileLauncher.cpp GUI.cpp GUI.hpp Rifle.hpp Rifle.cpp Bullet.hpp Bullet.cpp\
	Shrapnel.hpp Shrapnel.cpp Projectile.hpp Projectile.cpp GravityPU.hpp GravityPU.cpp GravityInverter.hpp GravityInverter.cpp HealthRecovery.hpp HealthRecovery.cpp\
	AnimatedSprite.cpp AnimatedSprite.hpp Animation.cpp Animation.hpp Bomb.hpp Bomb.cpp Sounds.hpp Sounds.cpp

LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lBox2D -L $(BOX2D)/Box2D/Build/Box2D #-L $(SFML)/lib
OBJECTS=main.o Game.o MyContactListener.o Menu.o Options.o SceneNode.o Entity.o Player.o Weapon.o BananaGun.o Banana.o Gamefield.o\
	Powerup.o Missile.o MissileLauncher.o GUI.o Rifle.o Bullet.o Shrapnel.o Projectile.o GravityPU.o GravityInverter.o HealthRecovery.o\
	Bomb.o Animation.o AnimatedSprite.o Sounds.o

EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)
  
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@ 

.cc.o:
	$(CC) $(CPPFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

run: main
	./main
