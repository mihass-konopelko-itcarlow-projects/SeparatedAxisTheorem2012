# pragma once
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include "BouncingThing.h"

class CollisionDetection
{
public:
	static CollisionDetection * instance(int borderWidth =0, int borderHeight=0);
	
	void BorderCollision(BouncingThing* obj);
	bool CollisionCheck(BouncingThing* obj1,BouncingThing* obj2);
	bool CheckForCollisionSAT(BouncingThing* obj1,BouncingThing* obj2);

	bool CheckSA(std::vector<sf::Vector2f> sa, BouncingThing* obj1,BouncingThing* obj2);

protected:
	CollisionDetection(int borderWidth, int borderHeight);
	static CollisionDetection * m_instance;

private:
	sf::Vector2f m_borderMax;


};