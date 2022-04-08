#include "stdafx.h" 
#include "CollisionDetection.h"
#include <iostream>



CollisionDetection * CollisionDetection::m_instance = 0;

CollisionDetection::CollisionDetection(int borderWidth, int borderHeight):
	m_borderMax(borderWidth,borderHeight) { }

void CollisionDetection::BorderCollision(BouncingThing* obj)
{
	std::vector<sf::Vector2f> corners = obj->getVerteciesScreenPosition();
	sf::Vector2f centrePos = obj->getPosition();

	for (int i = 0; i < corners.size(); i++)
	{
		if (centrePos.y + corners.at(i).y >= m_borderMax.y)
		{
			obj->setVelocity(sf::Vector2f(obj->getVelocity().x, obj->getVelocity().y * -1));
			obj->invertRotationVelocity();
		}

		else if (centrePos.y + corners.at(i).y <= 0) 
		{
			obj->setVelocity(sf::Vector2f(obj->getVelocity().x, obj->getVelocity().y * -1));
			obj->invertRotationVelocity();
		}

		if (centrePos.x + corners.at(i).x >= m_borderMax.x) 
		{
			obj->setVelocity(sf::Vector2f(obj->getVelocity().x * -1, obj->getVelocity().y));
			obj->invertRotationVelocity();
		}

		else if (centrePos.x + corners.at(i).x <= 0) 
		{
			obj->setVelocity(sf::Vector2f(obj->getVelocity().x * -1, obj->getVelocity().y));
			obj->invertRotationVelocity();
		}
	}	
}

CollisionDetection * CollisionDetection::instance(int borderWidth, int borderHeight) 
{
	if (m_instance == 0)  
		m_instance = new CollisionDetection(borderWidth, borderHeight);
	
    return m_instance;
}


bool CollisionDetection::CheckSA(std::vector<sf::Vector2f> sa, BouncingThing* objA, BouncingThing* objB)
{
	float minA = 0, maxA = 0;    
	float minB = 0, maxB = 0;

	std::vector<sf::Vector2f> m_objAVerts = objA->getVerteciesScreenPosition();
	std::vector<sf::Vector2f> m_objBVerts = objB->getVerteciesScreenPosition();

	std::vector<sf::Vector2f>::iterator saItt = sa.begin();

	for (; saItt < sa.end(); ++saItt)
	{
		std::vector<sf::Vector2f>::iterator objAVertsItt = m_objAVerts.begin();
		for (int i = 0; objAVertsItt < m_objAVerts.end(); ++objAVertsItt, i++)    
		{  
			float result = objAVertsItt->x * saItt->x + objAVertsItt->y * saItt->y;
  
			if (i == 0) maxA = minA = result;
			if (result > maxA) maxA = result;   
			if (result < minA) minA = result;
		}

		// Offset
		minA += objA->getPosition().x * saItt->x +objA->getPosition().y * saItt->y;
		maxA += objA->getPosition().x * saItt->x +objA->getPosition().y * saItt->y;

		
		std::vector<sf::Vector2f>::iterator objBVertsItt = m_objBVerts.begin();
		for (int i =0; objBVertsItt < m_objBVerts.end(); ++objBVertsItt, i++)
		{  
			float result = objBVertsItt->x * saItt->x + objBVertsItt->y * saItt->y;
  
			if (i == 0) maxB = minB = result;
			if (result > maxB) maxB = result;           
			if (result < minB) minB = result;
		}

		// Offset
		minB += objB->getPosition().x * saItt->x +objB->getPosition().y * saItt->y;
		maxB += objB->getPosition().x * saItt->x +objB->getPosition().y * saItt->y;   

		if ( minA>maxB || minB>maxA)    
			return true;	        
	}        
	return false;
}

bool CollisionDetection::CheckForCollisionSAT(BouncingThing* objA,BouncingThing* objB)
{
	std::vector<sf::Vector2f> objASA = objA->getSA();
	std::vector<sf::Vector2f> objBSA = objB->getSA();
  
	if (CheckSA(objASA, objA, objB))
		return false;
            
	if(CheckSA(objBSA, objA, objB))
		return false;
          
	return true;
}

bool CollisionDetection::CollisionCheck(BouncingThing* objA,BouncingThing* objB)
{	
	// Pair redundancy check
	if (!objA->CheckIfCollidedAlready(objB->getId())|| !objB->CheckIfCollidedAlready(objA->getId()))
	{
		// Bound Circle collision check
		if (sqrt(	pow((objA->getPosition().x -objB->getPosition().x),2)+
					pow((objA->getPosition().y -objB->getPosition().y),2))   < objA->getBoundigCircleRadius()+ objB->getBoundigCircleRadius())
		{
			if (CheckForCollisionSAT( objA, objB))
			{
				// Responce:
				sf::Vector2f temp = objA->getVelocity();
				objA->setVelocity(objB->getVelocity());
				objB->setVelocity(temp);

				objA->invertRotationVelocity();
				objB->invertRotationVelocity();

				objA->AddCollidePair(objB->getId());
				objB->AddCollidePair(objA->getId());

				return true;
			}
		objA->AddCollidePair(objB->getId());
		objB->AddCollidePair(objA->getId());
		}
	}
	return false;
}





