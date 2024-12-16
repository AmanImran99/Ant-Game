#ifndef Ant_HPP
#define Ant_HPP

#include <GL/glut.h> // Include for OpenGL functions
#include <SOIL.h>

class Ant {
private:
    float x, y;        // Ant position
    float width, height; // Dimensions of the Ant
    bool facingRight;
    GLuint ant_idle1;
    GLuint ant_idle2;
    GLuint ant_idle3;
    mutable int currentFrame; // Current frame index (mutable to change in const method)
    mutable float frameTimer; // Timer to control animation speed



public:
    Ant(float startX, float startY);

    // Draw the Ant
    void draw() const;

    // Move the Ant
    void move(char ch);

    //loadTextures
    void loadTextures();

    // Get position (optional, for collision detection, etc.)
    float getX() const { return x; }
    float getY() const { return y; }

    void updateFrame(float deltaTime) const; // Helper to update animation frame
};

#endif
