#pragma once
#include "BouncingThing.h"
#include "BouncingTriangle.h"
#include "BouncingBox.h"
#include "BouncingThing.h"
#include "Multiside.h"

class ShapeMaker
{
public:
	static ShapeMaker* instance(int borderWidth = 0, int borderHeight = 0);

	BouncingThing* createTriangle(int id);
	BouncingThing* createBox(int id);
	BouncingThing* createMultiside(int id);

protected:
	ShapeMaker(int borderWidth, int borderHeight);
	static ShapeMaker* m_instance;

private:
	// Limits the sizes for the created shapes
	const int MIN_THING_SIZE = 10;
	const int MAX_THING_SIZE = 25;

	// Used to create a buffer space between generated shapes
	const int BUFFER_SPACE = 30;


	sf::Vector2f m_borderMax;
	std::vector<sf::Vector2i> m_pregeneratedSpawns;

	void generateSpawnPositions();
	sf::Vector2i getSpawnPosition();
	int setSize();
	float setAngle();
	float setAngularVelocity();
	int setNumberOfSides();
};