# pragma once

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 



class BouncingThing
{
protected:

	int m_id;						// Id is used for pair-check
	float m_speed;
	float m_angle;	
	float m_boundingSphereRadius;	
	int m_totalSides;

	sf::Vector2f m_position;		// Acts as a Centre as well
	sf::Vector2f m_velocity;
	sf::Transform m_rotation;
	sf::Transform m_translation; 

	std::vector<sf::Vector2f> m_vertPositions;
	std::vector<int> m_collisionChecksWith;


public:
	virtual void update()=0;
	virtual void draw()=0;
	virtual void launch(double speed, double angle)=0;

	virtual void AddCollidePair(int id) = 0;
	virtual bool CheckIfCollidedAlready(int id)=0;
	virtual void ClearCollideList()=0;

	virtual sf::Vector2f getPosition()=0;
	virtual sf::Vector2f getVelocity()=0;
	virtual float getBoundigCircleRadius()=0;
	virtual	std::vector<sf::Vector2f> getSA()=0;
	virtual std::vector<sf::Vector2f> getVerteciesScreenPosition()=0;
	virtual int getId()=0;

	virtual void setVelocity(sf::Vector2f vel) =0;
	virtual void setPosition(sf::Vector2f pos) =0;
	virtual void invertRotationVelocity() = 0;
};