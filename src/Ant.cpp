#include "Ant.hpp"
#include <cstdio>
#include <iostream>

// Constructor
Ant::Ant(float startX, float startY)
    : x(startX), y(startY), facingRight(true) { // Initialize facingRight to true
    // Ant dimensions
    width = 50;
    height = 50;
}

void Ant::updateFrame(float deltaTime) const {
    frameTimer += deltaTime; // Increment the timer
    if (frameTimer >= 0.2f) { // Change frame every 0.2 seconds (adjust as needed)
        frameTimer = 0.0f; // Reset timer
        currentFrame = (currentFrame + 1) % 4; // Loop through frames 0 -> 1 -> 2 -> 3
    }
}

GLuint loadTexture(const std::string& filePath) {
    GLuint textureID = SOIL_load_OGL_texture(
        filePath.c_str(),  // Path to the texture file
        SOIL_LOAD_AUTO,    // Automatically detect format
        SOIL_CREATE_NEW_ID, // Generate a new OpenGL texture ID
        SOIL_FLAG_INVERT_Y // Flip the texture vertically
    );

    if (!textureID) {
        std::cerr << "Failed to load texture: " << filePath << " - " << SOIL_last_result() << std::endl;
    } else {
        // Set texture parameters
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    return textureID;
}

void Ant::loadTextures() {
    // Load textures using the helper function
    ant_idle1 = loadTexture("textures/ant(idle1).png");
    ant_idle2 = loadTexture("textures/ant(idle2).png");
    ant_idle3 = loadTexture("textures/ant(idle3).png");
}

// Draw the Ant as a rectangle
void Ant::draw() const {
    // Update the frame based on time
    updateFrame(0.01f); // Pass time step (adjust for desired animation speed)

    GLuint currentTexture;
    // Select texture based on current frame
    switch (currentFrame) {
        case 0: currentTexture = ant_idle1; break;
        case 1: currentTexture = ant_idle2; break;
        case 2: currentTexture = ant_idle3; break;
        case 3: currentTexture = ant_idle2; break;
        default: currentTexture = ant_idle1; break; // Fallback
    }

    // Enable texture rendering
    glEnable(GL_TEXTURE_2D);

    // Enable blending for transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Set blending function

    // Bind the current texture
    glBindTexture(GL_TEXTURE_2D, currentTexture);

    // Draw the textured rectangle
    glBegin(GL_QUADS);
    if (facingRight) {
        // Draw normally
        glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y);   // Bottom-left
        glTexCoord2f(1.0f, 0.0f); glVertex2f(x + width, y); // Bottom-right
        glTexCoord2f(1.0f, 1.0f); glVertex2f(x + width, y + height); // Top-right
        glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y + height);   // Top-left
    } else {
        // Flip horizontally
        glTexCoord2f(1.0f, 0.0f); glVertex2f(x, y);   // Bottom-left
        glTexCoord2f(0.0f, 0.0f); glVertex2f(x + width, y); // Bottom-right
        glTexCoord2f(0.0f, 1.0f); glVertex2f(x + width, y + height); // Top-right
        glTexCoord2f(1.0f, 1.0f); glVertex2f(x, y + height);   // Top-left
    }
    glEnd();

    // Disable blending and textures
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}

// Move the Ant by an offset
void Ant::move(char ch) {
    if (ch == 'r') {
        x += 20;
        facingRight = false; // Update direction// Update direction
    }
    if (ch == 'l') {
        x -= 20;
        facingRight = true;
    }
    // Constraints
    if (x < 0) x = 0;
    if (x + width > 600) {
        x = 600 - width;
    }
}
