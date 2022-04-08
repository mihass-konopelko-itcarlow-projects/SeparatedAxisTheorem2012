# SeparatedAxisTheorem2012

My second-year project involving collision detection via SAT. It was implemented using SFML2 (window creation and updating) and a bit of OpenGL (for fine line drawing).

Project Features:

  • Randomly generated squares, triangles and simple polygons
  
  • Real-time collision of generated shapes against themselves and the border of the screen (SAT and Bounding Sphere)

  
---------------------- 
Controls:

•	None

----------------------

Bugs:

•	None (fixed them before uploading to GitHub)
 
----------------------

Important Note: while I inteded to keep this project unaltered, I had to do multiple changes to make it work in 2022:

-Due to a difference in 10 years (geez I feel older now), I had to port it from VS2011 onto VS2022.  This led to a compability issue with SFML2.  Sadly at a time of this submission there was no SFML version for VS2022, so I had to cMake it.

While looking at the project, I decided to address some bugs which were:
  
-Cheap colision against the window border (instead of vertex point collision, my student self went and implemented collision against the centre of the shape)
  
-Stucking, which was addressed in two ways: one via a dedicated spawn point allocation (so that a random shape did not spawn in another random shape) and another via inverting rotation when two shapes collided.
