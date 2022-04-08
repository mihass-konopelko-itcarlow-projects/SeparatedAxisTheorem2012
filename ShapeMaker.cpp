#include "stdafx.h" 
#include "ShapeMaker.h"
#include <math.h>
#include <random>

ShapeMaker* ShapeMaker::m_instance = 0;

ShapeMaker* ShapeMaker::instance(int borderWidth, int borderHeight)
{
	if (m_instance == 0)
		m_instance = new ShapeMaker(borderWidth, borderHeight);

	return m_instance;
}

ShapeMaker::ShapeMaker(int borderWidth, int borderHeight) :
	m_borderMax(borderWidth, borderHeight)
{
	// Generate a set of spawn positions when the instance is initialised
	this->generateSpawnPositions();
}



BouncingThing* ShapeMaker::createTriangle(int id)
{
	sf::Vector2i spawn = this->getSpawnPosition();
	return new BouncingTriangle(
		spawn.x,
		spawn.y,
		this->setSize(),
		this->setAngle(),
		this->setAngularVelocity(),
		id);
}

BouncingThing* ShapeMaker::createBox(int id)
{
	sf::Vector2i spawn = this->getSpawnPosition();
	return new BouncingBox(
		spawn.x,
		spawn.y,
		this->setSize(),
		this->setAngle(),
		this->setAngularVelocity(),
		id);
}

BouncingThing* ShapeMaker::createMultiside(int id) 
{
	sf::Vector2i spawn = this->getSpawnPosition();
	return new BouncingMultiside(
		spawn.x,
		spawn.y,
		this->setNumberOfSides(),
		this->setSize(),
		this->setAngle(),
		this->setAngularVelocity(),
		id);
}


void ShapeMaker::generateSpawnPositions()
{
	// First we generate a number of sectors where things can be generated
	int sectorSize = MAX_THING_SIZE + BUFFER_SPACE;
	
	int xSectors = m_borderMax.x / sectorSize;
	int ySectors = m_borderMax.y / sectorSize;

	// To not spawn any thing on the edge, substract 2 from the sector variables
	xSectors -= 2;
	ySectors -= 2;

	// Generate spawn points via for loop and iterators
	int xPos, yPos;
	int ySecItt = 0;
	for (int xSecItt = 0; xSecItt < xSectors && ySecItt < ySectors; xSecItt++) 
	{
		// Pos = corner border sector + n*sectors passed + random position within sector
		xPos = sectorSize + (sectorSize * xSecItt) + (rand() % sectorSize/2);
		yPos = sectorSize + (sectorSize * ySecItt) + (rand() % sectorSize/2);

		m_pregeneratedSpawns.push_back(sf::Vector2i(xPos, yPos));

		if (xSecItt == xSectors - 1) {
			xSecItt = 0;
			ySecItt++;
		}
	}

	std::random_shuffle(m_pregeneratedSpawns.begin(), m_pregeneratedSpawns.end());
}

sf::Vector2i ShapeMaker::getSpawnPosition() 
{
	sf::Vector2i spawnPoint = m_pregeneratedSpawns.back();
	m_pregeneratedSpawns.pop_back();
	return spawnPoint;
}

int ShapeMaker::setSize() 
{
	return MIN_THING_SIZE + rand() % (MAX_THING_SIZE - MIN_THING_SIZE);
}

float ShapeMaker::setAngle() 
{
	return rand() % 360;
}

float ShapeMaker::setAngularVelocity() 
{
	return -0.02f + ((rand() % 40) / 100);
}

int ShapeMaker::setNumberOfSides()
{
	return 4 + rand() % 4;
}