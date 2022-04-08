// Separated Axis Theorem Example.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 

#include <math.h>
#include "BouncingThing.h"
#include "CollisionDetection.h"
#include "ShapeMaker.h"


//////////////////////////////////////////////////////////// 
/// Entry point of application 
//////////////////////////////////////////////////////////// 
int main()
{
	// Sets random seed.
	srand((unsigned)time(0));

	// Windows Size
	int screenWidth = 800;
	int screenHeight = 800;

	// Creates window for the project
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight, 32), "Separated Axis Theorem");

	// Runs collision detection
	CollisionDetection::instance(screenWidth, screenHeight);


	// Generate total quantity of each shape 
	int totalTriangles = 5 + rand() % 20;
	int totalBoxes = 5 + rand() % 10;
	int totalMultisides = 2 + rand() % 10;

	// Will create shapes
	ShapeMaker::instance(screenWidth, screenHeight);

	// Used to set ID of a thing
	int id_count = 0;			
	std::vector<BouncingThing*> things;

	// Speed and angle used to launch things
	float launchSpeed, launchAngle;

	for (int i = 0; i < totalTriangles; i++)
	{
		launchSpeed = 0.02 + (rand() % 200) / 10000;
		launchAngle = rand() % 360;

		things.push_back(ShapeMaker::instance()->createTriangle(id_count));
		things.back()->launch( launchSpeed, launchAngle);
		id_count++;
	}

	for (int i = 0; i < totalBoxes; i++)
	{
		launchSpeed = 0.05 + (rand() % 200) / 10000;
		launchAngle = rand() % 360;

		things.push_back(ShapeMaker::instance()->createBox(id_count));
		things.back()->launch(launchSpeed, launchAngle);
		id_count++;
	}

	for (int i = 0; i < totalMultisides; i++)
	{
		launchSpeed = 0.05 + (rand()%200)/10000;
		launchAngle = rand() % 360;

		things.push_back(ShapeMaker::instance()->createMultiside(id_count));
		things.back()->launch(launchSpeed, launchAngle);
		id_count++;
	}


	//prepare OpenGL surface for HSR 
	glClearDepth(1.f);
	glClearColor(0.0f, 0.0f, 0.0f, 0.f); //background colour
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	// Setup a perspective projection & Camera position 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set up a  orthographic projection same size as window
	// This mease the vertex coordinates are in pixel space
	glOrtho(0, screenWidth, 0, screenHeight, 0, 1); // use pixel coordinates


	// Start game loop 
	while (window.isOpen())
	{
		// Process events 
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			// Close window : exit 
			if (Event.type == sf::Event::Closed)
				window.close();

			// Escape key : exit 
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();
		}

		//Prepare for drawing 
		// Clear color and depth buffer 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Apply some transformations 
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


		std::vector<BouncingThing*>::iterator mainIt = things.begin();
		std::vector<BouncingThing*>::iterator subIt = things.begin();

		for (; mainIt != things.end(); ++mainIt)
		{
			// Checks Borders
			CollisionDetection::instance()->BorderCollision(*mainIt);

			(*mainIt)->update();
			(*mainIt)->draw();

			// Check for collisions is first
			for (; subIt != things.end(); ++subIt)
			{
				// Checks so that there is no check on self
				if (subIt != mainIt)
				{
					// Checks for bounding spheres, pair check and SAT
					CollisionDetection::instance()->CollisionCheck(*subIt, *mainIt);
				}
			}

			subIt = things.begin();
		}

		mainIt = things.begin();

		// Clears collisison list
		for (; mainIt != things.end(); mainIt++)
			(*mainIt)->ClearCollideList();


		// Finally, display rendered frame on screen 
		window.display();
	}

	return EXIT_SUCCESS;
}

