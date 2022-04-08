# pragma once
#include "BouncingThing.h"


class BouncingTriangle : public BouncingThing
{
public:	
	BouncingTriangle(int x, int y, int size, float intialAngle, float angularRotationSpeed,int id);

	void launch(double speed, double angle);
	void update();
	void draw();	


	void AddCollidePair(int id);
	bool CheckIfCollidedAlready(int id);
	void ClearCollideList();

	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	float getBoundigCircleRadius();
	std::vector<sf::Vector2f> getSA();
	std::vector<sf::Vector2f> getVerteciesScreenPosition();
	int getId();


	void setPosition(sf::Vector2f pos);
	void setVelocity(sf::Vector2f vel);
	void invertRotationVelocity();
};