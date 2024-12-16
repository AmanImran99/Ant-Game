#ifndef RAIN.HPP
#define RAIN_HPP


#include <GL/glut.h> // Include for OpenGL functions
#include "Ant.hpp"

class Rain {
public:
    float x, y;        	// Rain position
    int width, height;	// Rain size
    int reset;			// Amount of times the drop has hit the ground
    int speed;			// Speed of the raindrop

//draw rain drop
public:
    Rain(float X);

    // Draw the Rain
    void draw() const;

    // Drop the Rain
    void drop(int &score);

    // Check collision with the ant
    bool checkCollision(const Ant& ant);

    // Get position (optional, for collision detection, etc.)
    float getX() const { return x; }
    float getY() const { return y; }
};










#endif
