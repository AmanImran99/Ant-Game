#include "Rain.hpp"
#include "Ant.hpp"



// Constructor
Rain::Rain(float X) : x(X), y(700), width(20), height(50), reset(0), speed(5) {}


void Rain::draw() const {
    glColor3f(0.3, 0.3, 1);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
    glEnd();
}

bool Rain::checkCollision(const Ant& ant) {
    // Rain bounding box
    float rainLeft = x;
    float rainRight = x + width;
    float rainBottom = y;
    float rainTop = y + height;

    // Ant bounding box
    float antLeft = ant.getX();
    float antRight = ant.getX() + 50;	//50 is the width of the ant
    float antBottom = ant.getY();
    float antTop = ant.getY() + 50;		//50 is the height of the ant

    // Check for overlapping bounding boxes
    return !(rainRight < antLeft ||   // Rain is to the left of the Ant
             rainLeft > antRight ||  // Rain is to the right of the Ant
             rainTop < antBottom ||  // Rain is below the Ant
             rainBottom > antTop);   // Rain is above the Ant
}

void Rain::drop(int &score) {
    y -= speed; // Move the raindrop down
    if (y + height < 0) { // Check if it has moved below the screen
        y = 700; // Reset to the top of the screen
        reset += 1;
        x = rand() % 600-width + 20;
        // Increment the score every time the raindrop resets
        score += 1;
    }
}
