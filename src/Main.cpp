#include <GL/glut.h> // For GLUT functions and OpenGL support
#include <GL/gl.h>   // For core OpenGL functionality (optional, as GLUT includes it)
#include <GL/glu.h>  // For GLU functions (like gluOrtho2D)
#include <set>
#include <iostream>
#include <SOIL.h>
#include <sstream>  // Include for std::ostringstream
#include "Ant.hpp"
#include "Rain.hpp"


std::set<unsigned char> pressedKeys;
// Global ant instance
Ant ant(100.0f, 50.0f); // Start position

int score = 0;  // Initialize score
bool inGame = true;

int stage = 0;		//varaible to help increase difficulty

Rain drop1(20);
Rain drop2(500);
Rain drop3(300);
Rain drop4(600);
Rain drop5(300);
// Function to render text
void renderText(float x, float y, void *font, const char *text) {
    glRasterPos2f(x, y); // Set position to render text
    while (*text) {
        glutBitmapCharacter(font, *text);  // Render each character
        text++;
    }
}




void mainGameLoop(){
    // Draw the ant

	if (inGame){
	    ant.draw();
	    drop1.drop(score);  // Update raindrop position
	    drop1.draw();


	    //stage 1
	    if (score >= 1){
	    	if (stage == 0){
	    		drop2.y = 800;
	    		stage = 1;
	    	}
	    	drop2.drop(score);
	    	drop2.draw();
	    }

	    //stage 2
	    if (score >= 3){
	    	if (stage == 1){
	    		drop1.speed = 8;
	    		drop2.speed = 7;
	    		stage = 2;
	    	}
	    }

	    //stage 3
	    if (score >= 10){
	    	if (stage == 2){
	    		drop3.y = 950;
	    		stage = 3;
	    	}
	    	drop3.drop(score);
	    	drop3.draw();
	    }

	    //stage 4
	    if (score >= 20){
	    	if (stage == 3){
	    		drop1.speed = 13;
	    		drop2.speed = 11;
	    		drop3.speed = 11;
	    		stage = 4;
	    	}
	    }

	    //stage 5
	    if (score >= 35){
	    	if (stage == 4){
	    		drop4.y = 800;
	    		drop4.speed = 9;
	    		stage = 5;
	    	}
	    	drop4.drop(score);
	    	drop4.draw();
	    }


	    //stage 6
	    if (score >= 50){
	    	if (stage == 5){
	    		drop1.speed = 18;
	    		drop2.speed = 17;
	    		drop3.speed = 16;
	    		drop4.speed = 13;
	    		stage = 6;
	    	}
	    }

	    //stage 7
	    if (score >= 70){
	    	if (stage == 6){
	    		drop5.y = 900;
	    		drop5.speed = 12;
	    		stage = 7;
	    	}
	    	drop5.drop(score);
	    	drop5.draw();
	    }

	    //stage 8
	    if (score >= 100){
	    	if (stage == 7){
	    		drop1.speed = 25;
	    		drop2.speed = 24;
	    		drop3.speed = 23;
	    		drop4.speed = 20;
	    		drop5.speed = 20;
	    		stage = 8;
	    	}
	    }


	    // Check for collision
	    if 	(      (drop1.checkCollision(ant))
	    		|| (drop2.checkCollision(ant))
				|| (drop3.checkCollision(ant))
				|| (drop4.checkCollision(ant))
				|| (drop5.checkCollision(ant))		){
	        // Handle collision
	        //std::cout << "Collision detected!" << std::endl;
	        std::cout << "Final Score: " << score <<std::endl;
	        std::cout << ":)";
	        inGame = false;
	    }



	}
	else
	{
		//Code for after the game ends
	}
    // Render score (Remains on screen always)
    std::ostringstream scoreStream;
    scoreStream << "Score: " << score;
    std::string scoreStr = scoreStream.str();
    glColor3f(1.0, 1.0, 1.0);  // Set text color to white
    renderText(500.0f, 680.0f, GLUT_BITMAP_HELVETICA_18, scoreStr.c_str());


}








GLuint backgroundTexture;

void loadTexture() {

	//Background
    backgroundTexture = SOIL_load_OGL_texture(
        "textures/background.png", // Path to texture
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    if (!backgroundTexture) {
        std::cerr << "Failed to load texture: " << SOIL_last_result() << std::endl;
    }
    // Set texture parameters
    glBindTexture(GL_TEXTURE_2D, backgroundTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


void drawBackground(){
    // Enable 2D textures
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, backgroundTexture);

    // Draw a textured quad
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);   // Bottom-left
        glTexCoord2f(1.0f, 0.0f); glVertex2f(600.0f, 0.0f); // Bottom-right
        glTexCoord2f(1.0f, 1.0f); glVertex2f(600.0f, 700.0f); // Top-right
        glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, 700.0f);   // Top-left
    glEnd();

    glDisable(GL_TEXTURE_2D);
}




// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawBackground();

	mainGameLoop();



    glutSwapBuffers();
}

// Timer callback for fixed frame rate
void timer(int value) {
    // Update game state


    // Check which keys are pressed and move the ant accordingly
    if (pressedKeys.count('a')) ant.move('l'); // Move left
    if (pressedKeys.count('d')) ant.move('r'); // Move right

    // Redraw the screen
    glutPostRedisplay();

    // Register the timer callback again
    glutTimerFunc(16, timer, 0); // Approx. 60 FPS (16 ms per frame)
}

void handleKeyPress(unsigned char key, int x, int y) {
    pressedKeys.insert(key); // Add key to the pressed keys set
}

void handleKeyRelease(unsigned char key, int x, int y) {
    pressedKeys.erase(key); // Remove key from the pressed keys set
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 700);
    glutCreateWindow("Life of Ant");

    loadTexture(); // Load the background texture
    ant.loadTextures();

    // Set up 2D orthographic projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 600, 0, 700);

    // Register callbacks
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeyPress);
    glutKeyboardUpFunc(handleKeyRelease); // To track key releases
    glutTimerFunc(16, timer, 0);          // Start the timer for fixed frame rate

    glutMainLoop();
    return 0;
}
