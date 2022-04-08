#include "stdafx.h" 
#include "Multiside.h"

BouncingMultiside::BouncingMultiside(int x, int y, int sidesnum, int size, float initialAngle, float angularRotationSpeed,int id)
{
	m_position = sf::Vector2f(x,y);
	m_angle =initialAngle;
	m_rotation.rotate(angularRotationSpeed);
	m_totalSides = sidesnum;

	double PI =4*atan(1);
	double angleVal = 2*PI/m_totalSides; 

	m_id = id;

	for(register int i = 0; i<m_totalSides ;++i)
		m_vertPositions.push_back(sf::Vector2f( cos(initialAngle+(angleVal)*i)*size, sin(initialAngle+(angleVal)*i)*size));
	     

	m_boundingSphereRadius = size + 1;
}

void BouncingMultiside::update() 
{
	m_position += m_velocity;
	for(register int i = 0; i<m_totalSides ;++i)	
		m_vertPositions[i] = m_rotation.transformPoint(m_vertPositions[i]);
}

void BouncingMultiside::draw() 
{
	glBegin(GL_LINE_LOOP);

	for(register int i = 0; i<m_totalSides ;++i)
		glVertex2d(		m_vertPositions[i].x + m_position.x,
						m_vertPositions[i].y+ m_position.y);    
		
	glEnd(); 
}

void BouncingMultiside::launch(double speed, double angle)
{
	m_velocity.x =speed*cos(angle);
	m_velocity.y =speed*sin(angle);
}

void BouncingMultiside::AddCollidePair(int id)
{
	m_collisionChecksWith.push_back(id);
}

bool BouncingMultiside::CheckIfCollidedAlready(int id)
{
	for(int i =0;i<m_collisionChecksWith.size();i++)
	{
		if(m_collisionChecksWith[i] == id)
			return true;
	}
	return false;
}

void BouncingMultiside::ClearCollideList()
{
	m_collisionChecksWith.clear();
}





sf::Vector2f BouncingMultiside::getPosition()
{
	return m_position;
}

float BouncingMultiside::getBoundigCircleRadius()
{
	return m_boundingSphereRadius;
}

sf::Vector2f BouncingMultiside::getVelocity()
{
	return m_velocity;
}

std::vector<sf::Vector2f> BouncingMultiside::getSA()
{
	std::vector<sf::Vector2f> sepAxis;

	// Separated Axis variables
	float SAx;
	float SAy;

	for (int i = 0; i < m_totalSides; i++)
	{
		if( i+1 < 3)
		{
			SAx = -(m_vertPositions[i].y - m_vertPositions[i+1].y);
			SAy = (m_vertPositions[i].x - m_vertPositions[i+1].x);
		} 

		else
		{
			SAx = -(m_vertPositions[i].y - m_vertPositions[0].y);
			SAy = (m_vertPositions[i].x - m_vertPositions[0].x);
		}

		sepAxis.push_back( sf::Vector2f(SAx,SAy)/ sqrt(SAx*SAx +SAy*SAy ));
	}
	return sepAxis;
}

std::vector<sf::Vector2f> BouncingMultiside::getVerteciesScreenPosition()
{
	return m_vertPositions;
}

int BouncingMultiside::getId()	
{
	return m_id;
}


void BouncingMultiside::setVelocity(sf::Vector2f vel)
{
	m_velocity = vel;
}

void BouncingMultiside::setPosition(sf::Vector2f pos)
{
	m_position = pos;
}

void BouncingMultiside::invertRotationVelocity()
{
	m_rotation = m_rotation.getInverse();
}






	 

