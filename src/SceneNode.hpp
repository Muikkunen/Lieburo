#ifndef SCENENODE_HH
#define SCENENODE_HH

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

//library includes
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <vector>
#include <memory>
#include <assert.h>

class SceneNode {

public:
	typedef std::shared_ptr<SceneNode> Ptr;

	SceneNode(){}
	~SceneNode();

	void attachChild(Ptr child);
	Ptr detachChild(const SceneNode& node);
	std::vector<Ptr>& getChildren();
	virtual b2Body* getBody()const{return NULL;}
	virtual bool isAlive(){return false;}
	virtual void setAlive(bool){}

	void updateAll(sf::Time deltaTime);
	void drawAll(sf::RenderTarget& target);
	void removeAll();

	virtual void update(sf::Time){}
	virtual void draw(sf::RenderTarget&){}

private:
	std::vector<Ptr> mChildren;
	std::vector<Ptr> childrenToDestroy;
	SceneNode* mParent;
};


#endif