# pragma once
#include "BouncingThing.h"


class BouncingMultiside: public BouncingThing
{
public:	
	BouncingMultiside(int x, int y, int sidesnum,int size, float intialAngle, float angularRotationSpeed,int id);

	void update();
	void draw();	
	void launch(double speed, double angle);

	void AddCollidePair(int id);
	bool CheckIfCollidedAlready(int id);
	void ClearCollideList();

	std::vector<sf::Vector2f> getSA();
	std::vector<sf::Vector2f> getVerteciesScreenPosition();
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	float getBoundigCircleRadius();	
	int getId();

	void setPosition(sf::Vector2f pos);
	void setVelocity(sf::Vector2f vel);
	void invertRotationVelocity();
};